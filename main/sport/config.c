#include "../../include/sport/config.h"

void config_init(void)
{
    // GPIO DE/RE
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << RS485_DE_PIN,
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);
    gpio_set_level(RS485_DE_PIN, 0); // réception par défaut

    // UART config
    uart_config_t uart_config = {
        .baud_rate = 9600,          // adapte selon ton bus
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, 1024, UART_BUF_SIZE, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_LOGI("[RS485]", "TX pin = %d, RX pin = %d", UART_TX_PIN, UART_RX_PIN);
}

void rs485_send(const uint8_t *data, size_t len)
{
    gpio_set_level(RS485_DE_PIN, 1);   // émission
    uart_write_bytes(UART_NUM, data, len);
    uart_wait_tx_done(UART_NUM, pdMS_TO_TICKS(200));
    gpio_set_level(RS485_DE_PIN, 0);   // retour réception
}

int rs485_receive(uint8_t *buf, size_t max_len, TickType_t timeout)
{
    return uart_read_bytes(UART_NUM, buf, max_len, timeout);
}

void enter_mode_config()
{
    uint8_t frame[] = {SOF, 0x00, CFG_CMD_ENTER, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x02, 0x7C, 0x04 };
    rs485_send(frame, 11);
}