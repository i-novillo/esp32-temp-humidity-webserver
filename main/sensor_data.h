#ifndef SHARED_DATA_H
#define SHARED_DATA_H

/**
 * @brief Initializes the sensor data structure and any necessary synchronization primitives.
 */
void init_sensor_data(void);

/**
 * @brief Sets the current temperature and humidity values in the shared data structure.
 * @param temperature The current temperature value to set.
 * @param humidity The current humidity value to set.
 */
void set_sensor_data(float temperature, float humidity);

/**
 * @brief Retrieves the current temperature and humidity values from the shared data structure.
 * @param temperature A pointer to a float where the temperature value will be stored.
 * @param humidity A pointer to a float where the humidity value will be stored.
 */
void get_sensor_data(float *temperature, float *humidity);

#endif