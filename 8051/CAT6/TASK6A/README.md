# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-6

**DATE:** 20/08/2026

**NAME OF EXP:** UART Initialization and Serial Character Transmission using AT89S52

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + USB-to-TTL Serial Converter + PC (PuTTY) + Keil µVision

---

## TASK 6A: UART Initialization and Character Transmission

### 1. Circuit Diagram

The AT89S52 communicates with a PC through a USB-to-TTL serial converter. The UART transmit and receive pins are connected to the corresponding pins of the converter.

**Connections:**
- AT89S52 **TXD (P3.1)** → USB-to-TTL **RXD**
- AT89S52 **RXD (P3.0)** → USB-to-TTL **TXD**
- Connect the grounds of the microcontroller board and converter.
- Connect the USB-to-TTL converter to the PC and open its COM port using PuTTY.

[Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The AT89S52 UART is configured for 8-bit asynchronous serial communication with a baud rate of 9600. Timer 1, operating in Mode 2 (8-bit auto-reload), generates the baud-rate timing.

The `transmit()` function places each character into the `SBUF` register. The microcontroller waits until the transmit interrupt flag (`TI`) is set, indicating that transmission is complete, and then clears the flag before sending the next character.

The main function repeatedly transmits a predefined string to the PC terminal.

**UART Configuration:**

- `SCON = 0x50` – Selects UART Mode 1 (8-bit UART) and enables reception.
- `TMOD = 0x20` – Configures Timer 1 in Mode 2 (8-bit auto-reload).
- `TH1 = 0xFD` and `TL1 = 0xFD` – Set the reload value for 9600 baud with an 11.0592 MHz crystal.
- `TR1 = 1` – Starts Timer 1.

**Pseudocode:**

1. Initialize the UART communication settings.
2. Configure Timer 1 in Mode 2 for baud-rate generation.
3. Load the timer registers with the value `0xFD`.
4. Start Timer 1.
5. Define a transmit function that:
   - Places a character in `SBUF`.
   - Waits until `TI` becomes 1.
   - Clears `TI` after transmission.
6. In the main loop, traverse the predefined string character by character.
7. Transmit each character using the transmit function.
8. Repeat the process continuously.

**Code Base:**

The program is implemented in Embedded C using Keil C51.

- `first()` initializes the UART and Timer 1 configuration.
- `transmit(char a)` sends an individual character through the UART and checks the transmission completion flag.
- `SBUF` is used to load the character for transmission.
- `TI` indicates completion of character transmission.
- `main()` continuously sends the predefined string to the PC terminal.

### 3. Inference

The experiment demonstrates UART initialization and serial data transmission using the AT89S52 microcontroller. The microcontroller successfully sends characters to a PC terminal through a USB-to-TTL interface using 9600-8-N-1 communication. The use of a separate transmission function makes the program modular and allows individual characters to be transmitted sequentially.