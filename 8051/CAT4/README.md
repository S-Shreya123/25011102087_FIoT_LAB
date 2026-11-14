# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-4

**DATE:** 06/08/2026

**NAME OF EXP:** Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK 4: Keypad-Based LED Control and Display System

### 1. Circuit Diagram

The experiment involves interfacing a 4×4 matrix keypad, four LEDs and a seven-segment display with the AT89S52 microcontroller.

- **Microcontroller:** AT89S52
- **Keypad:** 4×4 Matrix Keypad
- **Keypad GPIO Port:** Port 2
- **Row Connections:** P2.7, P2.6, P2.5, P2.4
- **Column Connections:** P2.3, P2.2, P2.1, P2.0
- **Seven-Segment Display:** Connected to Port 0
- **LED GPIO Port:** Port 1
- **Power Supply:** 5V DC

[Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The matrix keypad is used to provide input to the microcontroller. The program scans the keypad by checking its rows and columns to identify the pressed key. The corresponding value is displayed on the seven-segment display, while the LED output is controlled based on the selected key.

Different keys trigger different LED operations, including individual LED control, running patterns, binary counting, alternating patterns and blinking. A reset function clears the display and switches OFF all LEDs.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Define the keypad rows, columns, LED port and seven-segment display port.
3. Initialize the display and LEDs to their default states.
4. Scan the keypad to identify the pressed key.
5. Display the corresponding key value on the seven-segment display.
6. Execute the LED operation associated with the selected key:
   - **Keys 1–4:** Turn ON the corresponding LED.
   - **Key 5:** Generate a running LED pattern.
   - **Key 6:** Alternate between two LED patterns (1010 and 0101).
   - **Key 7:** Display a binary count from 0 to 15.
   - **Key 8:** Blink all four LEDs together.
   - **Key 9:** Turn OFF all LEDs.
   - **Key 0:** Reset the system.
7. Continue scanning the keypad for further inputs.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides the 8051 microcontroller register definitions.
- `#define segment P0` assigns Port 0 to the seven-segment display.
- `#define sw P2` assigns Port 2 to the matrix keypad.
- `#define led P1` assigns Port 1 to LED control.
- `keypad_scan()` identifies the pressed key by scanning the keypad rows and columns.
- `display_digit()` selects the appropriate segment pattern to display digits and hexadecimal characters.
- `delay()` generates software delays using nested loops.
- `mode1_alt()` produces a sequential running LED pattern.
- `mode2_bincount()` generates a four-bit binary count from 0 to 15.
- `mode3_altpattern()` alternates between two LED combinations.
- `mode4_altpattern()` switches all four LEDs ON and OFF together.
- `reset()` clears the seven-segment display and turns OFF the LEDs.
- The `switch` statement in `main()` selects the LED operation based on the keypad input.

### 3. Inference

The system accepts input through the matrix keypad, displays the corresponding key value on the seven-segment display and controls the LEDs according to the selected operation. The experiment demonstrates keypad interfacing, seven-segment display control, GPIO manipulation and implementation of different LED patterns using the AT89S52 microcontroller.