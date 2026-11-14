# CAT6 – Task C: Interrupt-Driven UART Reception Using Ring Buffer

## Experiment Overview

This experiment demonstrates interrupt-driven UART communication using the AT89S52 microcontroller. Instead of continuously checking for incoming serial data, the microcontroller uses its serial interrupt to receive characters.

Received characters are stored temporarily in a 16-byte circular buffer. The main program retrieves these characters from the buffer and transmits them back to the PC terminal.

## Hardware Setup

| Component | Specification |
|---|---|
| Microcontroller | AT89S52 |
| Development Board | 8051 Universal Development Board |
| Programming Environment | Keil µVision |
| Operating Voltage | +5V |
| Crystal Frequency | 11.0592 MHz |
| Communication Interface | UART |
| Serial Converter | USB-to-TTL Converter |
| PC Terminal | PuTTY |
| Baud Rate | 9600 |
| Ring Buffer Size | 16 bytes |

## Hardware Connections

The AT89S52 communicates with the PC through a USB-to-TTL serial converter.

| AT89S52 Pin | USB-to-TTL Converter |
|---|---|
| P3.0 (RXD) | TX |
| P3.1 (TXD) | RX |
| GND | GND |

**Connection Notes:**
- The converter's TX pin connects to the microcontroller's RXD pin.
- The converter's RX pin connects to the microcontroller's TXD pin.
- Both devices must share a common ground.
- Use a TTL-level USB-to-serial converter compatible with the board's 5V logic.
- The USB-to-TTL converter connects to the PC through USB.

## Circuit Diagram

[Circuit Diagram](circuit.png)

## UART Configuration

UART communication is configured using the AT89S52's serial interface and Timer 1.

- Timer 1 operates in Mode 2 (8-bit auto-reload).
- UART operates in serial Mode 1.
- Baud rate is configured to 9600.
- The serial interrupt and global interrupt are enabled.
- Incoming data is received through the SBUF register.
- Serial interrupt handling is performed using interrupt number 4.

## Interrupt-Driven Reception

The program uses the serial interrupt to handle incoming characters.

1. Initialize the UART and configure Timer 1.
2. Enable the serial interrupt and global interrupts.
3. Wait for incoming serial data.
4. When a character arrives, the serial interrupt is triggered.
5. Read the received character from SBUF.
6. Store the character in the circular buffer.
7. Update the head index to the next buffer position.
8. Return from the interrupt and allow the main program to continue.

This approach avoids continuously polling the UART receive flag in the main program.

## Circular Buffer Implementation

A circular buffer is used to temporarily store received characters until the main program processes them.

The buffer has a total size of 16 bytes and uses two index variables:

| Variable | Purpose |
|---|---|
| Head | Indicates the next position where incoming data can be stored |
| Tail | Indicates the next position from which data can be retrieved |

**Buffer Characteristics:**
- Total buffer size: 16 bytes
- Usable capacity: 15 bytes
- One position is reserved to distinguish between full and empty states.
- The indices wrap around when they reach the end of the buffer.
- When the buffer is full, newly received characters are discarded.

The head index is updated by the interrupt routine, while the tail index is used by the main program to retrieve buffered characters.

## Main Program Operation

The main program continuously checks whether the circular buffer contains unread data.

When a character is available:

1. Retrieve the character from the position indicated by the tail index.
2. Update the tail index to the next buffer position.
3. Transmit the retrieved character through UART.
4. Continue checking for additional buffered characters.

This separates character reception from character processing and echo transmission.

## Source Files

| File | Description |
|---|---|
| `taskC.c` | UART initialization, serial interrupt handling, circular buffer management and character echo |
| `STARTUP.A51` | 8051 startup assembly file |
| `CAT6_TaskC.uvproj` | Keil µVision project file |
| `CAT6_TaskC.hex` | Generated HEX file for microcontroller programming |
| `circuit.png` | UART interface circuit diagram |

## Programming Concepts

- Bare-metal Embedded C programming
- Direct register-level programming
- UART configuration using SCON and SBUF
- Timer 1 Mode 2 for baud-rate generation
- Serial interrupt handling (interrupt 4)
- Interrupt-driven character reception
- Circular buffer implementation
- Head and tail index management
- Buffer overflow handling
- Serial communication and debugging using PuTTY

## Observations

- The serial interrupt is triggered when a character is received.
- Incoming characters are stored in the circular buffer.
- The head and tail indices manage buffer storage and retrieval.
- The main program retrieves buffered characters and echoes them to the PC terminal.
- When the buffer reaches its usable capacity, additional incoming characters are discarded.
- UART communication operates at 9600 baud.

## Conclusion

The experiment demonstrates interrupt-driven UART reception and circular buffer management using the AT89S52 microcontroller. By handling incoming data through a serial interrupt, the program avoids continuous polling and allows the main program to process received characters independently.

The implementation provides practical experience with UART configuration, interrupt handling, circular buffer operations, and asynchronous serial communication in embedded systems.