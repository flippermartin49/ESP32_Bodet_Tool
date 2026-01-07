#ifndef _ETHERNET_H
#define _ETHERNET_H

#include "esp_event.h"
#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_client.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>

void ethernet_init(void);
void test_request(void);
void udp_broadcast_send(void);
void udp_discovery_listener_task(void *arg);


#endif