#include "RS485.h"

void rs485_init(void)
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
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(UART_NUM, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN,
                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void rs485_send(const uint8_t *data, size_t len)
{
    gpio_set_level(RS485_DE_PIN, 1);   // émission
    uart_write_bytes(UART_NUM, data, len);
    uart_wait_tx_done(UART_NUM, pdMS_TO_TICKS(100));
    gpio_set_level(RS485_DE_PIN, 0);   // retour réception
}

int rs485_receive(uint8_t *buf, size_t max_len, TickType_t timeout)
{
    return uart_read_bytes(UART_NUM, buf, max_len, timeout);
}


void varsys_run_task(void *arg)
{
    
    
    while(1)
    {
        
    }
}
