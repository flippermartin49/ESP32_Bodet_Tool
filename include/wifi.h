#ifndef _WIFI_H
#define _WIFI_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"
#include "esp_http_server.h"

#include "gestion_scan.h"
#include "ethernet.h"

#define WIFI_SSID "ESP_BODET_TOOL"
#define WIFI_PASS "12345678"
#define PORT 1234

void wifi_init_ap(void);
void tcp_server_task(void *pvParameters);

esp_err_t devices_get_handler(httpd_req_t *req);
esp_err_t root_handler(httpd_req_t *req);
esp_err_t scan_dhs_handler(httpd_req_t *req);
esp_err_t proxy_test_handler(httpd_req_t *req);



void start_http_server(void);

#endif