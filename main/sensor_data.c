#include "sensor_data.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "SENSOR_DATA";

typedef struct {
    float temperature;
    float humidity;
} sensor_data_t;

static sensor_data_t g_sensor_data = {0};
static SemaphoreHandle_t sensor_mutex = NULL;

void init_sensor_data(void)
{
    sensor_mutex = xSemaphoreCreateMutex();

    if (sensor_mutex == NULL) {
        ESP_LOGE(TAG, "Failed to create sensor mutex");
    } else {
        ESP_LOGI(TAG, "Sensor mutex created");
    }
}

void set_sensor_data(float temperature, float humidity)
{
    if (xSemaphoreTake(sensor_mutex, portMAX_DELAY) == pdTRUE) {
        g_sensor_data.temperature = temperature;
        g_sensor_data.humidity = humidity;
        xSemaphoreGive(sensor_mutex);
    }
}

void get_sensor_data(float *temperature, float *humidity)
{
    if (xSemaphoreTake(sensor_mutex, portMAX_DELAY) == pdTRUE) {
        *temperature = g_sensor_data.temperature;
        *humidity = g_sensor_data.humidity;
        xSemaphoreGive(sensor_mutex);
    }
}