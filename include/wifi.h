#ifndef _WIFI_H
#define _WIFI_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"


#define WIFI_SSID "ESP_BODET_TOOL"
#define WIFI_PASS "12345678"
#define PORT 1234

void wifi_init_p2p(void);
void wifi_create_ap(void);
void tcp_server_task(void *pvParameters);

#endif