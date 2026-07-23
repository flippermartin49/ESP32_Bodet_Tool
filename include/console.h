#ifndef _CONSOLE_H_
#define _CONSOLE_H_


#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_console.h"
#include "esp_log.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"

#include "linenoise/linenoise.h"

#include "ethernet.h"   

#include "config.h"

void console_init(void);
void console_task(void *args);
void save_commands(void);

/*GESTION ETHERNET */

int cmd_AT(int agrc, char **argv);
int cmd_status_link(int argc, char **argv);
int cmd_scan(int argc, char **argv);
int cmd_help(int argc, char **argv);
int cmd_getMAC(int argc, char **argvc);
int cmd_get_eth_IP_Info(int agrc, char **argvc);
int cmd_getWIFI_Info(int agrc, char **argvc);
int cmd_ping(int argc, char **argvc);
int cmd_reboot(int argc, char **argvc);
int cmd_set_eth_ip(int argc, char **argvc);
int cmd_set_wifi_ip(int argc, char **argvc);

/*****  GESTION SPORT *****/

int cmd_enter_config(int agrc, char **argv);
int cmd_exit_config(int agrc, char **argv);
int cmd_reset_board(int agrc, char **argv);

#endif