#include "../include/console.h"


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

    ESP_ERROR_CHECK(esp_console_cmd_register(&scan_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&help_cmd));
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

static int cmd_scan(int argc, char **argv)
{
    ESP_LOGI(TAG, "AT+SCAN -> UDP broadcast");
    udp_broadcast_send();
    return 0;
}

static int cmd_help(int argc, char **argv)
{
    printf(
        "\nCommandes disponibles:\n"
        "  AT+SCAN        Lance un scan UDP broadcast\n"
        "  AT+HELP        Affiche cette aide\n\n"
    );
    return 0;
}


// ==========================
// Task console
// ==========================

void console_task(void *arg)
{
    char *line;

    ESP_LOGI(TAG, "Console prête");

    while (1) {
        line = linenoise("ESP32> ");
        if (line == NULL) continue;

        int ret;
        esp_console_run(line, &ret);

        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}