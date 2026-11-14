# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 1

**DATE:** 23/07/2026

**NAME OF EXP:** 8051 Development Board Tool Chain Setup

**HARDWARE SETUP / PLATFORM:** 8051 Microcontroller + Keil µVision

---

## TASK 1: Bare-Metal LED Blink

### 1. Circuit Diagram

The experiment involves interfacing an LED with the 8051 microcontroller and controlling it through a GPIO pin.

- **Microcontroller:** 8051
- **GPIO Port:** Port 1
- **GPIO Pin:** P1.7
- **Peripheral:** LED with current-limiting resistor
- **Power Supply:** 5V DC

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The LED is connected to pin P1.7 of the 8051 microcontroller. The program alternates the pin's output between HIGH and LOW to switch the LED ON and OFF. A delay is introduced between these transitions using two nested `for` loops, producing a visible blinking effect.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Assign P1.7 as the LED control pin.
3. Define a delay function using nested loops.
4. Set the LED pin HIGH and introduce a delay.
5. Set the LED pin LOW and introduce another delay.
6. Repeat the process continuously.

**Code Base:**

The program is written in Embedded C using Keil µVision.

- `reg51.h` provides the 8051 register definitions.
- `sbit ledpin = P1^7` assigns the LED to pin P1.7.
- `ledpin = 1` sets the output HIGH, while `ledpin = 0` sets it LOW.
- `delay()` uses two nested loops with 400 and 500 iterations to generate a software delay.
- `while(1)` keeps the LED blinking continuously.

### 3. Inference

The LED connected to P1.7 blinks continuously as the output pin alternates between HIGH and LOW. The experiment demonstrates GPIO control and software delay generation using the 8051 microcontroller.