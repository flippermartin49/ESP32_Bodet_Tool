
#include "../include/wifi.h"


static const char *TAG_WIFI = "WIFI_P2P";

void wifi_init_p2p(void)
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    esp_netif_t* netif = esp_netif_create_default_wifi_ap();

    // ------ IP statique 192.168.4.1 ------
    esp_netif_ip_info_t ip_info;
    IP4_ADDR(&ip_info.ip,      192, 168, 4, 1);
    IP4_ADDR(&ip_info.gw,      192, 168, 4, 1);
    IP4_ADDR(&ip_info.netmask, 255, 255, 255, 0);

    ESP_ERROR_CHECK(esp_netif_dhcps_stop(netif));
    ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip_info));
    ESP_ERROR_CHECK(esp_netif_dhcps_start(netif));

 ESP_LOGI(TAG_WIFI, "IP AP fixée : %s", ip4addr_ntoa((const ip4_addr_t*)&ip_info.ip));

    // ------ WiFi ------
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "ESP32_P2P",
            .password = "12345678",
            .ssid_len = 0,
            .channel = 1,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG_WIFI, "Soft-AP actif. SSID: ESP32_P2P | IP: 192.168.4.1");
}

void wifi_create_ap(void)
{
    wifi_config_t ap_config = {
        .ap = {
            .ssid = "ESP32_P2P",
            .ssid_len = strlen("ESP32_P2P"),
            .channel = 1,
            .password = "12345678",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen((char*)ap_config.ap.password) == 0) {
        ap_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
    ESP_LOGI(TAG_WIFI, "Point d'accès créé avec SSID:%s", ap_config.ap.ssid);
}

void tcp_server_task(void *pvParameters)
{
    char rx_buffer[128];
    int addr_family = AF_INET;
    int ip_protocol = IPPROTO_IP;

    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    listen(listen_sock, 1);

    while (1) {
        struct sockaddr_in6 source_addr;
        socklen_t socklen = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &socklen);
        if (sock < 0) {
            ESP_LOGE(TAG_WIFI, "Erreur accept");
            continue;
        }

        int len;
        while ((len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0)) > 0) {
            rx_buffer[len] = 0;
            ESP_LOGI(TAG_WIFI, "Reçu: %s", rx_buffer);
        }
        close(sock);
    }
}