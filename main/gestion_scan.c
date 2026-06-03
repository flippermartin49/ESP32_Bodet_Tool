#include "../include/gestion_scan.h"

static const char *TAG_JSON = "JSON";

void generate_devices_json(char *dev_to_json)
{
    if(!dev_to_json) return;

    ESP_LOGI(TAG_JSON, "Creating Json File.... with %d devices", device_count);

    size_t used = 0;
    used += snprintf(dev_to_json + used, MAX_JSON_LEN - used, "{ \"devices\": [");

    for (int i = 1; i < device_count; i++) 
    {

        char buf[512];

        snprintf(buf, sizeof(buf),
            "{"
            "\"ip\":\"%s\","
            "\"nom\":\"%s\","
            "\"mask\":\"%s\","
            "\"gateway\":\"%s\","
            "\"dns\":\"%s\","
            "\"gamme\":\"%s\","
            "\"mac\":\"%s\","
            "\"version\":\"%s\""
            "}",
            extern_devices_list[i].ip,
            extern_devices_list[i].nom_produit,
            extern_devices_list[i].mask,
            extern_devices_list[i].gateway,
            extern_devices_list[i].dns,
            extern_devices_list[i].gamme,
            extern_devices_list[i].mac,
            extern_devices_list[i].version
        );

        // Sécurité taille
        if (used + strlen(buf) >= MAX_JSON_LEN)
        {
            ESP_LOGE(TAG_JSON, "JSON buffer overflow !");
            break;
        }

        used += snprintf(dev_to_json + used, MAX_JSON_LEN - used, "%s", buf);

        if (i < (device_count - 1))
        {
            used += snprintf(dev_to_json + used, MAX_JSON_LEN - used, ",");
        }
    }

    snprintf(dev_to_json + used, MAX_JSON_LEN - used, "] }");
    device_count = 0;
    //ESP_LOGI(TAG_JSON,"JSON = %s", dev_to_json);
}

bool parse_udp_device(const char *payload, device_t *dev)
{
    // On vide la structure avant 
    memset(dev, 0, sizeof(device_t));

    char buf[512];
    strncpy(buf, payload, sizeof(buf)-1);

    char *line;
    int idx = 0;

    line = strtok(buf, "\n");

    while(line)
    {
        // suppression \r
        line[strcspn(line,"\r")] = 0;

        switch(idx)
        {   
            case 1: strncpy(dev->dhcp, line, sizeof(dev->dhcp));break;
            case 2: strncpy(dev->ip,line,sizeof(dev->ip)); break;
            case 3: strncpy(dev->mask,line,sizeof(dev->mask)); break;
            case 4: strncpy(dev->mac,line,sizeof(dev->mac)); break;
            case 5: strncpy(dev->dns,line,sizeof(dev->dns)); break;
            case 6: strncpy(dev->gateway,line,sizeof(dev->gateway)); break;
            case 7: strncpy(dev->version,line,sizeof(dev->version)); break;
            case 8: strncpy(dev->nom_produit,line,sizeof(dev->nom_produit)); break;
            case 9: strncpy(dev->gamme,line,sizeof(dev->gamme)); break;
            default: break;
        }

        idx++;
        line = strtok(NULL,"\n");
    }

    return (idx >= 9);
}

