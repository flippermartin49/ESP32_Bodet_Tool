#ifndef _RS485_H
#define _RS485_H

#include "driver/uart.h"
#include "driver/gpio.h"
#include "config.h"

#include "esp_log.h"

#define UART_NUM       UART_NUM_2
#define UART_TX_PIN    17
#define UART_RX_PIN    16
#define RS485_DE_PIN   4

#define UART_BUF_SIZE  256

void rs485_init(void);
void rs485_send(const uint8_t *data, size_t len);
int rs485_receive(uint8_t *buf, size_t max_len, TickType_t timeout);

void varsys_run_task(void *arg);


typedef struct {
    uint8_t data[50];
    size_t  len;
    uint8_t start_byte;
} varsys_frame_t;

extern varsys_frame_t handle_varsys;

typedef struct 
{
    char version[10]; 
    uint8_t board_number;
    uint8_t installation_number;
    map_scoreboard_e scoreboard;
    bool board_master;
    uint8_t luminosity;
    uint8_t coef_luminosity;
    bool board_btx;
    language_e board_language;
    bool modem_autoscan;
    uint8_t modem_canal; /* Canal de 1 a 6 */
    modem_network_e modem_network;
    uint16_t klaxon_time;
    mode_eco_e mode;
    uint16_t board_id;
    int8_t temperature_offset;
    bool mode_config;
    bool autonomous;
}config_t;

extern config_t config;


#define VARSYS_VIDEOSPORT_DEBUT_TRAME   0x20
#define VARSYS_POCKET_DEBUT_TRAME       0x02
#define VARSYS_DATA_DEBUT_TRAME         0x12

#define VARSYS_FIN_TRAME_EOD            0x04

#define VARSYS_UART_RX_BUFFER_SIZE      256





#endif