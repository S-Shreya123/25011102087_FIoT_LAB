# CAT6 – Task B: UART Character Reception and Echo Using AT89S52

## Experiment Details

| Field | Description |
| :--- | :--- |
| **Experiment ID** | CAT6 |
| **Date** | 20/08/2026 |
| **Experiment Name** | UART Character Reception and Echo |
| **Task Number** | Task B |
| **Microcontroller** | AT89S52 |
| **Development Board** | 8051 Universal Development Board |
| **Programming Language** | Embedded C |

## Objective

To establish serial communication between the AT89S52 microcontroller and a PC using UART. The experiment implements a polling-based echo mechanism in which characters received from the PC are transmitted back through the UART interface.

## Hardware Requirements

| Component | Specification |
| :--- | :--- |
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

## Circuit Diagram

[Circuit Diagram](circuit.png)

### Hardware Connections

| AT89S52 | USB-to-TTL Converter | Description |
| :--- | :--- | :--- |
| P3.0 (RXD) | TX | Receives serial data from the PC |
| P3.1 (TXD) | RX | Transmits serial data to the PC |
| GND | GND | Common ground |

The USB-to-TTL converter connects to the PC through USB. PuTTY is used as the serial terminal with a baud rate of 9600.

**Note:** Use a TTL-level USB-to-Serial converter compatible with the AT89S52's 5V logic. Do not use an RS-232 interface directly.

## UART Configuration

| Parameter | Configuration |
| :--- | :--- |
| Baud Rate | 9600 |
| Timer | Timer 1 |
| Timer Mode | Mode 2 (8-bit auto-reload) |
| Serial Mode | Mode 1 (8-bit UART) |
| Reception | Polling using RI flag |
| Transmission | Polling using TI flag |

## Working Principle

The program implements UART-based character reception and echo using polling.

1. Initialize UART using Timer 1 in Mode 2.
2. Configure serial communication for 9600 baud.
3. Continuously monitor the RI (Receive Interrupt) flag.
4. When RI becomes 1, read the received character from the SBUF register.
5. Clear the RI flag.
6. Load the received character into SBUF to initiate transmission.
7. Wait until the TI (Transmit Interrupt) flag becomes 1.
8. Clear the TI flag.
9. Repeat the process for subsequent characters.

This allows every character received from the PC to be transmitted back through the UART interface.

## Program Flow

```text
        Start
          |
          v
    Initialize UART
          |
          v
  Configure Timer 1
      Mode 2
          |
          v
  Set Baud Rate: 9600
          |
          v
   Check RI Flag
          |
     RI = 1?
          |
          v
   Read SBUF
          |
          v
     Clear RI
          |
          v
  Write Character
      to SBUF
          |
          v
   Check TI Flag
          |
     TI = 1?
          |
          v
     Clear TI
          |
          v
    Repeat Process
```

## Source Files

| File | Description |
| :--- | :--- |
| `taskB.c` | Embedded C program for UART character reception and echo |
| `STARTUP.A51` | 8051 startup assembly file |
| `CAT6_TaskB.uvproj` | Keil µVision project file |
| `CAT6_TaskB.hex` | Generated HEX file for microcontroller programming |
| `circuit.png` | UART interface circuit diagram |

## Testing and Observations

The program was tested by entering characters through the PuTTY serial terminal.

**Observed Results:**

- Characters entered in PuTTY were successfully received by the AT89S52.
- Each received character was transmitted back to the PC.
- The RI flag indicated the reception of a character.
- The TI flag indicated the completion of character transmission.
- UART communication operated at 9600 baud.

## Key Concepts Demonstrated

- UART configuration using `SCON` and `SBUF` registers.
- Timer 1 Mode 2 for baud-rate generation.
- Character reception using the RI flag.
- Character transmission using the TI flag.
- Polling-based serial communication.
- Serial communication testing using PuTTY.

## Inference

The experiment successfully demonstrated bidirectional serial communication between the AT89S52 microcontroller and a PC. The UART echo mechanism provided practical understanding of character reception, transmission, RI and TI flags, and polling-based serial communication.

## Conclusion

UART communication was successfully established between the AT89S52 and the PC using a USB-to-TTL converter. The experiment demonstrated how the 8051 microcontroller can receive and retransmit serial data using its built-in UART peripheral and polling mechanism.