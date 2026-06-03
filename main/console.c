#include "../include/console.h"

static const char *TAG_PROMPT = "CONSOLE";

// ==========================
// Enregistrement commandes
// ==========================

void save_commands(void)
{
    esp_console_cmd_t AT_cmd = {
        .command = "TEST",
        .help = "Test COM console",
        .hint = NULL,
        .func = &cmd_AT,
    };

    esp_console_cmd_t scan_cmd = {
        .command = "SCAN",
        .help = "Lance un scan UDP broadcast",
        .hint = NULL,
        .func = &cmd_scan,
    };

    esp_console_cmd_t help_cmd = {
        .command = "HELP",
        .help = "Affiche les commandes disponibles",
        .hint = NULL,
        .func = &cmd_help,
    };

    esp_console_cmd_t MACcmd = {
        .command = "MAC",
        .help = "Affiche @ MAC",
        .hint = NULL,
        .func = &cmd_getMAC,
    };   

    esp_console_cmd_t ipEthInfo_cmd = {
        .command = "IP_ETH_INFO",
        .help = "Affiche @IP + submask + gateway interface Ethernet",
        .hint = NULL,
        .func = &cmd_get_eth_IP_Info,
    };

    esp_console_cmd_t ipWifiInfo_cmd = {
        .command = "IP_WIFI_INFO",
        .help = "Affiche @IP + submask + gateway interface Wifi",
        .hint = NULL,
        .func = &cmd_getWIFI_Info,
    };

    esp_console_cmd_t ping_cmd = {
        .command = "PING",
        .help = "Ping IP ETHERNET",
        .hint = "<ip>",
        .func = &cmd_ping,
    };

    esp_console_cmd_t reboot_cmd = {
        .command = "REBOOT",
        .help = "Reboot CPU",
        .hint = NULL,
        .func = &cmd_reboot,
    };

    esp_console_cmd_t setIP_cmd = {
        .command = "SET_IP_ETH",
        .help = "SET_IP <IP> <MASK>",
        .hint = "<IP> <MASK>" ,
        .func = &cmd_set_eth_ip,
    };

    esp_console_cmd_t setWifi_cmd = {
        .command = "SET_IP_WIFI",
        .help = "SET_IP <IP> <MASK>",
        .hint = "<IP> <MASK>" ,
        .func = &cmd_set_wifi_ip,
    };



    ESP_ERROR_CHECK(esp_console_cmd_register(&scan_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&help_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&MACcmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&ipEthInfo_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&ipWifiInfo_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&ping_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&reboot_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&setIP_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&setWifi_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&AT_cmd));

}


void console_init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    esp_console_config_t console_config = {
        .max_cmdline_length = 256,
        .max_cmdline_args = 8,
    };

    ESP_ERROR_CHECK(esp_console_init(&console_config));

    linenoiseSetMultiLine(1);
    linenoiseHistorySetMaxLen(20);

    save_commands();
}

// ==========================
// Commandes AT
// ==========================

int cmd_help(int argc, char **argv)
{
    printf(
        "\nCommandes disponibles:\n"
        "  AT            Test commande\n"
        "  SCAN          Lance un scan UDP broadcast\n"
        "  HELP          Affiche cette aide\n"
        "  IP_ETH_INFO   Affiche Config IP Ethernet\n"
        "  IP_WIFI_INFO  Affiche Config Wif\n"
        "  MAC           Affiche @MAC\n"
        "  SET_IP_ETH    Modifie config IP ethernet en statique\n"
        "  SET_IP_WIFI   Modifie config IP Wifi en statique\n"
        "  REBOOT        Reboot ESP\n"
        "  PING          Ping vers l'adresse donnée\n"
            
    );
    return 0;
}

int cmd_AT(int arc, char **argv)
{
    ESP_LOGI(TAG_PROMPT, "OK");
    return 0;
}

int cmd_scan(int argc, char **argv)
{
    ESP_LOGI(TAG_PROMPT, "SCAN -> UDP broadcast SCAN");
    udp_broadcast_send("dhs 1 get-info");
    return 0;
}

int cmd_getMAC(int argc, char **argvc)
{
    uint8_t mac[6];
    esp_netif_t *netif_mac = esp_netif_get_handle_from_ifkey("ETH_DEF");
    
    ESP_ERROR_CHECK(esp_netif_get_mac(netif_mac, mac));

    ESP_LOGI(TAG_PROMPT, "MAC Ethernet : %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return 0;
}

int cmd_get_eth_IP_Info(int agrc, char **argvc)
{
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("ETH_DEF");
    if (!netif) {
        ESP_LOGE(TAG_PROMPT, "Interface ETH introuvable");
        return 1;
    }
    
    esp_netif_ip_info_t ip;
    
    if (esp_netif_get_ip_info(netif, &ip) != ESP_OK) {
        ESP_LOGE(TAG_PROMPT, "Impossible de lire IP");
        return 1;
    }

    ESP_LOGI(TAG_PROMPT, "===== CONFIG IP ETHERNET =====");
    ESP_LOGI(TAG_PROMPT, "IP       : " IPSTR, IP2STR(&ip.ip));
    ESP_LOGI(TAG_PROMPT, "Masque   : " IPSTR, IP2STR(&ip.netmask));
    ESP_LOGI(TAG_PROMPT, "Gateway  : " IPSTR, IP2STR(&ip.gw));

    return 0;
}

int cmd_getWIFI_Info(int argc, char **argvc)
{
    if (argc != 1) {
        ESP_LOGI(TAG_PROMPT,"Commande inconnue");
        return 0;
    }

    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
    if (!netif) {
        ESP_LOGE(TAG_PROMPT, "Interface Wi-Fi introuvable");
        return 0;
    }

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(netif, &ip_info);

    ESP_LOGI(TAG_PROMPT, "===== CONFIG IP WIFI =====");
    ESP_LOGI(TAG_PROMPT, "Adresse IP  : %s", ip4addr_ntoa(&ip_info.ip));
    ESP_LOGI(TAG_PROMPT, "Masque      : %s", ip4addr_ntoa(&ip_info.netmask));
    ESP_LOGI(TAG_PROMPT, "Gateway     : %s", ip4addr_ntoa(&ip_info.gw));

    return 0;
}

int cmd_ping(int argc, char **argv)
{
    ESP_LOGI(TAG_PROMPT, "Ping vers adresse");

    if (argc != 2) {
        ESP_LOGI(TAG_PROMPT, "Usage: AT+PING x.x.x.x");
        return 0;
    }
    
    ping_ip(argv[1]);

    return 0;
}

int cmd_reboot(int argc, char **argv)
{
    ESP_LOGI(TAG_PROMPT, "Reboot....");
    vTaskDelay(pdMS_TO_TICKS(500));
    esp_restart();
    return 0;
}

int cmd_set_eth_ip(int argc, char **argv)
{ 
    if (argc != 3) {
        ESP_LOGI(TAG_PROMPT,"Usage:\n");
        ESP_LOGI(TAG_PROMPT,"SET_IP_ETH <IP> <MASK>\n");
        return 0;
    }

    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("ETH_DEF");
    if (!netif) {
        ESP_LOGE(TAG_PROMPT,"Interface ETH introuvable\n");
        return 0;
    }

    // Désactive DHCP
    ESP_ERROR_CHECK(esp_netif_dhcpc_stop(netif));
    ESP_LOGI(TAG_PROMPT,"Desactivation DHCP");

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(netif, &ip_info); // récupère l'IP, mask et gateway actuels


    if (!strcmp(argv[0], "SET_IP_ETH")) 
    {
        if (inet_pton(AF_INET, argv[1], &ip_info.ip.addr) != 1 || inet_pton(AF_INET, argv[2], &ip_info.netmask.addr) != 1) 
        {

            ESP_LOGE(TAG_PROMPT,"Format IP invalide\n");
            return 0;
        }

        ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip_info));

        ESP_LOGI(TAG_PROMPT, "--- Nouvelle config ethernet ---");
        ESP_LOGI(TAG_PROMPT, "IP     : %s", argv[1]);
        ESP_LOGI(TAG_PROMPT, "MASK   : %s", argv[2]);
    }
    else 
    {
        ESP_LOGE(TAG_PROMPT, "Commande inconnue\n");
    }

    return 0;
}

int cmd_set_wifi_ip(int argc, char **argv)
{
    if (argc != 3) {
        ESP_LOGI(TAG_PROMPT,"Usage: SET_IP_WIFI <IP> <MASK>");
        return 0;
    }

    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
    if (!netif) {
        ESP_LOGE(TAG_PROMPT,"Interface Wi-Fi introuvable");
        return 0;
    }

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(netif, &ip_info);

    if(!strcmp(argv[0], "SET_IP_WIFI"))
    {
        // Vérif état DHCP
        esp_netif_dhcp_status_t dhcp_status;
        esp_netif_dhcpc_get_status(netif, &dhcp_status);

        // TODO : Vérif status DHCP avant changement @IP

        ESP_ERROR_CHECK(esp_netif_dhcpc_stop(netif));

        if (inet_pton(AF_INET, argv[1], &ip_info.ip.addr) != 1 || inet_pton(AF_INET, argv[2], &ip_info.netmask.addr) != 1) 
        {
            ESP_LOGE(TAG_PROMPT,"Format IP invalide");
            return 0;
        } 
        
        ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip_info));

        ESP_LOGI(TAG_PROMPT,"--- Nouvelle config IP Wifi ---");
        ESP_LOGI(TAG_PROMPT,"Wi-Fi IP appliquée : %s", argv[1]);
        ESP_LOGI(TAG_PROMPT,"Subnet Mask : %s", argv[2]);
        ESP_LOGI(TAG_PROMPT,"Gateway : %s", ip4addr_ntoa((const ip4_addr_t*)&ip_info.gw));
    }
    else
    {
        ESP_LOGE(TAG_PROMPT, "Commande inconnue\n");
    }    

    return 0;
}

// ==========================
// Task console
// ==========================

void console_task(void *arg)
{
    char *line;

    ESP_LOGI(TAG_PROMPT, "---------- Prompt BODET Tool V1.0 ----------");
    ESP_LOGI(TAG_PROMPT, "   Commande HELP pour liste des commandes ");

    while (1) {
        line = linenoise("BodetTool> ");
        if (line == NULL) continue;

        int ret;
        esp_console_run(line, &ret);

        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}