idf_component_register(
    SRCS "wifi_manager.c" "web_server.c" "dh11_manager.c" "sensor_data.c" "main.c"
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_event esp_netif nvs_flash esp_http_server esp_driver_gpio dht11
)