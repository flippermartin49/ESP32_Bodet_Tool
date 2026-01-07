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

#include "ethernet.h"   // pour udp_broadcast_send()

static const char *TAG = "CONSOLE";

void console_init(void);
void console_task(void *args);
void save_commands(void);

static int cmd_scan(int argc, char **argv);
static int cmd_help(int argc, char **argv);
static int cmd_getMAC(int argc, char **argvc);
static int cmd_getIP_Info(int agrc, char **argvc);


#endif