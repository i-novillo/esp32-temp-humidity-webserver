#include "web_server.h"
#include "esp_log.h"

#include "sensor_data.h"

static const char *TAG = "WEB_SERVER";

// -------------------------
// HTTP handler
// -------------------------
static esp_err_t hello_get_handler(httpd_req_t *req)
{
    float temperature, humidity;
    char html_response[512];

    get_sensor_data(&temperature, &humidity);

    snprintf(html_response, sizeof(html_response),
        "<!DOCTYPE html>"
        "<html>"
        "<head><title>ESP32 Temperature and Humidity</title></head>"
        "<body>"
        "<h1>ESP32 DHT11 Temperature and Humidity Measurements</h1>"
        "<p>Temperature: %.1f C</p>"
        "<p>Humidity: %.1f %%</p>"
        "</body>"
        "</html>",
        temperature, humidity);

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, html_response, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_LOGI(TAG, "Starting HTTP server on port: '%d'", config.server_port);

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t hello_uri = {
            .uri       = "/",
            .method    = HTTP_GET,
            .handler   = hello_get_handler,
            .user_ctx  = NULL
        };

        httpd_register_uri_handler(server, &hello_uri);
        return server;
    }

    ESP_LOGE(TAG, "Error starting server!");
    return NULL;
}
