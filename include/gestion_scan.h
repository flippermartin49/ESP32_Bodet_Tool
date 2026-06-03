#ifndef _GESTION_SCAN_H_
#define _GESTION_SCAN_H_

#include <string.h>
#include <stdio.h>
#include "stdbool.h"
#include "esp_http_server.h"
#include "esp_log.h"


#define MAX_DEVICES 50
#define MAX_JSON_LEN 8192

typedef struct {
    char ip[16];
    char nom_produit[32];
    char mask[16];
    char gateway[16];
    char dns[16];
    char gamme[32];
    char mac[18];   // "AA:BB:CC:DD:EE:FF"
    char version[64];
    char dhcp[1];
} device_t;

extern uint8_t device_count;
extern device_t extern_devices_list[MAX_DEVICES];
extern device_t extern_device;


void devices_add(const char *ip, const char *mac, const char *name);
void generate_devices_json(char *dev_to_json);
bool parse_udp_device(const char *payload, device_t *dev);

#endif