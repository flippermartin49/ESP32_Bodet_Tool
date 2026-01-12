idf_component_register(SRCS "console.c" "ethernet.c" "main.c" "wifi.c"
                    INCLUDE_DIRS "." "../include/"
                    REQUIRES esp_wifi nvs_flash esp_eth esp_http_client esp_netif console vfs esp_timer)