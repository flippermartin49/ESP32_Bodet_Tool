#include <stdio.h>
#include "../include/wifi.h"
#include "../include/ethernet.h"
#include "../include/console.h"

void app_main(void)
{
    wifi_init_p2p();
    wifi_create_ap();

    ethernet_init();
    console_init();

    xTaskCreate(tcp_server_task, "tcp_server", 4096, NULL, 5, NULL);
    
    xTaskCreate(udp_discovery_listener_task, "udp_listener", 4096, NULL, 5, NULL);
    xTaskCreate(console_task, "console", 4096, NULL, 5, NULL);    

    vTaskDelay(pdMS_TO_TICKS(500));
}