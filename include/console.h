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

void console_init(void);
void console_task(void *args);
void save_commands(void);

int cmd_status_link(int argc, char **argv);
int cmd_scan(int argc, char **argv);
int cmd_help(int argc, char **argv);
int cmd_getMAC(int argc, char **argvc);
int cmd_getIP_Info(int agrc, char **argvc);
int cmd_getWIFI_Info(int agrc, char **argvc);
int cmd_ping(int argc, char **argvc);
int cmd_reboot(int argc, char **argvc);

#endif