# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-9

**DATE:** 01/10/2026

**NAME OF EXP:** STM32 UART Communication and Character Echo using HAL

**HARDWARE SETUP / PLATFORM:** STM32 Nucleo Development Board + PC Terminal (PuTTY) + STM32CubeMX + Keil MDK

---

## TASK 9A: Basic UART Communication – Character Transmission and Echo

### 1. Circuit Diagram

The STM32 communicates with a PC terminal through a serial connection using USART2.

**Connections:**
- STM32 USART2 TX → USB-to-Serial RX
- STM32 USART2 RX → USB-to-Serial TX
- STM32 GND → USB-to-Serial GND
- Connect the USB interface to the PC and open the corresponding COM port using PuTTY.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The USART2 peripheral is configured for asynchronous serial communication using the STM32 HAL library. The UART configuration uses a baud rate of 115200, 8 data bits, no parity and 1 stop bit.

The program uses blocking HAL UART functions to transmit and receive one character at a time. The received character is stored in a buffer and transmitted back to the PC terminal, allowing the user to verify two-way serial communication.

**UART Configuration:**

| Parameter | Configuration |
|---|---|
| Peripheral | USART2 |
| Baud Rate | 115200 |
| Word Length | 8 bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | Transmit and Receive |
| Hardware Flow Control | None |

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO and USART2.
4. Configure USART2 for 115200-8-N-1 communication.
5. Declare a character buffer.
6. Continuously perform the following:
   - Receive one character from the PC terminal.
   - Transmit the received character back to the terminal.
7. Repeat the process.

**Code Base:**

The program is developed in Embedded C using STM32 HAL libraries.

- `HAL_Init()` initializes the HAL library and system tick.
- `SystemClock_Config()` configures the system clock.
- `MX_USART2_UART_Init()` configures USART2 communication parameters.
- `HAL_UART_Init()` initializes the UART peripheral.
- `HAL_UART_Receive()` receives one character from the PC terminal.
- `HAL_UART_Transmit()` sends the received character back to the PC.
- `main()` continuously executes the receive-and-echo operation.

### 3. Inference

The experiment demonstrates serial communication between an STM32 microcontroller and a PC terminal using USART2 and STM32 HAL functions. It introduces UART configuration, character transmission, reception and echo functionality. Blocking UART communication provides a simple way to verify data exchange between the microcontroller and the terminal.