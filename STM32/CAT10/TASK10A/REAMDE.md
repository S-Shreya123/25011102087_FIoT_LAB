## TASK 10A: Establishing UART Communication Between STM32 and Wemos D1 Mini

### 1. Circuit Diagram

The STM32 microcontroller communicates with the Wemos D1 Mini (ESP8266) through UART. USART1 is used for communication with the Wemos, while USART2 is used to forward the received response to the PC terminal.

[Circuit Diagram](circuit.png)

**Connections:**

| STM32 Pin | Wemos D1 Mini Pin | Purpose |
|---|---|---|
| PA9 (USART1 TX) | RX | Transmits AT commands |
| PA10 (USART1 RX) | TX | Receives modem responses |
| GND | GND | Common ground |

USART2 is connected to the PC through the board's serial interface for displaying the received responses.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 communicates with the ESP8266 modem using UART and AT commands. The program first initializes USART1 and USART2, then transmits the basic `AT` command to the Wemos through USART1.

The ESP8266 processes the command and returns a response, typically `OK`, if communication is successful. The STM32 receives this response and forwards it to the PC terminal through USART2.

**UART Configuration:**

| Parameter | USART1 | USART2 |
|---|---|---|
| Purpose | STM32–Wemos communication | STM32–PC communication |
| Baud Rate | 115200 | 115200 |
| Word Length | 8 bits | 8 bits |
| Stop Bits | 1 | 1 |
| Parity | None | None |
| Mode | TX and RX | TX and RX |

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO, USART1 and USART2.
4. Declare the `AT` command and a receive buffer.
5. Transmit `AT\r\n` to the Wemos through USART1.
6. Receive the response from the ESP8266.
7. Forward the received response to the PC terminal through USART2.
8. Introduce a short delay.

**Code Base:**

The program is developed in Embedded C using STM32 HAL libraries.

- `HAL_Init()` initializes the HAL library.
- `SystemClock_Config()` configures the system clock.
- `MX_USART1_UART_Init()` initializes USART1 for communication with the Wemos.
- `MX_USART2_UART_Init()` initializes USART2 for PC terminal communication.
- `HAL_UART_Transmit()` transmits the AT command and forwards the received response.
- `HAL_UART_Receive()` receives the response from the ESP8266.
- `memset()` clears the receive buffer.
- `strlen()` calculates the command and response string lengths.
- `HAL_Delay()` introduces a delay between communication operations.

### 3. Inference

The experiment establishes UART communication between the STM32 microcontroller and the Wemos D1 Mini. The STM32 sends an AT command to the ESP8266, receives its response, and forwards it to the PC terminal. This verifies the basic serial communication interface required for further Wi-Fi modem configuration and data transmission.