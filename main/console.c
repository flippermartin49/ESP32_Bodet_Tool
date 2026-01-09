#include "../include/console.h"

static const char *TAG_PROMPT = "CONSOLE";


// ==========================
// Enregistrement commandes
// ==========================

void save_commands(void)
{
    esp_console_cmd_t scan_cmd = {
        .command = "AT+SCAN",
        .help = "Lance un scan UDP broadcast",
        .hint = NULL,
        .func = &cmd_scan,
    };

    esp_console_cmd_t help_cmd = {
        .command = "AT+HELP",
        .help = "Affiche les commandes disponibles",
        .hint = NULL,
        .func = &cmd_help,
    };

    esp_console_cmd_t MACcmd = {
        .command = "AT+MAC",
        .help = "Affiche @ MAC",
        .hint = NULL,
        .func = &cmd_getMAC,
    };   

    esp_console_cmd_t ipEthInfo_cmd = {
        .command = "AT+IP_ETH_INFO",
        .help = "Affiche @IP + submask + gateway",
        .hint = NULL,
        .func = &cmd_getIP_Info,
    };

    esp_console_cmd_t ping_cmd = {
        .command = "AT+PING=",
        .help = "Ping IP ETHERNET",
        .hint = "<ip>",
        .func = &cmd_ping,
    };

    esp_console_cmd_t reboot_cmd = {
        .command = "AT+REBOOT",
        .help = "Reboot CPU",
        .hint = NULL,
        .func = &cmd_reboot,
    };


    ESP_ERROR_CHECK(esp_console_cmd_register(&scan_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&help_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&MACcmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&ipEthInfo_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&ping_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&reboot_cmd));
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

int cmd_scan(int argc, char **argv)
{
    ESP_LOGI(TAG_PROMPT, "AT+SCAN -> UDP broadcast SCAN");
    udp_broadcast_send();
    return 0;
}

int cmd_help(int argc, char **argv)
{
    printf(
        "\nCommandes disponibles:\n"
        "  AT+SCAN          Lance un scan UDP broadcast\n"
        "  AT+HELP          Affiche cette aide\n"
        "  AT+IP_ETH_INFO   Affiche Config IP Ethernet\n"
        "  AT+MAC           Affiche @MAC\n"
    );
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

int cmd_getIP_Info(int agrc, char **argvc)
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

    ESP_LOGI(TAG_PROMPT, "===== CONFIG IP =====");
    ESP_LOGI(TAG_PROMPT, "IP       : " IPSTR, IP2STR(&ip.ip));
    ESP_LOGI(TAG_PROMPT, "Masque   : " IPSTR, IP2STR(&ip.netmask));
    ESP_LOGI(TAG_PROMPT, "Gateway  : " IPSTR, IP2STR(&ip.gw));

    return 0;
}

int cmd_ping(int argc, char **argv)
{
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


// ==========================
// Task console
// ==========================

void console_task(void *arg)
{
    char *line;

    ESP_LOGI(TAG_PROMPT, "---------- Prompt BODET Tool V1.0 ----------");

    while (1) {
        line = linenoise("BodetTool> ");
        if (line == NULL) continue;

        int ret;
        esp_console_run(line, &ret);

        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}