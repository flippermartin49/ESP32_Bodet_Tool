#ifndef _CONFIG_H_
#define _CONFIG_H_

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

typedef struct {
    uint8_t sof;
    uint16_t cmd;
    uint16_t fromId;
    uint16_t destId;
    uint8_t dataLen;
    uint8_t* data;
    uint16_t crc;
    uint8_t eof;
} config_trame_t;

void config_init(void);
uint8_t send_command_config(config_trame_t trame); 

// General config command
#define CFG_CMD                    0x0000
#define CFG_CMD_ACK                0x0001 //Lors d'un acquittement les deux premiers octets contiennent forc�ment la commande re�u
#define CFG_CMD_NACK               0x0002
#define CFG_CMD_ENTER              0x0003
#define CFG_CMD_EXIT               0x0004
#define CFG_CMD_ALIVE              0x0005

/*******************************/
/*  COMMANDES DE CONFIGURATION */
/*******************************/

#define CFG_CMD_CONFIG             0x10
#define CFG_CMD_SET_DEFAULT_CFG    0x1001
#define CFG_CMD_SET_CONFIG_BOARD   0x1002 //Si on ne veut pas changer une partie de la config on envoie des 0xFF � la place des datas
#define CFG_CMD_GET_CONFIG_BOARD   0x1003
#define CFG_CMD_SET_CONFIG_PARAM   0x1004
#define CFG_CMD_GET_CONFIG_PARAM   0x1005
#define CFG_CMD_SET_CONFIG_MODEM   0x1006
#define CFG_CMD_GET_CONFIG_MODEM   0x1007
#define CFG_CMD_GET_MODEM_VER      0x1008
#define CFG_CMD_GET_BOARD_VER      0x1009
#define CFG_CMD_LOCALISATION       0x1010
#define CFG_CMD_RESET              0x1011

/*******************************/
/*      COMMANDES DE TEST      */
/*******************************/

// OTA firmware update download command
#define CFG_CMD_FW_UPDATE          0x30
#define CFG_CMD_FW_UPDATE_START    0x3000

// Test board command
#define CFG_CMD_TEST               0x40
#define CFG_CMD_TEST_START         0x4000
#define CFG_CMD_TEST_CHANGE_MODE   0x4001
#define CFG_CMD_TEST_FLUSH_LINE    0x4002
#define CFG_CMD_TEST_CLEAN_LINE    0x4003
#define CFG_CMD_TEST_SET_OPTIONS   0x4004

/**************************************/
/*      COMMANDES DE RECENSEMENT      */
/**************************************/

// Recensement command
#define CFG_CMD_RCST               0x20
#define CFG_CMD_RCST_START         0x2000 //D�but du recensement
#define CFG_CMD_RCST_STOP          0x2001 //Arr�t du recesement
#define CFG_CMD_RCST_ANSW          0x2002 //Demande de recenssement de la carte suite au d�marrage du resencement
#define CFG_CMD_RCST_OK            0x2003 //R�ponse OK du pupitre
#define CFG_CMD_RCST_NOK           0x2004 //R�ponse NOK du pupitre
#define CFG_CMD_RCST_VERIF         0x2005 //Demande de v�rification de la part du pupitre

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


#endif