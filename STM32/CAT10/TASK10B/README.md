## TASK 10B: Exploring ESP8266 AT Commands for Wi-Fi Configuration

### 1. Circuit Diagram

The STM32 communicates with the Wemos D1 Mini (ESP8266) through USART1. USART2 is used to forward the modem responses to a PC terminal for monitoring.

[Circuit Diagram](circuit.png)

**Connections:**

| STM32 Pin | Wemos D1 Mini Pin | Purpose |
|---|---|---|
| PA9 (USART1 TX) | RX | Sends AT commands |
| PA10 (USART1 RX) | TX | Receives modem responses |
| GND | GND | Common ground |

USART2 is connected to the PC through the board's serial interface for displaying the responses.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 communicates with the ESP8266 Wi-Fi modem using AT commands over USART1. The modem responses are received by the STM32 and forwarded to the PC terminal through USART2.

The program explores different AT commands to check modem communication, configure Wi-Fi station mode, connect to a wireless access point, and retrieve network IP address information.

**AT Commands Used:**

| AT Command | Purpose |
|---|---|
| `AT` | Checks communication with the ESP8266 |
| `AT+CWMODE=1` | Configures the ESP8266 in station mode |
| `AT+CWJAP="SNUC","<Wi-Fi password>"` | Attempts to connect to the specified Wi-Fi access point |
| `AT+CIFSR` | Retrieves the IP address information |

**Pseudocode:**

1. Initialize the HAL library and configure the system clock.
2. Initialize GPIO, USART1 and USART2.
3. Declare the AT command strings and receive buffer.
4. Send the `AT` command through USART1.
5. Receive and forward the modem response to the PC terminal.
6. Send `AT+CWMODE=1` to configure station mode.
7. Receive and display the response.
8. Send `AT+CWJAP` with the Wi-Fi SSID and password to attempt access point connection.
9. Receive and display the connection response.
10. Send `AT+CIFSR` to retrieve IP address information.
11. Receive and forward the response to the PC terminal.

**Code Base:**

The program is developed in Embedded C using STM32 HAL libraries.

- `HAL_Init()` initializes the HAL library.
- `SystemClock_Config()` configures the system clock.
- `MX_USART1_UART_Init()` initializes USART1 for communication with the ESP8266.
- `MX_USART2_UART_Init()` initializes USART2 for PC terminal communication.
- `HAL_UART_Transmit()` sends AT commands and forwards modem responses.
- `HAL_UART_Receive()` receives responses from the ESP8266.
- `memset()` clears the receive buffer before each command.
- `strlen()` determines the length of command and response strings.
- `HAL_Delay()` introduces delays between successive AT commands.

Both UART peripherals are configured for 115200 baud, 8 data bits, no parity and 1 stop bit.

### 3. Inference

The experiment demonstrates the use of ESP8266 AT commands through UART communication with an STM32 microcontroller. The modem is configured in station mode, instructed to connect to a Wi-Fi access point, and queried for IP address information. The received responses are forwarded to a PC terminal, allowing the modem configuration and communication process to be monitored.