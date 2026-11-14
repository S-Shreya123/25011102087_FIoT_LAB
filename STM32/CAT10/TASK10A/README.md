# CAT10 – Task 10A: ESP8266 Wi-Fi Module – AT Command Basic Test Using UART

## Experiment Details

| Field | Description |
| :--- | :--- |
| **Experiment ID** | CAT10 |
| **Date** | 09/10/2026 |
| **Experiment Name** | ESP8266 Wi-Fi Module – AT Command Basic Test Using UART on STM32F411RE |
| **Task Number** | TASK10A |
| **Microcontroller** | STM32F411RE (Nucleo-64), ARM Cortex-M4 |
| **Communication Protocol** | UART (USART6) |

## Objective

To establish UART communication between the STM32F411RE microcontroller and the ESP8266 Wi-Fi module using USART6. The ESP8266 is tested by transmitting the basic `AT` command and checking for its response.

## Hardware Requirements

- STM32F411RE Nucleo-64 development board
- ESP8266 Wi-Fi module
- USB-to-Serial adapter or ST-Link Virtual COM Port for monitoring
- 3.3V power supply
- Jumper wires

## Circuit Diagram

[Circuit Diagram](circuit.png)

### Hardware Connections

| STM32F411RE | ESP8266 | Description |
| :--- | :--- | :--- |
| PC6 (USART6_TX) | RX | STM32 transmits data to ESP8266 |
| PC7 (USART6_RX) | TX | STM32 receives data from ESP8266 |
| 3.3V | VCC | Power supply |
| 3.3V | CH_PD | Enables the ESP8266 module |
| GND | GND | Common ground |

**Important:** Ensure that the ESP8266 receives a stable 3.3V supply capable of handling its current requirements. Do not connect it to 5V.

## Software Configuration

- **Microcontroller:** STM32F411RE
- **UART Peripheral:** USART6
- **TX Pin:** PC6
- **RX Pin:** PC7
- **Baud Rate:** 115200
- **UART Mode:** Transmit and Receive
- **HAL Library:** STM32 HAL

## Working Principle

USART6 is configured to communicate with the ESP8266 Wi-Fi module at 115200 baud. The STM32 transmits the `AT` command followed by carriage return and newline characters.

The ESP8266 processes the command and sends back a response. A successful communication is indicated by the `OK` response.

## Program Flow

1. Initialize the HAL library and configure the system clock.
2. Initialize USART6 with a baud rate of 115200.
3. Transmit the `AT\r\n` command to the ESP8266.
4. Wait for 1 second to allow the module to process the command and respond.
5. Enter an infinite loop.

The response can be monitored separately through a UART passthrough or serial monitoring setup.

## Code Snippet

```c
uint8_t cmd1[] = "AT\r\n";

HAL_UART_Transmit(&huart6, cmd1, sizeof(cmd1) - 1, 2000);

HAL_Delay(1000);

while (1)
{
}
```

## Expected Output

When the ESP8266 is powered correctly and UART communication is configured properly, it responds to the transmitted command with:

```text
AT
OK
```

## Inference

The `AT` command was successfully transmitted from the STM32F411RE to the ESP8266 through USART6. The `OK` response confirmed that the ESP8266 was powered and responsive, and that UART communication was functioning correctly at 115200 baud.

## Repository Contents

| File | Description |
| :--- | :--- |
| `circuit.png` | Circuit diagram showing the STM32F411RE–ESP8266 connections |
| `main.c` | Main application code for transmitting the AT command |
| `Core/` | STM32 application source and header files, if included |
| `README.md` | Experiment documentation |

## Conclusion

The basic AT command test was successfully performed using USART6 on the STM32F411RE. This experiment establishes the foundation for further ESP8266-based Wi-Fi communication and IoT applications.