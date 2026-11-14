# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-3

**DATE:** 30/07/2026

**NAME OF EXP:** Timer-Based LED Pattern Generator and Button Interrupt Controller

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK 3: Four-Mode LED Control System

### 1. Circuit Diagram

The experiment involves interfacing four LEDs and a push-button with the AT89S52 microcontroller. The LEDs are controlled through Port 1, while the push-button is connected to Port 2.

- **Microcontroller:** AT89S52
- **GPIO Port for LEDs:** Port 1
- **LED Connections:** P1.1, P1.2, P1.3 and P1.4
- **GPIO Port for Switch:** Port 2
- **Switch Connections:** P2.0 and P2.5
- **Peripheral:** Four LEDs and a push-button
- **Power Supply:** 5V DC

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The program uses a four-state control system to operate the LEDs in different patterns. A push-button is used to switch between the four modes. Each valid button press increments the mode, and the system returns to the first mode after completing all four.

A software delay function controls the timing of LED transitions. The button input is checked periodically, with a delay and release check to avoid multiple mode changes from a single press.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Define the LED and switch pins.
3. Initialize all LEDs to the OFF state and configure the input port.
4. Detect button presses and increment the operating mode.
5. Execute the corresponding LED pattern based on the selected mode:
   - **Mode 1:** Turn ON one LED at a time in sequence.
   - **Mode 2:** Display a binary count from 0000 to 1111.
   - **Mode 3:** Alternate between the patterns 1010 and 0101.
   - **Mode 4:** Flash all four LEDs together between ON and OFF states.
6. Use software delays to control the pattern transitions.
7. Return to the main loop to check for the next button press.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides the 8051 microcontroller register definitions.
- `#define led P1` maps the LED output to Port 1.
- `sbit` is used to assign the switch connections to P2.0 and P2.5.
- The `delay()` function uses nested loops to generate software delays.
- `switch_mode()` detects button presses, performs basic debouncing and updates the current mode.
- `mode1_alt()` generates the running LED sequence.
- `mode2_bincount()` displays the binary counter using the four LEDs.
- `mode3_altpattern()` alternates between two LED patterns.
- `mode4_altpattern()` switches all four LEDs ON and OFF together.
- The `switch` statement in `main()` selects the appropriate function based on the current mode.

### 3. Inference

The four-mode LED controller operates according to the selected button input. Each button press advances the system to the next LED pattern, demonstrating GPIO interfacing, switch debouncing, state-based control and software delay generation using the AT89S52 microcontroller.