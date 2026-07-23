/**
 * @file wifi.c
 * @author soulardma
 * @brief Fichier de configuration Wifi + serveur HTTP
 * @version 0.1
 * @date 2026-01-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */



#include "../include/wifi.h"

httpd_handle_t server = NULL;

static const char *TAG_WIFI = "WIFI_P2P";
static const char *TAG_HTTP = "HTTP";

void wifi_init_ap(void)
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    esp_netif_t* netif = esp_netif_create_default_wifi_ap();

    // IP fixe
    esp_netif_ip_info_t ip_info;
    IP4_ADDR(&ip_info.ip, 192,168,4,1);
    IP4_ADDR(&ip_info.gw, 192,168,4,1);
    IP4_ADDR(&ip_info.netmask,255,255,255,0);

    esp_netif_dhcps_stop(netif);
    esp_netif_set_ip_info(netif, &ip_info);
    esp_netif_dhcps_start(netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "ESP32_BODETOOL",
            .password = "12345678",
            .channel = 1,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG_WIFI, "AP démarré : 192.168.4.1");

    start_http_server();   // <-- serveur HTTP ici
}

void start_http_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 8192;
    ESP_LOGI("HTTP", "Server port: %d", config.server_port);

    if(httpd_start(&server,&config)==ESP_OK)
    {

        httpd_uri_t root_uri = {
            .uri      = "/",
            .method   = HTTP_GET,
            .handler  = root_handler,
        };

        httpd_uri_t ping = {
            .uri = "/ping",
            .method = HTTP_GET,
            .handler = ping_handler
        };

        /*====== TIME =====*/

        httpd_uri_t uri_device = {
            .uri      = "/devices_time", 
            .method   = HTTP_GET,
            .handler  = devices_time_get_handler,
            .user_ctx = NULL
        };

        httpd_uri_t scan_dhs_uri = {
            .uri      = "/scan_dhs",
            .method   = HTTP_GET,
            .handler  = scan_dhs_handler,
        };

        httpd_uri_t proxy_test_uri = {
            .uri      = "/proxy/test",
            .method   = HTTP_GET,
            .handler  = proxy_test_handler,
            .user_ctx = NULL
        };

        /*====== SPORT ======*/
        
        // Lance le recensement 
        httpd_uri_t recensement_uri = {
            .uri      = "/config/recensement",
            .method   = HTTP_GET,
            .handler  = recensement_handler,
            .user_ctx = NULL
        };

        // Renvoi les devices sur le bus RS485
        httpd_uri_t sport_devices_uri = {
            .uri      = "/config/devices_sport",
            .method   = HTTP_GET,
            .handler  = device_sport_get_handler,
            .user_ctx = NULL
        };

        httpd_uri_t exit_config_uri = {
            .uri      = "/config/exit",
            .method   = HTTP_GET,
            .handler  = exit_config_handler,
            .user_ctx = NULL
        };

        httpd_register_uri_handler(server, &root_uri);
        httpd_register_uri_handler(server, &ping);
        httpd_register_uri_handler(server, &scan_dhs_uri);
        httpd_register_uri_handler(server, &proxy_test_uri);

        httpd_register_uri_handler(server, &uri_device);
        httpd_register_uri_handler(server, &recensement_uri);
        httpd_register_uri_handler(server, &exit_config_uri);
        httpd_register_uri_handler(server, &sport_devices_uri);



        ESP_LOGI(TAG_HTTP,"Serveur HTTP démarré");
    }
}

esp_err_t root_handler(httpd_req_t *req)
{
    const char *resp =
        "ESP32 Device API\n"
        "Use:\n"
        "  /devices\n";

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t ping_handler(httpd_req_t *req)
{
    httpd_resp_send(req, "OK", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* ==================== TIME =================================*/

esp_err_t scan_dhs_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG_HTTP, "SCAN DHS request...");

    udp_broadcast_send("dhs 1 get-info");

    httpd_resp_send(req, "SCAN_STARTED", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

// Requete uniquement en mode listener, lancer scan udp avant
esp_err_t devices_time_get_handler(httpd_req_t *req)
{
    static char json_list[MAX_JSON_LEN];
    ESP_LOGI(TAG_HTTP,"Device_get_handler http...");

    generate_devices_json(json_list);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json_list, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}


// Essai affichage page serveur web du device selectionné
esp_err_t proxy_test_handler(httpd_req_t *req)
{
    ESP_LOGI("HTTP", "proxy_test_handler called");

    const char *html =
        "<!DOCTYPE html>"
        "<html>"
            "<head>"
            "<meta charset='utf-8'>"
            "<title>ESP32 Proxy Test</title>"
            "<style>"
                "body { font-family: sans-serif; background:#FFF012; padding:20px; }"
                "h1 { color:#000; }"
            "</style>"
            "</head>"
            "<body>"
                "<h1>Proxy ESP32 OK</h1>"
                "<p>La page est bien streamée depuis l'ESP32.</p>"
            "</body>"
        "</html>";

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* ===================== SPORT ====================================*/

esp_err_t enter_config_handler(httpd_req_t *req)
{

    ESP_LOGI(TAG_HTTP, "Enter config request....");

    enter_mode_config();
    
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, "json", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

esp_err_t recensement_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG_HTTP, "Start recensement request....");

    send_command_recensement();

    httpd_resp_send(req, "RECENSEMENT", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

esp_err_t device_sport_get_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG_HTTP, "Get sport device");

    static char json_sport_device[MAX_JSON_LEN];
    device_sport_to_json(json_sport_device, sizeof(json_sport_device));

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json_sport_device, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}


esp_err_t exit_config_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG_HTTP, "exit config request....");
    httpd_resp_send(req, "RECENSEMENT", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}
