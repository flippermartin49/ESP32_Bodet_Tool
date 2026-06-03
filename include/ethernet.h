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

#include "gestion_scan.h"

#include <string.h>

/**
 * @brief Messages TCP ou UDP a envoyer à la CPU Karbulink
 * 
 */

#define MSG_KARBULINK_SCAN              "kar 1 get-info"
#define MSG_KARBULINK_SUPERVISION       "kar 1 get-super" // Demande status supervision
#define MSG_KARBULINK_GET_CONFIG        "kar 1 get-conf"
#define MSG_KARBULINK_AUTOTEST          "kar 1 test-pro"
#define MSG_KARBULINK_SET_CONFIG        "kar 1 set-conf"
#define MSG_KARBULINK_SET_PRICE         "kar 1 set-price"
#define MSG_KARBULINK_LOCATE            "kar 1 set-locate"
#define MSG_KARBULINK_TEST              "kar 1 testotem"
#define MSG_KARBULINK_SET_IP            "kar 1 set-ip"

//#define MSG_KARBULINK_SET_PEERING       "kar 1 set-peering"
//#define MSG_KARBULINK_SET_FIRMWARE      "kar 1 set-firm"
//#define MSG_KARBULINK_TEST_PASSWORD     "kar 1 test-pass" // Demande validité du password

/**
 * @brief Messages TCP ou UDP pour Sigma
 * 
 */

// Renvoi les infos des produits sigma
#define MSG_SCAN_SIGMA      "sigma 1 get-info"

/**
 * @brief Message TCP ou UDP pour produits Time
 * 
 */

#define MSG_SCAN_DHS        "dhs 1 get-info"


void ethernet_init(void);
void test_request(void);
void udp_broadcast_send(const char *msg);
void udp_discovery_listener_task(void *arg);
esp_eth_handle_t get_eth_handle(void);
void ping_ip(const char *target);
bool device_exists(const char *mac);



#endif