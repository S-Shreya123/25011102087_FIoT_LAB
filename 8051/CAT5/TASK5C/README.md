# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-5

**DATE:** 13/08/2026

**NAME OF EXP:** Stepper Motor Control using AT89S52

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + Stepper Motor Driver + Stepper Motor + Keil µVision

---

## TASK 5C: Stepper Motor Rotation and Direction Control

### 1. Circuit Diagram

The experiment uses four GPIO pins of the AT89S52 microcontroller to control a stepper motor through a suitable motor driver.

- **Microcontroller:** AT89S52
- **Control Pins:** P3.0, P3.1, P3.2 and P3.3
- **Motor:** Four-phase stepper motor
- **Driver:** Compatible stepper motor driver
- **Power Supply:** As required by the motor and driver

[Circuit Diagram](circuit.png)

**Connections:**
- Connect P3.0–P3.3 to the four input pins of the motor driver.
- Connect the motor coils to the corresponding driver outputs.
- Provide a suitable external power supply to the motor driver.
- Ensure that the microcontroller and driver share a common ground.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The stepper motor is controlled by applying a sequence of digital signals to its four input lines. Different combinations of HIGH and LOW signals energize the motor phases in a specific order, causing the motor shaft to rotate.

The program implements an eight-step half-stepping sequence. The `rotate_right()` function applies the sequence in one direction, while `rotate_left()` applies the reverse sequence for rotation in the opposite direction.

A software delay is introduced between successive steps to allow the motor to respond to each change in the input pattern. The current main loop continuously calls `rotate_right()`, producing continuous rotation in one direction.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Assign four GPIO pins on Port 3 to the motor control inputs.
3. Define a delay function using nested loops.
4. Define the clockwise rotation function:
   - Apply the first motor input combination.
   - Introduce a delay.
   - Apply the next combination in the stepping sequence.
   - Repeat until all eight steps are completed.
5. Define the anticlockwise rotation function:
   - Apply the same stepping combinations in reverse order.
   - Introduce a delay between successive steps.
6. In the main function, continuously call the clockwise rotation function.
7. Repeat the sequence to maintain continuous motor rotation.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides the 8051 microcontroller register definitions.
- `IN1`, `IN2`, `IN3` and `IN4` represent the four motor control inputs connected to P3.0–P3.3.
- `delay()` generates a software delay using nested loops.
- `rotate_right()` generates an eight-step half-stepping sequence for rotation in one direction.
- `rotate_left()` generates the reverse eight-step sequence for rotation in the opposite direction.
- `main()` continuously calls `rotate_right()` to maintain continuous rotation.

### 3. Inference

The experiment demonstrates stepper motor interfacing and rotational control using GPIO pins of the AT89S52 microcontroller. By applying an ordered sequence of signals to the motor driver, the motor can be rotated in either direction. The experiment illustrates half-stepping, phase sequencing and the relationship between step intervals and motor speed.