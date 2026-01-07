#include "ethernet.h"

static const char *TAG = "ETH_IP101";
static const char *TAG_UDP = "UDP_SCAN";

#define RECEIVE_PORT 1669
#define SEND_PORT    1668
#define DISCOVERY_MSG  "dhs 2 set-info"

static esp_eth_handle_t s_eth_handle = NULL;

static void eth_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
        case ETHERNET_EVENT_CONNECTED:
            ESP_LOGI(TAG, "Ethernet Link Up");
            break;
        case ETHERNET_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "Ethernet Link Down");
            break;
        case ETHERNET_EVENT_START:
            ESP_LOGI(TAG, "Ethernet Started");
            break;
        case ETHERNET_EVENT_STOP:
            ESP_LOGI(TAG, "Ethernet Stopped");
            break;
    }
}

static void got_ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    esp_netif_t *netif = (esp_netif_t *)arg;
    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(netif, &ip_info);

    ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&ip_info.ip));
}

static void get_eth_mac(uint8_t *mac)
{
    esp_eth_ioctl(s_eth_handle, ETH_CMD_G_MAC_ADDR, mac);
}

void ethernet_init(void)
{
    /// --- INIT ---
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    
    if (esp_event_loop_create_default() != ESP_OK) {
        ESP_LOGI(TAG, "Event loop already created, continuing...");
    }

    /// --- NETIF ---
    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t *eth_netif = esp_netif_new(&cfg);

    /// --- MAC + PHY CONFIG ---
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();
    eth_esp32_emac_config_t emac_config = ETH_ESP32_EMAC_DEFAULT_CONFIG();

    // RMII clock input (50MHz external)
    emac_config.clock_config.rmii.clock_mode = EMAC_CLK_EXT_IN; // important
    emac_config.clock_config.rmii.clock_gpio = EMAC_CLK_IN_GPIO; // GPIO0

    // PHY IP101
    phy_config.phy_addr = 1;          // IP101 = 0
    phy_config.reset_gpio_num = 5;    // reset
    phy_config.autonego_timeout_ms = 4000;

    // MAC + PHY drivers
    esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&emac_config, &mac_config);
    esp_eth_phy_t *phy = esp_eth_phy_new_ip101(&phy_config);

    esp_eth_handle_t eth_handle = NULL;
    esp_eth_config_t eth_config = ETH_DEFAULT_CONFIG(mac, phy);
    ESP_ERROR_CHECK(esp_eth_driver_install(&eth_config, &eth_handle));

    /// --- REGISTER EVENTS ---
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, eth_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, got_ip_event_handler, eth_netif));

    /// --- ATTACH & START ---
    ESP_ERROR_CHECK(esp_netif_attach(eth_netif, esp_eth_new_netif_glue(eth_handle)));
    ESP_ERROR_CHECK(esp_eth_start(eth_handle));

    ESP_LOGI(TAG, "Ethernet init done (IP101GRI)");
}

/************************** UDP REQUEST ***************/

void udp_broadcast_send()
{
    esp_netif_ip_info_t ip_info;
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("ETH_DEF");
    if (!netif) {
        ESP_LOGE(TAG_UDP, "Impossible de récupérer ETH_DEF");
        return;
    }

    esp_netif_get_ip_info(netif, &ip_info);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG_UDP, "Impossible de créer le socket");
        return;
    }

    // Autoriser le broadcast
    int broadcast = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    // Bind local (optionnel si tu veux forcer IP source)
    struct sockaddr_in local_addr = {0};
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(0); // port aléatoire
    local_addr.sin_addr.s_addr = ip_info.ip.addr; // IP locale Ethernet
    bind(sock, (struct sockaddr *)&local_addr, sizeof(local_addr));

    // Destination broadcast
    struct sockaddr_in dest_addr = {0};
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port   = htons(SEND_PORT);           // port sur lequel les autres écoutent
    dest_addr.sin_addr.s_addr = inet_addr("255.255.255.255"); // broadcast

    const char *msg = "dhs 1 get-info";
    int err = sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0) {
        ESP_LOGE(TAG_UDP, "Erreur sendto : %d", err);
    } else {
        ESP_LOGI(TAG_UDP, "Broadcast envoyé sur %s:%d", inet_ntoa(dest_addr.sin_addr), SEND_PORT);
    }

    close(sock);
}



void udp_discovery_listener_task(void *arg)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG_UDP, "socket failed");
        vTaskDelete(NULL);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(RECEIVE_PORT),
        .sin_addr.s_addr = INADDR_ANY,
    };

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    while (1) {
        char rx_buffer[128];
        struct sockaddr_in source_addr;
        socklen_t addr_len = sizeof(source_addr);

        int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &addr_len);

        if (len > 0) 
        {
            rx_buffer[len] = 0;

            ESP_LOGI(TAG_UDP, "Réponse de %s : %s", inet_ntoa(source_addr.sin_addr), rx_buffer);
        }
    }
}

