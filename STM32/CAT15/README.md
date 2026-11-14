# EXPERIMENT DETAILS

- **EXP:** 15
- **DATE:** 12/11/2026
- **NAME OF EXP:** Smart Indoor Comfort Advisor Using BME280, MQTT and Node-RED
- **HARDWARE SETUP:** STM32 NUCLEO Development Board, BME280 Sensor and ESP8266 / Wemos D1 Mini
- **PLATFORM:** STM32CubeMX, Keil MDK, Arduino IDE and Node-RED

## TASK 15A: BME280 Sensor Interfacing and MQTT Data Transmission

### 1. Circuit Diagram

The BME280 sensor is interfaced with the STM32 development board using the I²C1 protocol. The ESP8266 communicates with the STM32 through UART and forwards the sensor data to an MQTT broker over Wi-Fi.

[Circuit Diagram](circuit.png)

**Connections:**

**BME280 to STM32:**
- BME280 VCC → 3.3V
- BME280 GND → GND
- BME280 SDA → STM32 I²C1 SDA
- BME280 SCL → STM32 I²C1 SCL

**STM32 to ESP8266:**
- STM32 USART1 TX → ESP8266 UART RX
- STM32 GND → ESP8266 GND

The UART communication is configured at 115200 baud with 8 data bits, no parity and 1 stop bit. The ESP8266 uses its alternate UART pins through `Serial.swap()`.

### 2. Core Logic and Code Base

**Working Principle:**

1. Initialize the STM32 peripherals, including I²C1, USART1 and USART2.
2. Configure the Bosch BME280 API with I²C read, write and delay callback functions.
3. Initialize the BME280 sensor using `bme280_init()`.
4. Configure temperature and pressure oversampling to 2× and humidity oversampling to 1×.
5. Set the filter coefficient to 2, standby time to 1000 ms and operating mode to normal.
6. Retrieve compensated temperature, pressure and humidity readings using `bme280_get_sensor_data()`.
7. Convert pressure from Pa to hPa and construct a JSON payload using `snprintf()`.
8. Transmit the JSON data through USART1 and USART2.
9. The ESP8266 receives the UART data, identifies complete messages using the newline character and publishes them to the MQTT topic `sensor/bme280`.
10. Repeat the sensor reading and transmission process at one-second intervals.

**Example JSON Payload:**

```json
{
  "status": "success",
  "temperature": 28.45,
  "humidity": 62.30,
  "pressure": 1008.72
}
```

**Code Base:**

- `main.c` – Initializes STM32 peripherals, configures the BME280 sensor, obtains measurements, generates JSON and transmits it through UART.
- `bme280.c` – Bosch BME280 sensor driver implementation.
- `bme280.h` – BME280 API declarations.
- `bme280_defs.h` – Sensor register definitions and data structures.
- ESP8266 Arduino sketch – Establishes Wi-Fi and MQTT connections, receives JSON data through UART and publishes it to the MQTT broker.

### 3. MQTT Communication

The ESP8266 is configured in Wi-Fi Station Mode and connects to the MQTT broker.

**MQTT Configuration:**

| Parameter | Configuration |
|---|---|
| Broker | `broker.emqx.io` |
| Port | `1883` |
| Protocol | MQTT over TCP |
| Topic | `sensor/bme280` |
| Client ID | Generated using ESP8266 chip ID |

The `PubSubClient` library handles MQTT communication. The UART receive buffer stores incoming characters until a newline is received, after which the complete JSON message is published.

The ESP8266 also checks Wi-Fi and MQTT connectivity and attempts reconnection if either connection is lost.

## TASK 15B: Indoor and Outdoor Environmental Monitoring Using Node-RED

### 1. Project Overview

A separate Node-RED flow named **Smart Indoor Comfort Advisor** was developed to monitor indoor and outdoor environmental conditions and generate recommendations for improving indoor comfort.

The system uses:
- BME280 sensor readings received through MQTT for indoor conditions.
- OpenWeatherMap API for outdoor weather information.
- Node-RED Function nodes for data processing and comfort analysis.
- Dashboard 2.0 for displaying sensor readings and recommendations.

This flow is maintained separately from the existing Sun Personality dashboard.

### 2. Data Collection

**Indoor Sensor Data – BME280**

An MQTT input node receives sensor readings from the broker.

| Node | Purpose |
|---|---|
| `Indoor Sensor MQTT Input` | Receives BME280 data from topic `sensor/bme280` |
| `Parse Indoor Sensor JSON` | Converts incoming JSON into a JavaScript object |
| `Debug Indoor Sensor Data` | Displays received readings for testing |

The indoor readings include:
- Temperature (°C)
- Humidity (%)
- Pressure (hPa)

**Outdoor Weather Data – OpenWeatherMap**

An HTTP request is configured to retrieve outdoor weather information.

| Node | Purpose |
|---|---|
| `Fetch Outdoor Weather` | Triggers the weather request every 5 minutes |
| `Prepare Weather Request` | Prepares the incoming message |
| `Get Outdoor Weather` | Sends an HTTP GET request to OpenWeatherMap |
| `Parse Outdoor Weather JSON` | Converts the API response into a JavaScript object |
| `Debug Outdoor Weather Data` | Displays received weather information |

The outdoor data includes:
- Temperature (°C)
- Humidity (%)
- Pressure (hPa)
- Weather description
- Location name

### 3. Data Labelling

Two Change nodes identify the source of incoming data before passing it to the decision engine.

| Node | Configuration |
|---|---|
| `Label Indoor Data` | Sets `msg.topic` to `"indoor"` |
| `Label Outdoor Data` | Sets `msg.topic` to `"outdoor"` |

Both nodes connect to the same Function node for combined analysis.

### 4. Comfort Decision Engine

A Function node named `Indoor Comfort Decision Engine` processes the indoor and outdoor readings.

**Main Operations:**

1. Stores the latest indoor and outdoor readings using Node-RED flow context.
2. Identifies the incoming data source using `msg.topic`.
3. Extracts and converts sensor values into numbers.
4. Validates the required temperature and humidity readings.
5. Classifies indoor comfort based on temperature and humidity.
6. Generates cooling and ventilation recommendations.
7. Calculates indoor-outdoor temperature and humidity differences.
8. Prepares a combined output message for the dashboard.

**Comfort Classification:**

| Condition | Classification |
|---|---|
| Temperature above 30°C and humidity above 70% | Hot and Humid |
| Temperature above 30°C | Hot |
| Humidity above 70% | Humid |
| Humidity below 30% | Dry |
| Temperature below 20°C | Cold |
| Temperature above 26°C | Slightly Warm |
| Otherwise | Comfortable |

The conditions are evaluated in order, and the first matching condition determines the classification.

**Recommendations Generated:**

- **Cooling Advice:** Suggests suitable actions such as using a fan, AC or dehumidifier based on indoor conditions.
- **Window Recommendation:** Compares indoor and outdoor temperature and humidity to recommend opening or closing windows.
- **Ventilation Status:** Classifies ventilation opportunities as good, poor or limited.

The decision engine also calculates the difference between indoor and outdoor temperature and humidity.

### 5. Dashboard 2.0

A separate Dashboard 2.0 page named **Smart Indoor Comfort Advisor** displays environmental readings and recommendations through three groups.

**Indoor Conditions**
- Indoor Temperature Gauge
- Indoor Humidity Gauge

**Outdoor Conditions**
- Outdoor Temperature Gauge
- Outdoor Humidity Gauge

**Comfort Insights**
- Indoor Comfort Status
- Cooling Advice
- Window Ventilation Advice
- Ventilation Status

The gauges display the corresponding indoor and outdoor measurements, while the text widgets display the recommendations generated by the decision engine.

### 6. Overall System Flow

```text
                 INDOOR DATA
                      |
                    BME280
                      |
                 STM32 (I2C)
                      |
             Compensated Readings
                      |
                 JSON Payload
                      |
                USART1 / UART
                      |
                   ESP8266
                      |
                    Wi-Fi
                      |
                 MQTT Broker
                broker.emqx.io
                      |
              Topic: sensor/bme280
                      |
              Node-RED MQTT Input
                      |
              Parse Indoor JSON
                      |
              Label Indoor Data
                      |
                      +----------------------+
                                             |
                                             v
                                  Indoor Comfort Decision
                                          Engine
                                             |
                         +-------------------+------------------+
                         |                   |                  |
                    Comfort Status     Cooling Advice      Window Advice
                                             |
                                      Ventilation Status
                                             |
                                             v
                                       Dashboard 2.0


                 OUTDOOR DATA
                      |
               OpenWeatherMap API
                      |
                 HTTP Request
                      |
              Parse Weather JSON
                      |
              Label Outdoor Data
                      |
                      +----------------------+
                                             |
                                             v
                                  Indoor Comfort Decision
                                          Engine
```

### 7. Inference

The BME280 sensor was interfaced with the STM32 development board using I²C to obtain compensated temperature, humidity and pressure readings. These measurements were formatted as JSON and transmitted through UART to the ESP8266, which forwarded the data to an MQTT broker.

Node-RED received the indoor sensor readings through MQTT and retrieved outdoor weather information using the OpenWeatherMap API. A Function node compared the two data sources, classified indoor comfort and generated cooling and ventilation recommendations.

The Dashboard 2.0 interface displayed indoor and outdoor environmental conditions along with the generated comfort insights. This experiment demonstrates sensor interfacing, UART communication, MQTT-based data transmission, cloud-based weather retrieval and real-time environmental monitoring using Node-RED.