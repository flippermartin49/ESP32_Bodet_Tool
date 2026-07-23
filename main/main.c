#include <stdio.h>
#include "../include/wifi.h"
#include "../include/ethernet.h"
#include "../include/console.h"
#include "../include/sport/config.h"
#include "../include/sport/varsys.h"


void app_main(void)
{

    date_heure_t date_test = {
        .year = 2022,
        .month = 3,
        .day = 27,
        
        .hour = 8,
        .minute = 17,
        .second = 41
    };

    //console_init();
    // En cas d'utilisation Varsys Sport
    config_init();
    
    wifi_init_ap();
    
    /*ethernet_init();
    
    
    
    xTaskCreate(udp_discovery_listener_task, "udp_listener", 4096, NULL, 5, NULL);  

    //udp_broadcast_send("dhs 1 get-info");

    vTaskDelay(pdMS_TO_TICKS(2000));
    */
    //xTaskCreate(console_task, "console", 4096, NULL, 5, NULL);  

    xTaskCreate(rs485_receive_task, "rs485_task", 4096, NULL, 10, NULL);    
    

    //send_command_recensement();
    

}