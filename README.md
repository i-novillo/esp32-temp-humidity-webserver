# ESP32 DHT11 Web Server

An asynchronous IoT application built with **ESP-IDF** that reads temperature and humidity data from a **DHT11** sensor and serves it through a lightweight **HTTP web server** over the configured Wi-Fi connection.

The project demonstrates the use of **FreeRTOS tasks**, **Kconfig / menuconfig** for hardware abstraction, and **thread-safe data sharing** between a background sensor driver and a network interface.

---

## 📋 Table of Contents

- [✨ Features](#-features)
- [🏗️ Hardware Architecture](#️-hardware-architecture)
- [💻 Software Overview](#-software-overview)
- [⚙️ Configuration](#️-configuration)
- [📦 Installation & Flashing](#-installation--flashing)
- [📚 Third-Party Libraries](#-third-party-libraries)

---

## ✨ Features

- **Dynamic Pin Mapping**  
  Change the sensor GPIO without modifying source code by using `menuconfig`.

- **Asynchronous Polling**  
  A background FreeRTOS task handles sensor timing, periodic reads, and retry/error recovery.

- **Simple Web UI**  
  Responds to HTTP `GET` requests with a lightweight dashboard showing the latest temperature and humidity values.

- **ESP-IDF Native Project**  
  Built in **C** using the **ESP-IDF** framework.

---

## 🏗️ Hardware Architecture

To build this project, you will need:

- **ESP32 DevKit** (any common variant)
- **DHT11 Sensor** (3-pin or 4-pin version)

### Wiring

| DHT11 Pin | ESP32 |
|----------|------|
| VCC      | 3.3V |
| GND      | GND  |
| DATA     | Configured GPIO (default: **GPIO 14**) |

> **Note:** Some standalone DHT11 modules already include the required pull-up resistor.  
> If you are using a bare DHT11 sensor, you may need a **10kΩ pull-up resistor** between **VCC** and **DATA**.

---

## 💻 Software Overview

The application is split into four main logical parts:

1. **Wi-Fi Manager**  
   Initializes the ESP32 Wi-Fi interface and connects to the configured network.

2. **DHT11 Manager**  
   A FreeRTOS task that periodically wakes up, queries the sensor, and stores the latest reading.

3. **Sensor Data Store**  
   A thread-safe shared data structure (protected with a **mutex**) that holds the latest valid temperature and humidity values.

4. **HTTP Server**  
   A lightweight `esp_http_server` instance that serves the latest sensor values when a client visits the ESP32’s IP address.

---

## ⚙️ Configuration
The project is fully configurable via the ESP-IDF configuration menu.

1. Open the menu:
    ```bash
    idf.py menuconfig
    ````

2. Navigate to App Configuration.

3. Modify the following parameters:
    * DHT11 GPIO Pin: The pin connected to the sensor data line.
    * Sensor Read Period (ms): Frequency of sensor updates (e.g., 2000ms).
    * WiFi SSID/Password: Credentials for your local network.

## ⚠️ Compatibility Note (ESP-IDF v6.0+)
At the time this project was created, the required **DHT11** library may not be updated for use with **ESP-IDF v6.0+**.

To fix this, update the `CMakeLists.txt` file inside the managed component folder for the DHT11 dependency:

Replace this:
```cmake
idf_component_register(SRCS "esp32-dht11.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver)
```

With this
```cmake
idf_component_register(SRCS "esp32-dht11.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES esp_driver_gpio)
```

## 📦 Installation & Flashing
```bash
# 1. Clone the repository
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name

# 2. Set the target (esp32, esp32s3, etc.)
idf.py set-target esp32

# 3. Build the project
idf.py build

# 4. Flash and Monitor
idf.py -p [PORT] flash monitor
```

## 📚 Third-Party Libraries
This project makes use of the following open-source library to interface with the sensor:

[esp32-dht11](https://github.com/abdellah2288/esp32-dht11)
    * Author: [abdellah2288](https://github.com/abdellah2288/)
    * Description: This library provides the critical timing logic and bit-banging required to read the 1-wire protocol used by DHT11 sensors on the ESP32.
    * Contribution: It is used within the dh11_manager.c to abstract the low-level data pulses into float values.