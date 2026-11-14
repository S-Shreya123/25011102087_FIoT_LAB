# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-7

**DATE:** 27/08/2026

**NAME OF EXP:** 16×2 LCD Initialization and Character Display using AT89S52

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 16×2 HD44780-Compatible LCD + Keil µVision

---

## TASK 7A: LCD Initialization and Character Display in 4-Bit Mode

### 1. Circuit Diagram

The 16×2 LCD is interfaced with the AT89S52 using four data lines and two control signals. The LCD operates in 4-bit mode, allowing data and commands to be transferred using D4–D7.

**Connections:**

- P3.4 → LCD D4
- P3.5 → LCD D5
- P3.6 → LCD D6
- P3.7 → LCD D7
- P3.3 → LCD Enable (E)
- P3.2 → LCD Register Select (RS)
- LCD RW → GND (write-only operation)
- LCD VSS → GND and VDD → +5V
- LCD V0 → Contrast adjustment potentiometer

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The LCD is initialized in 4-bit mode by sending commands through its four data pins. Each 8-bit command or character is transferred in two parts: the higher nibble followed by the lower nibble.

The RS pin determines whether the information sent is a command (`RS = 0`) or display data (`RS = 1`). The Enable pin is pulsed to allow the LCD to latch the transmitted nibble.

The initialization sequence configures the LCD's interface mode, display settings and entry mode. After initialization, the program manually sends character data through D4–D7 to display characters on the LCD.

**LCD Configuration:**

- **Interface:** 4-bit mode
- **Display:** 2-line mode
- **Font:** 5×8 dots
- **Function Set:** `0x28`
- **Display Control:** `0x0F`
- **Entry Mode:** `0x06`

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Assign Port 3 pins for LCD data and control signals.
3. Define a delay function for LCD timing.
4. Initialize the LCD:
   - Set RS to command mode.
   - Send the initialization nibbles.
   - Configure the LCD for 4-bit, 2-line operation.
   - Set display and entry mode configurations.
5. Set RS to data mode.
6. Send character data in two 4-bit nibbles.
7. Repeat the process to display the required characters.

**Code Base:**

The program is implemented in Embedded C using Keil C51.

- `D4`, `D5`, `D6` and `D7` represent the four LCD data lines connected to Port 3.
- `RS` selects between command and data transmission.
- `E` provides the Enable signal for transferring each nibble.
- `delay()` generates software delays between LCD operations.
- `lcd_init()` sends the initialization sequence and configures the LCD.
- `main()` manually sends command and character nibbles to the LCD.

### 3. Inference

The experiment demonstrates interfacing a 16×2 character LCD with the AT89S52 microcontroller using a 4-bit GPIO-based communication method. It illustrates LCD initialization, command and data selection, and the transfer of information through two successive nibbles. This provides a foundation for developing reusable LCD driver functions for cursor positioning and dynamic display updates.