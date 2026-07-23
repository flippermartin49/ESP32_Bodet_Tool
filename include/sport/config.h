#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>

// Sur board ESP32-Ethernet-Kit V1.2
#define UART_TX_PIN    GPIO_NUM_33
#define UART_RX_PIN    GPIO_NUM_32
#define RS485_DE_PIN   GPIO_NUM_4

// Connecteur MOXA 3(D+) et 4(D-)

#define UART_BUF_SIZE  256

#define SOF                 0x30
#define END_FRAME           0x04

#define DEFAULT_DEST_ID     0x0000
#define DEFAULT_FROM_ID     0xFFFF


typedef enum {
    RX_WAIT_SOF,
    RX_HEADER,
    RX_DATA,
    RX_CRC,
    RX_EOF
}rx_state_t;

typedef struct {
    rx_state_t state;
    uint8_t buffer[UART_BUF_SIZE];
    uint16_t index;
    uint8_t data_len;
    uint16_t crc_rx;
}rx_parser_t;

typedef enum {
    NETWORK_OUTDOOR,
    NETWORK_INDOOR,
    NB_NETWORK,
} modem_network_e;

typedef enum {
    LANGUAGE_FRENCH,                                                                                                                           \
    LANGUAGE_ENGLISH,                                                                                                                           \
    LANGUAGE_GERMAN,                                                                                                                               \
    LANGUAGE_SPANISH,                                                                                                                             \
    LANGUAGE_DANISH,
}language_e;

typedef enum{
    MODE_NO_ECO,   /* Tout allume */                                                                                                               \
    MODE_SEMI_ECO, /* Mode eco, eteint entre 0 et 6h */                                                                                            \
    MODE_ECO,      /* Tout arrete */
}mode_eco_e;

// structure de la trame de configuration
typedef struct {
    uint8_t sof;
    uint8_t firstCmd;
    uint8_t secondCmd;
    uint16_t fromId;
    uint16_t destId;
    uint8_t dataLen;
    uint8_t data[256];
    uint16_t crc;
    uint8_t eof;
}config_trame_t;

extern config_trame_t config_trame;
 

// General config command
// 1er octet
#define CFG_CMD                    0x00
// 2nd octet
#define CFG_CMD_ACK                0x01 //Lors d'un acquittement les deux premiers octets contiennent forc�ment la commande re�u
#define CFG_CMD_NACK               0x02
#define CFG_CMD_ENTER              0x03
#define CFG_CMD_EXIT               0x04
#define CFG_CMD_ALIVE              0x05

/*******************************/
/*  COMMANDES DE CONFIGURATION */
/*******************************/
// 1er octet
#define CFG_CMD_CONFIG             0x10

// 2nd octet
#define CFG_CMD_SET_DEFAULT_CFG    0x01
#define CFG_CMD_SET_CONFIG_BOARD   0x02 //Si on ne veut pas changer une partie de la config on envoie des 0xFF � la place des datas
#define CFG_CMD_GET_CONFIG_BOARD   0x03
#define CFG_CMD_SET_CONFIG_PARAM   0x04
#define CFG_CMD_GET_CONFIG_PARAM   0x05
#define CFG_CMD_SET_CONFIG_MODEM   0x06
#define CFG_CMD_GET_CONFIG_MODEM   0x07
#define CFG_CMD_GET_MODEM_VER      0x08
#define CFG_CMD_GET_BOARD_VER      0x09
#define CFG_CMD_LOCALISATION       0x10
#define CFG_CMD_RESET              0x11

/*******************************/
/*      COMMANDES DE TEST      */
/*******************************/

// OTA firmware update download command
#define CFG_CMD_FW_UPDATE          0x30
#define CFG_CMD_FW_UPDATE_START    0x00

// Test board command
// 1er octet
#define CFG_CMD_TEST               0x40
// 2nd octet
#define CFG_CMD_TEST_START         0x00
#define CFG_CMD_TEST_CHANGE_MODE   0x01
#define CFG_CMD_TEST_FLUSH_LINE    0x02
#define CFG_CMD_TEST_CLEAN_LINE    0x03
#define CFG_CMD_TEST_SET_OPTIONS   0x04

/**************************************/
/*      COMMANDES DE RECENSEMENT      */
/**************************************/

// Recensement command
#define CFG_CMD_RCST               0x20

#define CFG_CMD_RCST_START         0x00 //Début du recensement
#define CFG_CMD_RCST_STOP          0x01 //Arret du recesement
#define CFG_CMD_RCST_ANSW          0x02 //Demande de recenssement de la carte suite au demarrage du recensement
#define CFG_CMD_RCST_OK            0x03 //Reponse OK du pupitre
#define CFG_CMD_RCST_NOK           0x04 //Reponse NOK du pupitre
#define CFG_CMD_RCST_VERIF         0x05 //Demande de verification de la part du pupitre

/* Liste Gamme LEGACY */
#define MAP_SCOREBOARD_LEGACY_LIST                                                              \
    X(0, MAP_SCOREBOARD_FULL_USINE)                                                            \
    X(1, MAP_SCOREBOARD_BT6025)                                                                    \
    X(2, MAP_SCOREBOARD_BT6120)                                                                    \
    X(3, MAP_SCOREBOARD_BT6102M)                                                                               \
    X(4, MAP_SCOREBOARD_BT6103_LEFT)                                                                       \
    X(5, MAP_SCOREBOARD_BT6103_RIGHT)                                                                     \
    X(6, MAP_SCOREBOARD_BT6020)                                                                    \
    X(7, MAP_SCOREBOARD_BT6107_LEFT)                                                                       \
    X(8, MAP_SCOREBOARD_BT6107_RIGHT)                                                                     \
    X(9, MAP_SCOREBOARD_BT6002_BT6006_BT6008)                                                     \
    X(10, MAP_SCOREBOARD_BT6102E)                                                                              \
    X(11, MAP_SCOREBOARD_BT6104_LEFT)                                                                      \
    X(12, MAP_SCOREBOARD_BT6104_RIGHT)                                                                    \
    X(13, MAP_SCOREBOARD_BT6015)                                                                   \
    X(14, MAP_SCOREBOARD_BT6030)                                                                   \
    X(15, MAP_SCOREBOARD_POSSESSION_AUTONOMOUS) /* Pupitre possession en mode autonome */         \
    X(16, MAP_SCOREBOARD_BT2000_ALPHA_16x64)                                                    \
    X(17, MAP_SCOREBOARD_BT2000_ALPHA_24x80)                                                    \
    X(19, MAP_SCOREBOARD_BTX6015_XTREM)                                                                        \
    X(21, MAP_SCOREBOARD_BT2000_SCORE)                                                                  \
    X(22, MAP_SCOREBOARD_BT2000_CLUB)                                                                      \
    X(23, MAP_SCOREBOARD_BT2000_CLASSIC)                                                                \
    X(25, MAP_SCOREBOARD_BT6015_ECO)                                                              \
    X(27, MAP_SCOREBOARD_BT6107_16P_LEFT)                                                         \
    X(28, MAP_SCOREBOARD_BT6107_16P_RIGHT)

    /* Liste Gamme PROD */
#define MAP_SCOREBOARD_PROD_LIST                                                                   \
    X(50, MAP_SCOREBOARD_BT2025_CLUB)                                                                      \
    X(51, MAP_SCOREBOARD_BT2025_CLASSIC)                                                        \
    X(52, MAP_SCOREBOARD_BT2025P_CLASSIC)                                                               \
    X(53, MAP_SCOREBOARD_BT2045_CLASSIC)                                                                \
    X(54, MAP_SCOREBOARD_BT2045_ALPHA)                                                          \
    X(55, MAP_SCOREBOARD_BT2045_CLUB)                                                                      \
    X(56, MAP_SCOREBOARD_8006_6008)                                                                          \
    X(57, MAP_SCOREBOARD_BT6015_COMPACT_PB)                                                       \
    X(58, MAP_SCOREBOARD_BT6015_COMPACT)                                                          \
    X(59, MAP_SCOREBOARD_BT6030_ALPHA)                                                          \
    X(60, MAP_SCOREBOARD_BT6130_ALPHA)                                                          \
    X(61, MAP_SCOREBOARD_BT6330_ALPHA)                                                          \
    X(62, MAP_SCOREBOARD_BT6530_ALPHA)                                                          \
    X(63, MAP_SCOREBOARD_BT6730_ALPHA_H10)                                                      \
    X(64, MAP_SCOREBOARD_BT6730_ALPHA_H10_VIDEO)                                         \
    X(65, MAP_SCOREBOARD_BT6730_ALPHA_H15)                                                     \
    X(66, MAP_SCOREBOARD_BT6730_ALPHA_H15_VIDEO)                                         \
    X(67, MAP_SCOREBOARD_BT6730_ALPHA_H10_16P)                                                 \
    X(68, MAP_SCOREBOARD_BT6730_ALPHA_H10_16P_VIDEO)                                            \
    X(69, MAP_SCOREBOARD_BT6730_ALPHA_H15_16P)                                                 \
    X(70, MAP_SCOREBOARD_BT6730_ALPHA_H15_16P_VIDEO)                                           \
    X(71, MAP_SCOREBOARD_BTX6002_3x3)                                                                          \
    X(72, MAP_SCOREBOARD_BTX6015)                                                                              \
    X(73, MAP_SCOREBOARD_BTX6120_WP)                                                                        \
    X(74, MAP_SCOREBOARD_BTX6220_WP)                                                           \
    X(75, MAP_SCOREBOARD_BTX6025_MS)                                                                        \
    X(76, MAP_SCOREBOARD_BTX6125_MS)                                                                        \
    X(77, MAP_SCOREBOARD_BTX6125_HK)                                                                        \
    X(78, MAP_SCOREBOARD_BTX6425_HK)                                                           \
    X(79, MAP_SCOREBOARD_TEMOIN_BUT)                                                                        \
    X(80, MAP_SCOREBOARD_BTX6002_WPLE)                                                                         \
    X(81, MAP_SCOREBOARD_BTX6002_RH_HOME)                                                                      \
    X(82, MAP_SCOREBOARD_BTX6002_RH_GUEST)                                                                     \
    X(83, MAP_SCOREBOARD_BTX6002)                                                                              \
    X(84, MAP_SCOREBOARD_REPETITEUR_WP)                                                              \
    X(85, MAP_SCOREBOARD_ENS_SIRENE_VIDEO)                                                                        \
    X(86, MAP_SCOREBOARD_KLAXON_ADD_24S)                                                                     \
    X(87, MAP_SCOREBOARD_KLAXON_ADD_FP)                                                                           \
    X(88, MAP_SCOREBOARD_BTX8020_SET)                                                                      \
    X(90, MAP_SCOREBOARD_8T215)                                                                     \
    X(91, MAP_SCOREBOARD_8015_F6)                                                                 \
    X(92, MAP_SCOREBOARD_8T215_F6)                                                               \
    X(93, MAP_SCOREBOARD_8020)                                                                       \
    X(94, MAP_SCOREBOARD_8T120)                                                                     \
    X(95, MAP_SCOREBOARD_8T120_SOLO)                                                                \
    X(96, MAP_SCOREBOARD_8T120_F6)                                                               \
    X(97, MAP_SCOREBOARD_8T220)                                                                     \
    X(98, MAP_SCOREBOARD_8NT220)                                                                   \
    X(99, MAP_SCOREBOARD_8NT220_F10)                                                           \
    X(100, MAP_SCOREBOARD_8025)                                                                      \
    X(101, MAP_SCOREBOARD_8025_F6)                                                                \
    X(102, MAP_SCOREBOARD_8T125)                                                                    \
    X(103, MAP_SCOREBOARD_8T125_F6)                                                              \
    X(104, MAP_SCOREBOARD_8T125_F10)                                                             \
    X(105, MAP_SCOREBOARD_8T225)                                                                    \
    X(106, MAP_SCOREBOARD_8NT325)                                                                  \
    X(107, MAP_SCOREBOARD_8NT325_F10)                                                          \
    X(108, MAP_SCOREBOARD_8NT325_FS10)                                                        \
    X(109, MAP_SCOREBOARD_8T225_F10)                                                            \
    X(110, MAP_SCOREBOARD_8T225_FS10)                                                          \
    X(111, MAP_SCOREBOARD_8006_SF)                                                                           \
    X(112, MAP_SCOREBOARD_8006_DF)                                                                           \
    X(113, MAP_SCOREBOARD_8002)                                                                                   \
    X(114, MAP_SCOREBOARD_REPETITEUR_CHR_SCR)                                                            \
    X(115, MAP_SCOREBOARD_REPETITEUR_CHR)                                                                \
    X(116, MAP_SCOREBOARD_AFFICHEUR_FAUTES)                                                                  \
    X(117, MAP_SCOREBOARD_BT8000_TEST) /*A supprimer � terme */

#define X(num, id) id = num,

typedef enum {
    MAP_SCOREBOARD_LEGACY_LIST                                                                                                                                \
    MAP_SCOREBOARD_PROD_LIST            
    UNKNOWN_BOARD
} map_scoreboard_e;

#undef X

#define MAX_DEVICES_RS485 8

// Structure avec les paramètres de configuration
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
    modem_network_e modem_network; /* INDOOR ou OUTDOOR*/
    uint16_t klaxon_time;
    mode_eco_e mode;
    uint16_t board_id;
    int8_t temperature_offset;
    bool mode_config;
    bool autonomous;
}config_device_t;

bool add_device(config_trame_t frame_config_rx);
const config_device_t *rs485_get_devices(void);
void device_sport_to_json(char *out, size_t len);
void LOG_DEVICE(void);


void config_init(void);
void enter_mode_config(void);
void exit_mode_config(void);

/**
 * @brief Remet la carte en config usine
 * @return CFG_CMD_ACK 0x0001
 */
 void set_default_config(void);

/**
 * @brief Permet de lancer l'affichage du panneau en mode test (full noir)
 * @return CFG_CMD_ACK 0x0001
 */
void mode_test_start(void);

/**
 * @brief La carte renvoi ses paramètres tableau
 * 
 * @param uint16_t destID : identifiant du destinataire
 * 
 * @return CFG_CMD_ACK 0x0001 avec data :
 *      - Numéro de panneau (1 byte) de 1 à 6
 *      - N° installation   (1 byte) de 1 à 6
 *      - Type de panneau   (1 byte) Numéro dans la liste de map
 *      - Maitre ou esclave (1 byte) 0 : esclave ou 1 : maître
 *      - Mode autonome     (1 byte) 1 : autonome ou 0 sinon
 */
void get_config_board(uint16_t destID);

/**
 * @brief La carte renvoi la configuration actuelle de la carte
 * 
 */
void get_config_param(void);

/**
 * @brief Get the config modem object
 * 
 */
void get_config_modem(void);

/**
 * @brief Get the modem version object
 * 
 */
void get_modem_version(void);

/**
 * @brief Get the board version object
 * 
 */
void get_board_version(void);

/**
 * @brief La carte allume tout les digits ainsi que son klaxon pour etre repérable
 * 
 */
void get_localisation(uint16_t destID);

/**
 * @brief La carte RESET
 * @return CFG_CMD_ACK 0x0001
 */
void send_reset(uint16_t destID);

/*******************/
/**   MODE TEST   **/
/*******************/

typedef enum {
    TEST_MODE_VIDE,
    TEST_AUTO_CLASSIQUE,
    TEST_FULL,
    TEST_LIGNE_BY_LIGNE,
}mode_test_e;


/**
 * @brief Lancement du mode test, à lancer avant toute autre commande de test
 * 
 */

void enter_mode_test(void);

/**
 * @brief permet de changer entre les différents modes de test
 * 
 * @param mode : Choix entre les 4 modes
 * @return true : ACK reçu de la carte après envoi trame
 * @return false : NACK reçu de la carte
 */
bool test_mode_change(mode_test_e mode);


const config_device_t *get_devices(void);
uint16_t calcul_CRC16(uint8_t *data, size_t len);
esp_err_t rs485_send_frame(config_trame_t *trame);

void rs485_receive_task(void *arg);
void config_task(void *arg);

bool parser_process(rx_parser_t *p, uint8_t byte, config_trame_t *frame);

void send_command_recensement();
void send_ok_recensement(uint16_t id);

#endif