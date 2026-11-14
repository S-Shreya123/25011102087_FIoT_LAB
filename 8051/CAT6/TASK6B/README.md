# CAT6 – Task B: UART Character Reception and Echo

## Experiment Overview

This experiment demonstrates UART-based serial communication between an **AT89S52 microcontroller** and a PC. Characters entered through a serial terminal are received by the microcontroller and transmitted back to the PC using a polling-based UART echo mechanism.

## Hardware and Software Requirements

| Component | Specification |
|---|---|
| Microcontroller | AT89S52 |
| Development Board | 8051 Universal Development Board |
| Operating Voltage | +5V |
| Crystal Frequency | 11.0592 MHz |
| Communication Interface | UART |
| UART RX Pin | P3.0 (RXD) |
| UART TX Pin | P3.1 (TXD) |
| Serial Converter | USB-to-TTL Converter |
| PC Serial Terminal | PuTTY |
| Baud Rate | 9600 |
| Programming Environment | Keil µVision |
| Programming Language | Embedded C |

## Circuit Connections

The AT89S52 communicates with the PC through a USB-to-TTL serial converter.

| AT89S52 | USB-to-TTL Converter |
|---|---|
| P3.0 (RXD) | TX |
| P3.1 (TXD) | RX |
| GND | GND |

The USB-to-TTL converter connects to the PC through USB. The serial terminal is configured to communicate at **9600 baud**.

[Circuit Diagram](circuit.png)

## Working Principle

The program implements a simple UART echo mechanism using polling.

1. Initialize UART using Timer 1 in Mode 2.
2. Configure serial communication for 9600 baud.
3. Continuously monitor the RI (Receive Interrupt) flag.
4. When RI becomes 1, read the received character from SBUF.
5. Clear the RI flag.
6. Load the received character into SBUF to initiate transmission.
7. Wait until the TI (Transmit Interrupt) flag becomes 1.
8. Clear the TI flag and repeat the process.

This allows each character received from the PC to be transmitted back through UART.

## UART Configuration

- **Baud Rate:** 9600
- **Timer:** Timer 1
- **Timer Mode:** Mode 2 (8-bit auto-reload)
- **Serial Configuration:** 8-bit UART
- **Reception:** Polling using RI
- **Transmission:** Polling using TI

## Source Files

| File | Description |
|---|---|
| `taskB.c` | Embedded C program for UART character reception and echo |
| `STARTUP.A51` | 8051 startup assembly file |
| `CAT6_TaskB.uvproj` | Keil µVision project file |
| `CAT6_TaskB.hex` | Generated HEX file for microcontroller programming |
| `circuit.png` | UART interface circuit diagram |

## Programming Approach

The experiment uses bare-metal Embedded C programming with direct access to the 8051 UART registers.

Key concepts demonstrated:

- UART configuration using `SCON` and `SBUF`
- Timer 1 Mode 2 for baud-rate generation
- Character reception using the RI flag
- Character transmission using the TI flag
- Polling-based serial communication
- Serial communication testing using PuTTY

## Testing and Observations

The program was tested by entering characters through the PuTTY serial terminal.

Observed results:

- Characters entered in PuTTY are successfully received by the AT89S52.
- Each received character is transmitted back to the PC.
- The RI flag indicates the reception of a character.
- The TI flag indicates completion of character transmission.
- UART communication operates at 9600 baud.

## Inference

The experiment successfully demonstrates bidirectional serial communication between the AT89S52 microcontroller and a PC. The UART echo mechanism provides practical understanding of character reception, transmission, the RI and TI flags, and polling-based serial communication.