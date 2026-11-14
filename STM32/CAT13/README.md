# EXPERIMENT DETAILS

- **EXP:** 13
- **DATE:** 23/10/2026
- **NAME OF EXP:** BME280 Sensor Interfacing Using I²C and Bosch Sensor API
- **HARDWARE SETUP:** STM32 NUCLEO Development Board and BME280 Sensor
- **PLATFORM:** STM32CubeMX and Keil MDK using STM32 HAL and Bosch BME280 Sensor API

## TASK 13A: BME280 Sensor Interfacing and Data Acquisition Using I²C

### 1. Circuit Diagram

The BME280 sensor is interfaced with the STM32 development board using the I²C1 communication protocol.

**Connections:**
- BME280 VCC → 3.3V
- BME280 GND → GND
- BME280 SDA → STM32 I²C1 SDA
- BME280 SCL → STM32 I²C1 SCL

The sensor uses the I²C address `0x76` (7-bit address), represented as `0xEC` in the STM32 HAL API after shifting it left by one bit.

### 2. Core Logic and Code Base

**Working Principle:**

1. Initialize the STM32 peripherals, including I²C1, USART1 and USART2.
2. Configure the Bosch BME280 API with custom I²C read, write and delay functions.
3. Initialize the sensor using `bme280_init()`, which reads the chip ID and calibration data.
4. Configure temperature oversampling to 2×, pressure oversampling to 2× and humidity oversampling to 1×.
5. Set the filter coefficient to 2, standby time to 1000 ms and operating mode to normal.
6. Retrieve compensated temperature, pressure and humidity measurements using `bme280_get_sensor_data()`.
7. Convert pressure from Pa to hPa by dividing the pressure value by 100.
8. Format the sensor readings into a JSON string using `snprintf()`.
9. Transmit the generated JSON data through USART1 and USART2.
10. Repeat the measurement and transmission process at one-second intervals.

**Pseudocode:**

```text
START

Initialize HAL and system clock
Initialize GPIO, I2C1, USART1 and USART2

Configure Bosch BME280 device structure
Assign I2C read, write and delay functions

Initialize BME280 sensor

Configure:
    Temperature oversampling = 2x
    Pressure oversampling = 2x
    Humidity oversampling = 1x
    Filter coefficient = 2
    Standby time = 1000 ms
    Mode = Normal

WHILE true:
    Read compensated sensor data

    Convert pressure from Pa to hPa

    Generate JSON string containing:
        Temperature
        Humidity
        Pressure

    Transmit JSON through USART2
    Transmit JSON through USART1

    Wait for 1 second

END
```

**Code Base:**

- `main.c` – Initializes peripherals, configures the BME280 sensor, retrieves measurements, generates JSON data and transmits it through UART.
- `bme280.c` – Bosch sensor driver implementation.
- `bme280.h` – Bosch BME280 API declarations.
- `bme280_defs.h` – Sensor register definitions, constants and data structures.

### 3. Inference

The BME280 sensor was interfaced with the STM32 board using I²C1 and configured through the Bosch Sensor API. Compensated temperature, pressure and humidity readings were retrieved and formatted into JSON. The generated data was transmitted through USART1 and USART2 at one-second intervals.

This experiment demonstrates I²C-based sensor interfacing, sensor calibration and compensation using a vendor-provided API, and UART-based transmission of structured sensor data.