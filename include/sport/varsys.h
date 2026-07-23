#ifndef _VARSYS_H
#define _VARSYS_H

#include "config.h"
#include "varsys_enum.h"

#define VARSYS_DATA_SOH             0x12
#define VARSYS_DATA_EOD             0x04
#define VARSYS_VIDEOSPORT_SOH       0x20
#define VARSYS_POCKET_SOH           0x02

#define VARSYS_DATA_PROTOCOLE_MAX_SIZE 1024

#define MASK_LIST_DESTINATAIRE 0x3F
#define MASK_FAMILY            0x40
#define MASK_COS_RECIPIENT     0x40 // Codage sur l'octet suivant
#define MASK_COS_FIELD         0x80 // Codage sur l'octet suivant
#define MASK_RECIPIENT         0x07
#define MASK_SENDER            0x38
#define MASK_STORE_BYTE        0x80
#define MASK_FIELD             0x1F
#define MASK_FIELD_SIZE        0x60

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}date_heure_t;

typedef struct 
{
    uint8_t list_destinataire;
    varsys_data_correspondant_e destinataire;
    varsys_data_correspondant_e expediteur;
}varsys_frame_t;


esp_err_t varsys_decode_date(const uint8_t data[5], date_heure_t *dt);
esp_err_t varsys_encode_date(const date_heure_t *dt, uint8_t data[5]);
esp_err_t varsys_send_date(const date_heure_t *dt, varsys_frame_t frame_varsys );
esp_err_t varsys_calcul_crc16(uint8_t *data, uint16_t size);



#endif