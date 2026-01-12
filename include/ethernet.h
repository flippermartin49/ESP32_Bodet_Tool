#ifndef _ETHERNET_H
#define _ETHERNET_H

#include "esp_event.h"
#include "esp_timer.h"
#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "netinet/in.h"
#include "lwip/icmp.h"
#include "lwip/inet.h"
#include "lwip/inet_chksum.h"
#include "lwip/sockets.h"


#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>

void ethernet_init(void);
void test_request(void);
void udp_broadcast_send(void);
void udp_discovery_listener_task(void *arg);
esp_eth_handle_t get_eth_handle(void);
void ping_ip(const char *target);


#endif