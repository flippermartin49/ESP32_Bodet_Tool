#include "../../include/sport/config.h"

static const char *TAG_RS485 = "RS485";
static const char *TAG_CONFIG = "CONFIG";

QueueHandle_t cfg_rx_queue;

// tableau contenant les devices détectés
static config_device_t devices[MAX_DEVICES_RS485];
static uint8_t nb_devices = 0;

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
    ESP_LOGI(TAG_RS485, "TX pin = %d, RX pin = %d", UART_TX_PIN, UART_RX_PIN);

    cfg_rx_queue = xQueueCreate(10, sizeof(config_trame_t));

}

esp_err_t rs485_send_frame(config_trame_t *trame)
{
    uint8_t buffer[UART_BUF_SIZE];
    size_t pos = 0;

    if (trame == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if (pos + trame->dataLen + 3 > sizeof(buffer))
    {
        return ESP_ERR_INVALID_SIZE;
    }

    buffer[pos++] = trame->sof;
    buffer[pos++] = trame->firstCmd;
    buffer[pos++] = trame->secondCmd;

    buffer[pos++] = trame->fromId >> 8;
    buffer[pos++] = trame->fromId & 0xFF;

    buffer[pos++] = trame->destId >> 8;
    buffer[pos++] = trame->destId & 0xFF;

    buffer[pos++] = trame->dataLen;

    if (trame->dataLen)
    {
        memcpy(&buffer[pos], trame->data, trame->dataLen);
        pos += trame->dataLen;
    }

    trame->crc = calcul_CRC16(&buffer[1], pos - 1);

    buffer[pos++] = trame->crc >> 8;
    buffer[pos++] = trame->crc & 0xFF;
    

    buffer[pos++] = trame->eof;

    /* ===========================
     * Affichage de la trame
     * =========================== */

    char log_buffer[UART_BUF_SIZE * 3 + 1];
    size_t log_pos = 0;

    for (size_t i = 0; i < pos; i++)
    {
        log_pos += snprintf(&log_buffer[log_pos], sizeof(log_buffer) - log_pos, "%02X ", buffer[i]);
    }

    ESP_LOGI(TAG_RS485, "TX (%u octets): %s", (unsigned)pos, log_buffer);

    gpio_set_level(RS485_DE_PIN, 1);   // émission
    uart_write_bytes(UART_NUM_2, buffer, pos);
    uart_wait_tx_done(UART_NUM_2, pdMS_TO_TICKS(200));
    gpio_set_level(RS485_DE_PIN, 0);   // retour réception


    return ESP_OK;

}


void rs485_receive_task(void *arg)
{
    uint8_t rx[UART_BUF_SIZE];

    config_trame_t config_frame_rx;

    rx_parser_t parser = {0};
    parser.state = RX_WAIT_SOF;
    parser.index = 0;
    parser.data_len = 0;

    while(1)
    {
        int len = uart_read_bytes(UART_NUM_2, rx, sizeof(rx), pdMS_TO_TICKS(100));
        //ESP_LOG_BUFFER_HEX("RX_RAW", rx, len);

        for(int i = 0; i < len; i++)
        {
            if(parser_process(&parser, rx[i], &config_frame_rx))
            {
                xQueueSend(cfg_rx_queue, &config_frame_rx, portMAX_DELAY);

                ESP_LOGI(TAG_RS485, "1_CMD=0x%02X 2_CMD=0x%02X FROM=0x%04X DEST=%04X LEN_DATA=%u", 
                config_frame_rx.firstCmd, config_frame_rx.secondCmd, config_frame_rx.fromId, config_frame_rx.destId, config_frame_rx.dataLen);
                
            }
        }
    }
}

bool parser_process(rx_parser_t *p, uint8_t byte, config_trame_t *frame)
{
    switch(p->state)
    {
        case RX_WAIT_SOF:

            if(byte == 0x30)
            {
                p->index = 0;
                p->buffer[p->index++] = byte;
                p->state = RX_HEADER;
            }
            break;

        case RX_HEADER:
            
            p->buffer[p->index++] = byte;
            if(p->index == 8)
            {
                p->data_len = p->buffer[7];
                
                if(p->data_len == 0)
                    p->state = RX_CRC;
                else 
                    p->state = RX_DATA;
            }

            break;

        case RX_DATA:
            p->buffer[p->index++] = byte;
            
            if(p->index == (8 + p->data_len + 2))
                p->state = RX_EOF;

            break;

        case RX_CRC:
            p->buffer[p->index++] = byte;

            if(p->index == (8 + p->data_len + 2))
                p->state = RX_EOF;

            break;

        case RX_EOF:

            if(byte == 0x04)
            {
                p->buffer[p->index++] = byte;
                
                uint16_t crc_rx = ((uint16_t)p->buffer[8 + p->data_len] << 8) | p->buffer[8 + p->data_len + 1];

                uint16_t crc_calc = calcul_CRC16(&p->buffer[1], 7 + p->data_len);
                
                if(crc_rx == crc_calc)
                {
                    frame->firstCmd = p->buffer[1];
                    frame->secondCmd = p->buffer[2];

                    frame->fromId = ((uint16_t) p->buffer[3] << 8) | p->buffer[4];
                    frame->destId = ((uint16_t) p->buffer[5] << 8) | p->buffer[6];
                    frame->dataLen = p->buffer[7];

                    memcpy(frame->data, &p->buffer[8], frame->dataLen);
                    
                    p->state = RX_WAIT_SOF;
                    
                    return true;
                }

            }

            p->state = RX_WAIT_SOF;
            break;

    }

    return false;
}

uint16_t calcul_CRC16(uint8_t *data, size_t len)
{
    uint16_t crc = 0x0000;

    while(len--)
    {
        crc ^= ((uint16_t)*data++) << 8;

        for(uint8_t i = 0; i < 8; i++)
        {
            if(crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else 
                crc <<= 1;
        }
    }

    return crc;
}

void enter_mode_config()
{
    config_trame_t frame_enter_config =
    {
        .sof       = SOF,
        .firstCmd  = 0x00,
        .secondCmd = CFG_CMD_ENTER,
        .fromId    = 0x0000,
        .destId    = 0xFFFF,
        .dataLen   = 0,
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_enter_config));
    ESP_LOGI(TAG_CONFIG, "--> ENTER CONFIG MODE");

}

void exit_mode_config()
{
    config_trame_t frame_exit_config =
    {
        .sof       = SOF,
        .firstCmd  = 0x00,
        .secondCmd = CFG_CMD_EXIT,
        .fromId    = 0x0000,
        .destId    = 0xFFFF,
        .dataLen   = 0,
        .eof       = END_FRAME
    };
    ESP_ERROR_CHECK(rs485_send_frame(&frame_exit_config));
    ESP_LOGI(TAG_CONFIG, "--> EXIT CONFIG MODE");

}

void send_command_recensement()
{
    config_trame_t frame_rx;

    // RAZ liste device
    nb_devices = 0;
    memset(devices,0,sizeof(devices));

    config_trame_t frame_start_recensement =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_RCST,
        .secondCmd = CFG_CMD_RCST_START,
        .fromId    = 0x0000,
        .destId    = 0xFFFF,
        .dataLen   = 0,
        .eof       = END_FRAME
    };

    enter_mode_config();

    ESP_ERROR_CHECK(rs485_send_frame(&frame_start_recensement));
    ESP_LOGI(TAG_CONFIG, " -- > START RECENSEMENT");

    TickType_t start = xTaskGetTickCount();

    while ((xTaskGetTickCount() - start) < pdMS_TO_TICKS(3000))
    {

        if (xQueueReceive(cfg_rx_queue, &frame_rx, pdMS_TO_TICKS(200)) == pdTRUE)
        {
            if(frame_rx.firstCmd == CFG_CMD_RCST)
            {
                if(frame_rx.secondCmd == CFG_CMD_RCST_ANSW)
                {
                    ESP_LOGI(TAG_CONFIG, " --> Response queue receive");

                    if(add_device(frame_rx))
                    {
                        ESP_LOGI(TAG_CONFIG, "FOUND NEW ID : %04X", frame_rx.fromId);
                        ESP_LOG_BUFFER_HEX("DATA", frame_rx.data, frame_rx.dataLen);
                        //send_ok_recensement(frame_rx.fromId);
                    }
                }
            }
        }
    }   
        

    for (uint8_t i = 0; i < nb_devices; i++)
    {
        ESP_LOGI(TAG_CONFIG, "Equipement %d : ID = %04X", i, devices[i].board_id);
    }

    //exit_mode_config();

}

bool add_device(config_trame_t frame_config_rx)
{
    // Vérifie si l'ID existe déjà
    for (uint8_t i = 0; i < nb_devices; i++)
    {
        if (devices[i].board_id == frame_config_rx.fromId)
        {
            return false;    // Déjà connu
        }
    }

    // Vérifie qu'il reste de la place
    if (nb_devices >= MAX_DEVICES_RS485)
    {
        return false;
    }

    // Ajoute le nouvel ID
    devices[nb_devices].board_id = frame_config_rx.fromId;
    devices[nb_devices].installation_number = frame_config_rx.data[2];
    devices[nb_devices].board_number = frame_config_rx.data[3];
    devices[nb_devices].scoreboard = frame_config_rx.data[4];  // type de tableau En hexa, à convertir en décimal
    devices[nb_devices].version[0] = frame_config_rx.data[5];  // V
    devices[nb_devices].version[1] = frame_config_rx.data[6];  // 1
    devices[nb_devices].version[2] = frame_config_rx.data[7];  // .
    devices[nb_devices].version[3] = frame_config_rx.data[8];  // 1
    devices[nb_devices].version[4] = frame_config_rx.data[9];  // A
    devices[nb_devices].version[5] = frame_config_rx.data[10];  // 1
    devices[nb_devices].version[6] = frame_config_rx.data[11];  // 0
    
    ESP_LOGI(TAG_CONFIG, "DataLen = %d", frame_config_rx.dataLen);
    ESP_LOG_BUFFER_HEX(TAG_CONFIG, frame_config_rx.data, frame_config_rx.dataLen);

    LOG_DEVICE();

    nb_devices++;

    
    return true;
}

const config_device_t *get_devices(void)
{
    return devices;
}

void send_ok_recensement(uint16_t dest_id)
{

    config_trame_t frame_ok_recensement =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_RCST,
        .secondCmd = CFG_CMD_RCST_OK,
        .fromId    = 0x0000,
        .destId    = dest_id,
        .dataLen   = 2,
        .data      = {0x01, 0x00},
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_ok_recensement));
    ESP_LOGI(TAG_CONFIG, " Validaiton ID: %04X", dest_id);

}

void get_config_board(uint16_t destID)
{
    config_trame_t frame_config_board =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_CONFIG,
        .secondCmd = CFG_CMD_GET_CONFIG_BOARD,
        .fromId    = 0x0000,
        .destId    = destID,
        .dataLen   = 0,
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_config_board));
    ESP_LOGI(TAG_CONFIG, " -- > GET CONFIG BOARD");

}

void get_localisation(uint16_t destID)
{

     config_trame_t frame_localisation =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_CONFIG,
        .secondCmd = CFG_CMD_LOCALISATION,
        .fromId    = 0x0000,
        .destId    = destID,
        .dataLen   = 2,
        .data      = {0x01, 0x00},
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_localisation));
    ESP_LOGI(TAG_CONFIG, " -- > GET LOCALISATION");
}

void send_reset(uint16_t destID)
{
    config_trame_t frame_reset =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_CONFIG,
        .secondCmd = CFG_CMD_RESET,
        .fromId    = 0x0000,
        .destId    = destID,
        .dataLen   = 0,
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_reset));
    ESP_LOGI(TAG_CONFIG, " -- > RESET BOARD");
}

/*==================== MODE TEST =====================*/

void enter_mode_test(void)
{
    config_trame_t frame_reset =
    {
        .sof       = SOF,
        .firstCmd  = CFG_CMD_TEST,
        .secondCmd = CFG_CMD_TEST_START,
        .fromId    = 0x0000,
        .destId    = 0xFFFF,
        .dataLen   = 0,
        .eof       = END_FRAME
    };

    ESP_ERROR_CHECK(rs485_send_frame(&frame_reset));
    ESP_LOGI(TAG_CONFIG, " -- > ENTER TEST MODE");
}

bool test_mode_change(mode_test_e mode)
{
    

    return false;
}

void device_sport_to_json(char *out, size_t max_len)
{
    if (!out || max_len == 0) return;

    size_t used = 0;

    used += snprintf(out + used, max_len - used, "{ \"devices_sport\": [");

    for (uint8_t i = 0; i < nb_devices; i++)
    {
        config_device_t *d = &devices[i];

        used += snprintf(out + used, max_len - used,
            "{"
            "\"version\":\"%s\","
            "\"board_number\":%u,"
            "\"installation_number\":%u,"
            "\"scoreboard\":%u,"
            "\"board_master\":%d,"
            "\"luminosity\":%u,"
            "\"coef_luminosity\":%u,"
            "\"board_btx\":%d,"
            "\"language\":%u,"
            "\"modem_autoscan\":%d,"
            "\"modem_canal\":%u,"
            "\"modem_network\":%u,"
            "\"klaxon_time\":%u,"
            "\"mode\":%u,"
            "\"board_id\":%u,"
            "\"temperature_offset\":%d,"
            "\"mode_config\":%d,"
            "\"autonomous\":%d"
            "}",
            d->version,
            d->board_number,
            d->installation_number,
            d->scoreboard,
            d->board_master,
            d->luminosity,
            d->coef_luminosity,
            d->board_btx,
            d->board_language,
            d->modem_autoscan,
            d->modem_canal,
            d->modem_network,
            d->klaxon_time,
            d->mode,
            d->board_id,
            d->temperature_offset,
            d->mode_config,
            d->autonomous
        );

        if (i < nb_devices - 1)
        {
            used += snprintf(out + used, max_len - used, ",");
        }
    }

    snprintf(out + used, max_len - used, "] }");

    ESP_LOGI(TAG_CONFIG, "========== JSON ==========");
    ESP_LOGI(TAG_CONFIG, "%s", out);
    ESP_LOGI(TAG_CONFIG, "==========================");
}

void LOG_DEVICE(void)
{

    ESP_LOGI(TAG_CONFIG, "========== DEVICE %d ==========", nb_devices + 1);

    ESP_LOGI(TAG_CONFIG, "ID              : %04X", devices[nb_devices].board_id);
    ESP_LOGI(TAG_CONFIG, "Installation    : %u", devices[nb_devices].installation_number);
    ESP_LOGI(TAG_CONFIG, "Board           : %u", devices[nb_devices].board_number);
    ESP_LOGI(TAG_CONFIG, "Scoreboard      : %u", devices[nb_devices].scoreboard);
    ESP_LOGI(TAG_CONFIG, "Version         : %s", devices[nb_devices].version);

    ESP_LOGI(TAG_CONFIG, "Master          : %d", devices[nb_devices].board_master);
    ESP_LOGI(TAG_CONFIG, "Luminosity      : %u", devices[nb_devices].luminosity);
    ESP_LOGI(TAG_CONFIG, "Coef Lum        : %u", devices[nb_devices].coef_luminosity);
    ESP_LOGI(TAG_CONFIG, "BTX             : %d", devices[nb_devices].board_btx);
    ESP_LOGI(TAG_CONFIG, "Language        : %u", devices[nb_devices].board_language);
    ESP_LOGI(TAG_CONFIG, "Autoscan        : %d", devices[nb_devices].modem_autoscan);
    ESP_LOGI(TAG_CONFIG, "Canal modem     : %u", devices[nb_devices].modem_canal);
    ESP_LOGI(TAG_CONFIG, "Network modem   : %u", devices[nb_devices].modem_network);
    ESP_LOGI(TAG_CONFIG, "Klaxon          : %u", devices[nb_devices].klaxon_time);
    ESP_LOGI(TAG_CONFIG, "Mode            : %u", devices[nb_devices].mode);
    ESP_LOGI(TAG_CONFIG, "Temp offset     : %d", devices[nb_devices].temperature_offset);
    ESP_LOGI(TAG_CONFIG, "Mode config     : %d", devices[nb_devices].mode_config);
    ESP_LOGI(TAG_CONFIG, "Autonomous      : %d", devices[nb_devices].autonomous);

}