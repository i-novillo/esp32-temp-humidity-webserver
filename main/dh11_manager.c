#include "dh11_manager.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "esp32-dht11.h"

#include "sensor_data.h"

#define CONFIG_CONNECTION_TIMEOUT 5

#define TAG "DHT11_MANAGER"

static void dht11_task(void *pvParameters) {
    dht11_t dht11_sensor;
    dht11_sensor.dht11_pin = CONFIG_APP_DHT11_PIN;

    // Read data
    while(1)
    {
      if(!dht11_read(&dht11_sensor, CONFIG_CONNECTION_TIMEOUT))
      {  
        set_sensor_data(dht11_sensor.temperature, dht11_sensor.humidity);
        ESP_LOGV(TAG, "Temperature: %.1f C, Humidity: %.1f %%", dht11_sensor.temperature, dht11_sensor.humidity);
      }
      vTaskDelay(2000/portTICK_PERIOD_MS);
    } 
}

void start_dh11_task() {
    xTaskCreate(dht11_task, "dht11_task", 4096, NULL, 1, NULL);
}