#ifndef _VARSYS_DATA_ENUM_H__
#define _VARSYS_DATA_ENUM_H__

#define NB_CORRESPONDANT_MAX 6

#define VARSYS_DATA_CORRESPONDANT_LIST_IDENTIFIANT                                                                                                   \
    X(E_CORRESPONDANT_inconnu, 0)                                                                                                                    \
    X(E_CORRESPONDANT_pour_les_autres_GRL, 1)                                                                                                        \
    X(E_CORRESPONDANT_Administrateur, 2)                                                                                                             \
    X(E_CORRESPONDANT_quelconque, 3)                                                                                                                 \
    X(E_CORRESPONDANT_Config_n_4, 4)                                                                                                                 \
    X(E_CORRESPONDANT_GRL1, 5)                                                                                                                       \
    X(E_CORRESPONDANT_GRL2, 6)                                                                                                                       \
    X(E_CORRESPONDANT_GRL3, 7)                                                                                                                       \
    X(E_CORRESPONDANT_GRL4, 8)                                                                                                                       \
    X(E_CORRESPONDANT_GRL5, 9)                                                                                                                       \
    X(E_CORRESPONDANT_GRL6, 10)                                                                                                                      \
    X(E_CORRESPONDANT_Config_n_11, 11)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_12, 12)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_13, 13)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_14, 14)                                                                                                               \
    X(E_CORRESPONDANT_NA1, 15)                                                                                                                       \
    X(E_CORRESPONDANT_Config_n_16, 16)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_17, 17)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_18, 18)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_19, 19)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_20, 20)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_21, 21)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_22, 22)                                                                                                               \
    X(E_CORRESPONDANT_NP, 23)                                                                                                                        \
    X(E_CORRESPONDANT_Config_n_24, 24)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_25, 25)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_26, 26)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_27, 27)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_28, 28)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_29, 29)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_30, 30)                                                                                                               \
    X(E_CORRESPONDANT_Config_n_31, 31)                                                                                                               \
    X(E_CORRESPONDANT_QUELLE_HEURE, 32)                                                                                                              \
    X(E_CORRESPONDANT_Config_n_33, 33)                                                                                                               \
    X(E_CORRESPONDANT_GRL_presents, 34)

    #define X(id, value) id = value,

    typedef enum {
        VARSYS_DATA_CORRESPONDANT_LIST_IDENTIFIANT

            NB_CORRESPONDANT

    } varsys_data_correspondant_e;

    #undef X

    const char* varsys_data_correspondant_name(varsys_data_correspondant_e correspondant);

#define VARSYS_DATA_COMMAND_LIST                                                                                                                     \
    X(VARSYS_Message_systeme_Msb)                                                                                                                    \
    X(VARSYS_Message_systeme_Lsb)                                                                                                                    \
    X(VARSYS_Message_globale)                                                                                                                        \
    X(VARSYS_Page_1_Klaxons)                                                                                                                         \
    X(VARSYS_CHRONO_Afficheur_MS_DIZAINE) /* Page_1_Afficheur_1 */                                                                                   \
    X(VARSYS_CHRONO_Afficheur_MS_UNITE)   /* Page_1_Afficheur_2 */                                                                                   \
    X(VARSYS_FAULT_VIS)                   /* Page_1_Afficheur_3 */                                                                                   \
    X(VARSYS_SCORE_VIS_UNITE)             /* Page_1_Afficheur_4 */                                                                                   \
    X(VARSYS_SCORE_VIS_DIZAINE)           /* Page_1_Afficheur_5 */                                                                                   \
    X(VARSYS_SCORE_VIS_CENTAINE)          /* Page_1_Afficheur_6 */                                                                                   \
    X(VARSYS_CHRONO_Afficheur_HM_UNITE)   /* Page_1_Afficheur_7 */                                                                                   \
    X(VARSYS_CHRONO_Afficheur_HM_DIZAINE) /* Page_1_Afficheur_8 */                                                                                   \
    X(VARSYS_FAULT_LOC)                   /* Page_1_Afficheur_9 */                                                                                   \
    X(VARSYS_SCORE_LOC_CENTAINE)          /* Page_1_Afficheur_10 */                                                                                  \
    X(VARSYS_SCORE_LOC_DIZAINE)           /* Page_1_Afficheur_11 */                                                                                  \
    X(VARSYS_SCORE_LOC_UNITE)             /* Page_1_Afficheur_12 */                                                                                  \
    X(VARSYS_CHRONO_PLOT)                 /* Page_1_Afficheur_13 */                                                                                  \
                                          /*Bit 1 CHRONO PLOT; Bit 2: Point dixieme 24 sec */                                                        \
    X(VARSYS_Periode)                     /* Page_1_Afficheur_14 */                                                                                  \
    X(VARSYS_Page_1_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_1_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_1_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_1_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_1_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_1_Afficheur_20)                                                                                                                    \
    X(VARSYS_LOC_TIMEOUT) /* VARSYS_Page_1_Afficheur_21 */                                                                                           \
    X(VARSYS_VIS_TIMEOUT) /* VARSYS_Page_1_Afficheur_22 */                                                                                           \
    X(VARSYS_Page_1_Car_1)                                                                                                                           \
    X(VARSYS_Page_1_Car_2)                                                                                                                           \
    X(VARSYS_Page_1_Car_3)                                                                                                                           \
    X(VARSYS_Page_1_Car_4)                                                                                                                           \
    X(VARSYS_Page_1_Car_5)                                                                                                                           \
    X(VARSYS_Page_1_Car_6)                                                                                                                           \
    X(VARSYS_Page_1_Car_7)                                                                                                                           \
    X(VARSYS_Page_1_Car_8)                                                                                                                           \
    X(VARSYS_Page_1_Car_9)                                                                                                                           \
    X(VARSYS_Page_1_Car_10)                                                                                                                          \
    X(VARSYS_Page_1_Car_11)                                                                                                                          \
    X(VARSYS_Page_1_Car_12)                                                                                                                          \
    X(VARSYS_Page_1_Car_13)                                                                                                                          \
    X(VARSYS_Page_1_Car_14)                                                                                                                          \
    X(VARSYS_Page_1_Car_15)                                                                                                                          \
    X(VARSYS_Page_1_Car_16)                                                                                                                          \
    X(VARSYS_Page_1_Car_17)                                                                                                                          \
    X(VARSYS_Page_1_Car_18)                                                                                                                          \
    X(VARSYS_Page_1_Car_19)                                                                                                                          \
    X(VARSYS_Page_1_Car_20)                                                                                                                          \
    X(VARSYS_Page_1_Car_21)                                                                                                                          \
    X(VARSYS_Page_1_Car_22)                                                                                                                          \
    X(VARSYS_Page_1_Car_23)                                                                                                                          \
    X(VARSYS_Page_1_Car_24)                                                                                                                          \
    X(VARSYS_Page_1_Car_25)                                                                                                                          \
    X(VARSYS_Page_1_Car_26)                                                                                                                          \
    X(VARSYS_Page_1_Car_27)                                                                                                                          \
    X(VARSYS_Page_1_Car_28)                                                                                                                          \
    X(VARSYS_Page_1_Car_29)                                                                                                                          \
    X(VARSYS_Page_1_Car_30)                                                                                                                          \
    X(VARSYS_Page_1_Car_31)                                                                                                                          \
    X(VARSYS_Page_1_Car_32)                                                                                                                          \
    X(VARSYS_Page_1_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_1_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_1_Num_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_1_Val_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_1_Num_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_1_Val_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_1_Num_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_1_Val_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Chrono_Main_Mode) /* VARSYS_Page_1_Chrono_1_Mode */                                                                                     \
    X(VARSYS_Page_1_Chrono_1_Msb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_1_Lsb)                                                                                                                    \
    X(VARSYS_Chrono_Possession_Mode) /* VARSYS_Page_1_Chrono_2_Mode */                                                                               \
    X(VARSYS_Page_1_Chrono_2_Msb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_2_Lsb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_3_Mode)                                                                                                                   \
    X(VARSYS_Page_1_Chrono_3_Msb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_3_Lsb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_4_Mode)                                                                                                                   \
    X(VARSYS_Page_1_Chrono_4_Msb)                                                                                                                    \
    X(VARSYS_Page_1_Chrono_4_Lsb)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_2_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_13)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_14)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_2_Afficheur_20)                                                                                                                    \
    X(VARSYS_Page_2_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_2_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_2_Num_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_2_Val_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_2_Num_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_2_Val_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_2_Num_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_2_Val_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_2_Chrono_1_Mode)                                                                                                                   \
    X(VARSYS_Page_2_Chrono_1_Msb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_1_Lsb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_2_Mode)                                                                                                                   \
    X(VARSYS_Page_2_Chrono_2_Msb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_2_Lsb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_3_Mode)                                                                                                                   \
    X(VARSYS_Page_2_Chrono_3_Msb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_3_Lsb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_4_Mode)                                                                                                                   \
    X(VARSYS_Page_2_Chrono_4_Msb)                                                                                                                    \
    X(VARSYS_Page_2_Chrono_4_Lsb)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_3_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_13)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_14)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_20)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_21)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_22)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_23)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_24)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_25)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_26)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_27)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_28)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_29)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_30)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_31)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_32)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_33)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_34)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_35)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_36)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_37)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_38)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_39)                                                                                                                    \
    X(VARSYS_Page_3_Afficheur_40)                                                                                                                    \
    X(VARSYS_Page_3_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_3_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_4_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_4_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_13)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_14)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_20)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_21)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_22)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_23)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_24)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_25)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_26)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_27)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_28)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_29)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_30)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_31)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_32)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_33)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_34)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_35)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_36)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_37)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_38)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_39)                                                                                                                    \
    X(VARSYS_Page_4_Afficheur_40)                                                                                                                    \
    X(VARSYS_Page_4_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_4_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Canal_de_fonctionement)                                                                                                                 \
    X(VARSYS_Jour_du_mois) /* L'annee est codee sur les bits 8 a 6 de UCH_Jour_du_mois (poids   */                                                   \
    X(VARSYS_Mois)         /* forts) et les bits 8 a 5 de UCH_Mois (poids faibles).             */                                                   \
    X(VARSYS_Heure)        /* Sur les bit 8 a 6 de UCH_Heure est code l'heure de l'autotest     */                                                   \
    X(VARSYS_Minute)                                                                                                                                 \
    X(VARSYS_Seconde)                                                                                                                                \
    X(VARSYS_Synchronisation_ancienne_Var_Sys) /* Declaration de cet octet seulement pour etre compatible */                                         \
                                               /* avec l'ancienne declaration de Var_Sys. Ne pas utiliser. */                                        \
    X(VARSYS_Decalage_horaire)                 /* Bit 7: maj pupitre, */                                                                             \
                                               /* Bit 6: mode affichage au noir-, */                                                                 \
                                               /* Bit 5: mode eco */                                                                                 \
    X(VARSYS_Temperature)                                                                                                                            \
    X(VARSYS_Compensation_temperature) /* Bit 7: maj pupitre */                                                                                      \
                                       /* Bit 6: mode affichage au noir */                                                                           \
                                       /* Bit 5: si 1 Nom locaux sur deux lignes. */                                                                 \
                                       /* Bit 4: si 1 Nom Visiteurs sur deux lignes. */                                                              \
                                       /* Bit 0-1-2-3 val compensation */                                                                            \
    X(VARSYS_Page_5_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_5_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_5_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_5_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_6_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_6_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_6_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_6_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_7_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_7_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_7_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_7_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_7_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_7_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_7_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_7_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_7_Chrono_1_Mode)                                                                                                                   \
    X(VARSYS_Page_7_Chrono_1_Msb)                                                                                                                    \
    X(VARSYS_Page_7_Chrono_1_Lsb)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_8_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_13)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_14)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_8_Afficheur_20)                                                                                                                    \
    X(VARSYS_Page_8_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_8_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_8_Num_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_8_Val_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_8_Num_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_8_Val_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_8_Num_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_8_Val_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_8_Chrono_1_Mode)                                                                                                                   \
    X(VARSYS_Page_8_Chrono_1_Msb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_1_Lsb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_2_Mode)                                                                                                                   \
    X(VARSYS_Page_8_Chrono_2_Msb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_2_Lsb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_3_Mode)                                                                                                                   \
    X(VARSYS_Page_8_Chrono_3_Msb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_3_Lsb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_4_Mode)                                                                                                                   \
    X(VARSYS_Page_8_Chrono_4_Msb)                                                                                                                    \
    X(VARSYS_Page_8_Chrono_4_Lsb)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_1)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_2)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_3)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_4)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_5)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_6)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_7)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_8)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_9)                                                                                                                     \
    X(VARSYS_Page_9_Afficheur_10)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_11)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_12)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_13)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_14)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_15)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_16)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_17)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_18)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_19)                                                                                                                    \
    X(VARSYS_Page_9_Afficheur_20)                                                                                                                    \
    X(VARSYS_Page_9_Num_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_9_Val_afficheur_clignotant_1)                                                                                                      \
    X(VARSYS_Page_9_Num_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_9_Val_afficheur_clignotant_2)                                                                                                      \
    X(VARSYS_Page_9_Num_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_9_Val_afficheur_clignotant_3)                                                                                                      \
    X(VARSYS_Page_9_Num_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_9_Val_afficheur_clignotant_4)                                                                                                      \
    X(VARSYS_Page_9_Chrono_1_Mode)                                                                                                                   \
    X(VARSYS_Page_9_Chrono_1_Msb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_1_Lsb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_2_Mode)                                                                                                                   \
    X(VARSYS_Page_9_Chrono_2_Msb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_2_Lsb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_3_Mode)                                                                                                                   \
    X(VARSYS_Page_9_Chrono_3_Msb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_3_Lsb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_4_Mode)                                                                                                                   \
    X(VARSYS_Page_9_Chrono_4_Msb)                                                                                                                    \
    X(VARSYS_Page_9_Chrono_4_Lsb)                                                                                                                    \
    X(VARSYS_Page_10_Affichage_mode_heure) /* Bit 0 = 1 => Affichage du message en mode heure.                */                                     \
                                           /* Bit 1 = 1 => Affichage du message en mode match.                */                                     \
                                           /* Bit 2 = 1 => Gestion du message en cours.                       */                                     \
    X(VARSYS_Page_10_octet_2)              /* CRC1 */                                                                                                \
    X(VARSYS_Page_10_octet_3)              /* CRC2 */                                                                                                \
    X(VARSYS_Page_10_octet_4)              /* Taille message */                                                                                      \
    X(VARSYS_Page_10_octet_5)              /* Mode defilement */                                                                                     \
    X(VARSYS_Page_10_octet_6)              /* Vitesse */                                                                                             \
    X(VARSYS_Page_10_octet_7)              /* Temps */                                                                                               \
    X(VARSYS_Page_10_octet_8)              /* Debut message */                                                                                       \
    X(VARSYS_Page_10_octet_9)                                                                                                                        \
    X(VARSYS_Page_10_octet_10)                                                                                                                       \
    X(VARSYS_Page_10_octet_11)                                                                                                                       \
    X(VARSYS_Page_10_octet_12)                                                                                                                       \
    X(VARSYS_Page_10_octet_13)                                                                                                                       \
    X(VARSYS_Page_10_octet_14)                                                                                                                       \
    X(VARSYS_Page_10_octet_15)                                                                                                                       \
    X(VARSYS_Page_10_octet_16)                                                                                                                       \
    X(VARSYS_Page_10_octet_17)                                                                                                                       \
    X(VARSYS_Page_10_octet_18)                                                                                                                       \
    X(VARSYS_Page_10_octet_19)                                                                                                                       \
    X(VARSYS_Page_10_octet_20)                                                                                                                       \
    X(VARSYS_Page_10_octet_21)                                                                                                                       \
    X(VARSYS_Page_10_octet_22)                                                                                                                       \
    X(VARSYS_Page_10_octet_23)                                                                                                                       \
    X(VARSYS_Page_10_octet_24)                                                                                                                       \
    X(VARSYS_Page_10_octet_25)                                                                                                                       \
    X(VARSYS_Page_10_octet_26)                                                                                                                       \
    X(VARSYS_Page_10_octet_27)                                                                                                                       \
    X(VARSYS_Page_10_octet_28)                                                                                                                       \
    X(VARSYS_Page_10_octet_29)                                                                                                                       \
    X(VARSYS_Page_10_octet_30)                                                                                                                       \
    X(VARSYS_Page_10_octet_31)                                                                                                                       \
    X(VARSYS_Page_10_octet_32)                                                                                                                       \
    X(VARSYS_Page_10_octet_33)                                                                                                                       \
    X(VARSYS_Page_10_octet_34)                                                                                                                       \
    X(VARSYS_Page_10_octet_35)                                                                                                                       \
    X(VARSYS_Page_10_octet_36)                                                                                                                       \
    X(VARSYS_Page_10_octet_37)                                                                                                                       \
    X(VARSYS_Page_10_octet_38)                                                                                                                       \
    X(VARSYS_Page_10_octet_39)                                                                                                                       \
    X(VARSYS_Page_10_octet_40)                                                                                                                       \
    X(VARSYS_Page_10_octet_41)                                                                                                                       \
    X(VARSYS_Page_10_octet_42)                                                                                                                       \
    X(VARSYS_Page_10_octet_43)                                                                                                                       \
    X(VARSYS_Page_10_octet_44)                                                                                                                       \
    X(VARSYS_Page_10_octet_45)                                                                                                                       \
    X(VARSYS_Page_10_octet_46)                                                                                                                       \
    X(VARSYS_Page_10_octet_47)                                                                                                                       \
    X(VARSYS_Page_10_octet_48)                                                                                                                       \
    X(VARSYS_Page_10_octet_49)                                                                                                                       \
    X(VARSYS_Page_10_octet_50)                                                                                                                       \
    X(VARSYS_Page_10_octet_51)                                                                                                                       \
    X(VARSYS_Page_10_octet_52)                                                                                                                       \
    X(VARSYS_Page_10_octet_53)                                                                                                                       \
    X(VARSYS_Page_10_octet_54)                                                                                                                       \
    X(VARSYS_Page_10_octet_55)                                                                                                                       \
    X(VARSYS_Page_10_octet_56)                                                                                                                       \
    X(VARSYS_Page_10_octet_57)                                                                                                                       \
    X(VARSYS_Page_10_octet_58)                                                                                                                       \
    X(VARSYS_Page_10_octet_59)                                                                                                                       \
    X(VARSYS_Page_10_octet_60)                                                                                                                       \
    X(VARSYS_Page_10_octet_61)                                                                                                                       \
    X(VARSYS_Page_10_octet_62)                                                                                                                       \
    X(VARSYS_Page_10_octet_63)                                                                                                                       \
    X(VARSYS_Page_10_octet_64)                                                                                                                       \
    X(VARSYS_Page_10_octet_65)                                                                                                                       \
    X(VARSYS_Page_10_octet_66)                                                                                                                       \
    X(VARSYS_Page_10_octet_67)                                                                                                                       \
    X(VARSYS_Page_11_Afficheur_1)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_2)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_3)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_4)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_5)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_6)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_7)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_8)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_9)                                                                                                                    \
    X(VARSYS_Page_11_Afficheur_10)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_11)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_12)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_13)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_14)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_15)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_16)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_17)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_18)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_19)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_20)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_21)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_22)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_23)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_24)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_25)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_26)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_27)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_28)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_29)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_30)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_31)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_32)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_33)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_34)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_35)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_36)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_37)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_38)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_39)                                                                                                                   \
    X(VARSYS_Page_11_Afficheur_40)                                                                                                                   \
    X(VARSYS_Page_11_Num_afficheur_clignotant_1)                                                                                                     \
    X(VARSYS_Page_11_Val_afficheur_clignotant_1)                                                                                                     \
    X(VARSYS_Page_11_Num_afficheur_clignotant_2)                                                                                                     \
    X(VARSYS_Page_11_Val_afficheur_clignotant_2)                                                                                                     \
    X(VARSYS_Page_11_Num_afficheur_clignotant_3)                                                                                                     \
    X(VARSYS_Page_11_Val_afficheur_clignotant_3)                                                                                                     \
    X(VARSYS_Page_11_Num_afficheur_clignotant_4)                                                                                                     \
    X(VARSYS_Page_11_Val_afficheur_clignotant_4)                                                                                                     \
    X(VARSYS_Page_11_Chrono_1_Mode)                                                                                                                  \
    X(VARSYS_Page_11_Chrono_1_Msb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_1_Lsb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_2_Mode)                                                                                                                  \
    X(VARSYS_Page_11_Chrono_2_Msb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_2_Lsb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_3_Mode)                                                                                                                  \
    X(VARSYS_Page_11_Chrono_3_Msb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_3_Lsb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_4_Mode)                                                                                                                  \
    X(VARSYS_Page_11_Chrono_4_Msb)                                                                                                                   \
    X(VARSYS_Page_11_Chrono_4_Lsb)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_1)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_2)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_3)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_4)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_5)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_6)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_7)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_8)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_9)                                                                                                                    \
    X(VARSYS_Page_12_Afficheur_10)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_11)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_12)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_13)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_14)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_15)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_16)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_17)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_18)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_19)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_20)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_21)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_22)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_23)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_24)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_25)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_26)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_27)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_28)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_29)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_30)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_31)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_32)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_33)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_34)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_35)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_36)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_37)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_38)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_39)                                                                                                                   \
    X(VARSYS_Page_12_Afficheur_40)                                                                                                                   \
    X(VARSYS_Page_12_Num_afficheur_clignotant_1)                                                                                                     \
    X(VARSYS_Page_12_Val_afficheur_clignotant_1)                                                                                                     \
    X(VARSYS_Page_12_Num_afficheur_clignotant_2)                                                                                                     \
    X(VARSYS_Page_12_Val_afficheur_clignotant_2)                                                                                                     \
    X(VARSYS_Page_12_Num_afficheur_clignotant_3)                                                                                                     \
    X(VARSYS_Page_12_Val_afficheur_clignotant_3)                                                                                                     \
    X(VARSYS_Page_12_Num_afficheur_clignotant_4)                                                                                                     \
    X(VARSYS_Page_12_Val_afficheur_clignotant_4)                                                                                                     \
    X(VARSYS_Page_12_Chrono_1_Mode)                                                                                                                  \
    X(VARSYS_Page_12_Chrono_1_Msb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_1_Lsb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_2_Mode)                                                                                                                  \
    X(VARSYS_Page_12_Chrono_2_Msb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_2_Lsb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_3_Mode)                                                                                                                  \
    X(VARSYS_Page_12_Chrono_3_Msb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_3_Lsb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_4_Mode)                                                                                                                  \
    X(VARSYS_Page_12_Chrono_4_Msb)                                                                                                                   \
    X(VARSYS_Page_12_Chrono_4_Lsb)

#define X(id) id,

typedef enum {
    VARSYS_DATA_COMMAND_LIST

        NB_VARSYS_COMMAND,
    UNKNOWN_COMMAND

} varsys_data_command_e;

#undef X

const char* varsys_data_correspondant_name(varsys_data_correspondant_e correspondant);
const char* varsys_data_command_name(varsys_data_command_e command);

#endif