# EXPERIMENT DETAILS

- **EXP:** 14
- **DATE:** 29/10/2026
- **NAME OF EXP:** MQTT Communication Using STM32 and ESP8266 with Custom-Built API
- **HARDWARE SETUP:** STM32 NUCLEO Development Board and ESP8266 Wi-Fi Module
- **PLATFORM:** STM32CubeMX and Keil MDK using STM32 HAL and Custom ESP8266 API (`ESPLib`)

## TASK 14A: Establishing MQTT Communication and Publishing Data Using ESP8266

### 1. Circuit Diagram

The ESP8266 Wi-Fi module is interfaced with the STM32 development board through USART1 communication.

[Circuit Diagram](circuit.png)

**Connections:**
- STM32 USART1 TX → ESP8266 RX
- STM32 USART1 RX → ESP8266 TX
- STM32 GND → ESP8266 GND
- ESP8266 powered using a suitable 3.3V supply

The UART communication is configured at a baud rate of 115200 with 8 data bits, no parity and 1 stop bit.

### 2. Core Logic and Code Base

**Working Principle:**

1. Initialize the STM32 HAL library and configure the system clock.
2. Initialize GPIO and USART1 for serial communication with the ESP8266.
3. Initialize the ESP8266 in Station Mode using `ESP8266_Init()`.
4. Connect the ESP8266 to the Wi-Fi network using `ESP8266_wifiConnect()`.
5. Establish a TCP connection with the MQTT broker `broker.emqx.io` on port `1883` using `ESP8266_portConnect()`.
6. Configure the MQTT client parameters:
   - Keep-alive interval: 500
   - Clean Session enabled
   - Client ID: `STM32_Publisher`
   - Username and password: Not configured
7. Connect to the MQTT broker using `MQTT_connectBroker()`.
8. Publish a message to the topic `stm32/shreyashivani/data` using QoS 0.
9. Repeat the publishing operation every one second.

**Pseudocode:**

```text
START

Initialize HAL
Configure system clock
Initialize GPIO and USART1

Initialize ESP8266 in Station Mode

Connect to Wi-Fi network
IF connection fails:
    Call Error_Handler()

Connect to MQTT broker using TCP
IF connection fails:
    Call Error_Handler()

Configure MQTT parameters:
    Keep-alive = 500
    Clean Session = Enabled
    Client ID = STM32_Publisher
    Username = NULL
    Password = NULL

Connect to MQTT broker

WHILE true:
    Publish message to MQTT topic
    Wait for 1 second

END
```

**Code Base:**

- `main.c` – Configures the STM32 peripherals, initializes the ESP8266, connects to Wi-Fi and the MQTT broker, and periodically publishes messages.
- `ESPLib.h` – Contains the declarations and definitions of the custom ESP8266 and MQTT API interfaces.
- `ESPLib.c` – Contains the implementation of the ESP8266 communication and MQTT functions.

### 3. Inference

The STM32 development board was configured to communicate with the ESP8266 module through USART1. Using the custom-built ESP8266 API, the module was initialized in Station Mode, connected to a Wi-Fi network and established a connection with the MQTT broker.

The STM32 application periodically publishes messages to a specified MQTT topic using QoS 0 at one-second intervals. This experiment demonstrates Wi-Fi connectivity, MQTT broker communication and periodic message publishing using an STM32-based system.

**Note:** The implemented code is an MQTT communication test that publishes a fixed text message. BME280 sensor interfacing, JSON generation from sensor readings and Node-RED analytics are not implemented in this code.