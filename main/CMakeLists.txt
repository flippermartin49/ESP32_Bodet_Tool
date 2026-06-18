idf_component_register(SRCS "sport/config.c" "console.c" "ethernet.c" "main.c" "wifi.c" "gestion_scan.c"
                    INCLUDE_DIRS "." "../include/" "../include/sport/"
                    REQUIRES esp_wifi nvs_flash esp_eth esp_http_client esp_netif console vfs esp_timer esp_http_server)