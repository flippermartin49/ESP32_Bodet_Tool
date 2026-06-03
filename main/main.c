#include <stdio.h>
#include "../include/wifi.h"
#include "../include/ethernet.h"
#include "../include/console.h"
#include "../include/sport/RS485.h"


void app_main(void)
{
    rs485_init();   // En cas d'utilisation Varsys Sport

    wifi_init_ap();
    ethernet_init();
    console_init();

    xTaskCreate(udp_discovery_listener_task, "udp_listener", 4096, NULL, 5, NULL);  

    vTaskDelay(pdMS_TO_TICKS(1000));

    //udp_broadcast_send("dhs 1 get-info");

    vTaskDelay(pdMS_TO_TICKS(2000));

    xTaskCreate(console_task, "console", 4096, NULL, 5, NULL);  
}