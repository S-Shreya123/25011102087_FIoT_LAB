# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-11  
**DATE:** 15/10/2026  
**NAME OF EXP:** HTTP Server using STM32–Wemos Wi-Fi Modem and AT Commands  
**HARDWARE SETUP:** STM32 Development Board + Wemos D1 Mini (ESP8266)  
**PLATFORM:** STM32CubeMX + Keil MDK

## TASK 11A: Configuring ESP8266 as a TCP Server

### 1. Circuit Diagram

The STM32 communicates with the Wemos ESP8266 module through UART1. UART2 is used to communicate with the PC terminal.

```text
       STM32 Board                  Wemos D1 Mini
      ┌─────────────┐              ┌─────────────┐
      │             │              │             │
      │ PA9 (TX)    ├─────────────►│ RX          │
      │ PA10 (RX)   │◄─────────────┤ TX          │
      │             │              │             │
      │ GND         ├──────────────┤ GND         │
      └─────────────┘              └─────────────┘

       STM32 USART2  ──────────────►  PC Terminal
```

[Circuit Diagram](circuit.png)

### 2. Core Logic

The STM32 configures the ESP8266 as a Wi-Fi station and establishes a TCP server using AT commands.

1. Initialize USART1 for communication with the ESP8266 and USART2 for the PC terminal.
2. Send `AT` to check whether the ESP8266 responds.
3. Configure station mode using `AT+CWMODE=1`.
4. Connect to the Wi-Fi network using `AT+CWJAP`.
5. Retrieve the assigned IP address using `AT+CIFSR`.
6. Enable multiple TCP connections using `AT+CIPMUX=1`.
7. Start the TCP server on port 80 using `AT+CIPSERVER=1,80`.

**AT Commands Used:**

| Command | Purpose |
|---|---|
| `AT` | Check communication with ESP8266 |
| `AT+CWMODE=1` | Set ESP8266 to station mode |
| `AT+CWJAP` | Connect to the Wi-Fi access point |
| `AT+CIFSR` | Retrieve the assigned IP address |
| `AT+CIPMUX=1` | Enable multiple TCP connections |
| `AT+CIPSERVER=1,80` | Start a TCP server on port 80 |

### 3. Inference

The STM32 communicates with the ESP8266 through UART and configures it using AT commands. The module connects to the specified Wi-Fi network, obtains an IP address, and starts a TCP server on port 80. This establishes the network-side setup required for the HTTP server implemented in the next task.