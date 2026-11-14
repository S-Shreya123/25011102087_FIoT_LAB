## TASK 10C: ESP8266 Wi-Fi Configuration and TCP Server Setup

### 1. Circuit Diagram

The STM32 microcontroller communicates with the Wemos D1 Mini (ESP8266) through USART1. USART2 is used to forward modem responses to the PC terminal for monitoring.

[Circuit Diagram](circuit.png)

**Connections:**

| STM32 Pin | Wemos D1 Mini Pin | Purpose |
|---|---|---|
| PA9 (USART1 TX) | RX | Sends AT commands |
| PA10 (USART1 RX) | TX | Receives modem responses |
| GND | GND | Common ground |

USART2 provides the serial communication interface between the STM32 and PC terminal.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 configures the ESP8266 Wi-Fi modem using AT commands transmitted through USART1. The modem responses are received and forwarded to the PC terminal through USART2.

After establishing basic communication, the ESP8266 is configured in station mode and instructed to connect to a Wi-Fi access point. The program then retrieves the assigned IP address, enables multiple TCP connections, and starts a TCP server on port 80.

**AT Commands Used:**

| AT Command | Purpose |
|---|---|
| `AT` | Checks communication with the ESP8266 |
| `AT+CWMODE=1` | Configures Wi-Fi station mode |
| `AT+CWJAP="SNUC","<Wi-Fi password>"` | Attempts to connect to the Wi-Fi access point |
| `AT+CIFSR` | Retrieves IP address information |
| `AT+CIPMUX=1` | Enables multiple TCP connections |
| `AT+CIPSERVER=1,80` | Starts a TCP server on port 80 |

**Pseudocode:**

1. Initialize the HAL library and configure the system clock.
2. Initialize GPIO, USART1 and USART2.
3. Declare AT command strings and a receive buffer.
4. Send the `AT` command to verify modem communication.
5. Configure the ESP8266 in station mode using `AT+CWMODE=1`.
6. Send the Wi-Fi credentials using `AT+CWJAP`.
7. Receive and display the connection response.
8. Retrieve the IP address using `AT+CIFSR`.
9. Enable multiple connections using `AT+CIPMUX=1`.
10. Start the TCP server on port 80 using `AT+CIPSERVER=1,80`.
11. Forward the modem responses to the PC terminal.

**Code Base:**

The program is developed in Embedded C using STM32 HAL libraries.

- `HAL_Init()` initializes the HAL library.
- `SystemClock_Config()` configures the system clock.
- `MX_USART1_UART_Init()` initializes USART1 for STM32–ESP8266 communication.
- `MX_USART2_UART_Init()` initializes USART2 for PC terminal communication.
- `HAL_UART_Transmit()` sends AT commands and forwards modem responses.
- `HAL_UART_Receive()` receives responses from