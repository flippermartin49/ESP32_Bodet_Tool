#include "varsys.h"

#define TAG "VARSYS"

esp_err_t varsys_decode_date(const uint8_t data[5], date_heure_t *dt)
{
    if(dt == NULL)
    {
        return ESP_ERR_INVALID_SIZE;
    }

    uint16_t year = ((data[0] >> 5) << 4) | (data[1] >> 4);
    
    dt->day = data[0] & 0x1F;
    dt->month = (data[1] & 0x0F) + 1; // le protocole commence à 0
    dt->year = 2000 + year;
    dt->hour = data[2] & 0x1F;
    dt->minute = data[3];
    dt->second = data[4];

    return ESP_OK;

}

esp_err_t varsys_encode_date(const date_heure_t *dt, uint8_t data[5])
{

    if(dt == NULL)
    {
        return ESP_ERR_INVALID_SIZE;
    }

    uint8_t year = dt->year % 100;

    data[0] = (dt->day & 0x1F) | (((year >> 4) & 0x07) << 5);
    data[1] = ((dt->month - 1) & 0x0F) | ((year & 0x0F) << 4);
    data[2] = dt->hour & 0x0F;
    data[3] = dt->minute;
    data[4] = dt->second;

    return ESP_OK;

}

esp_err_t varsys_send_date(const date_heure_t *dt, varsys_frame_t frame_varsys )
{
    
    // on vérifie les paramètres.
    if((dt == NULL))
        return ESP_ERR_INVALID_ARG;
    if(dt->day < 1 || dt->day > 31)
        return ESP_ERR_INVALID_ARG;
    if(dt->month < 1 || dt->month > 12)
        return ESP_ERR_INVALID_ARG;
    if(dt->hour > 23 || dt->minute || dt->second || dt->year > 99)
        return ESP_ERR_INVALID_ARG;
    
    uint8_t tx_buffer[VARSYS_DATA_PROTOCOLE_MAX_SIZE];
    size_t pos = 0;

    tx_buffer[pos++] = VARSYS_DATA_SOH;

    /* Premier octet liste de destinataire ==> non encodé*/
    tx_buffer[pos++] = frame_varsys.list_destinataire;

    

    tx_buffer[pos++] = VARSYS_DATA_EOD;


    // Envoi sur RS485
    gpio_set_level(RS485_DE_PIN, 1);   // émission
    uart_write_bytes(UART_NUM_2, tx_buffer, pos);
    uart_wait_tx_done(UART_NUM_2, pdMS_TO_TICKS(200));
    gpio_set_level(RS485_DE_PIN, 0);   // retour réception

    return ESP_OK;

}

esp_err_t varsys_calcul_crc16(uint8_t *data, uint16_t size)
{
    uint16_t crc = 0;

    for (uint16_t i = 0; i < size; i++)
    {
        crc ^= ((uint16_t) data[i] << 8);

        for(uint8_t j = 0; j < 8; j++)
        {
            if(crc & 0x8000)
                crc =(crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }

    }
    return crc;
}

