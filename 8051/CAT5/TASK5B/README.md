# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-5

**DATE:** 13/08/2026

**NAME OF EXP:** Timer-Based LED Fading using Software PWM

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK 5B: LED Fading using Timer 0 and Software PWM

### 1. Circuit Diagram

The experiment uses Timer 0 of the AT89S52 microcontroller to generate timing intervals for software PWM-based LED brightness control.

- **Microcontroller:** AT89S52
- **Timer:** Timer 0 (16-bit Mode 1)
- **Crystal Frequency:** 11.0592 MHz
- **LED GPIO Pin:** P3.1
- **Power Supply:** 5V DC

**Connections:**
- Connect the LED to P3.1 through a current-limiting resistor.
- Connect the microcontroller to the 5V supply and common ground.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer 0 is configured in 16-bit Mode 1 and loaded with the initial value `0xFFA3`. The program uses the timer overflow flag (`TF0`) to control the HIGH and LOW states of the LED.

Software PWM is implemented by varying the duration for which the LED remains HIGH within a timer cycle. The `controller()` function accepts a brightness level and adjusts the switching threshold accordingly. This changes the duty cycle and produces different LED brightness levels.

The brightness level is gradually increased from 1 to 10 and then decreased back to 1. The `direction` variable determines whether the brightness sequence moves upward or downward, producing a continuous fading effect.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Assign the LED to Port 3, Pin 1.
3. Initialize the brightness counter and direction.
4. Configure Timer 0 in 16-bit Mode 1.
5. Load the timer registers with `0xFF` and `0xA3`.
6. Start Timer 0.
7. Call the `controller()` function with the current brightness level.
8. Inside the controller:
   - Select the switching threshold based on the brightness level.
   - Keep the LED HIGH while the timer count is within the selected range.
   - Switch the LED LOW when the threshold is crossed.
   - Wait for timer overflow.
   - Clear the overflow flag and reload the timer.
   - Repeat the process to generate the PWM pattern.
9. Increase or decrease the brightness counter based on the current direction.
10. Reverse the direction at the upper and lower brightness levels.
11. Continue the process to produce repeated LED fading.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides the 8051 microcontroller register definitions.
- `sbit led = P3^1` assigns the LED to pin P3.1.
- `count` stores the current brightness level.
- `direction` determines whether the brightness level increases or decreases.
- `TMOD = 0x01` configures Timer 0 in 16-bit Mode 1.
- `TH0 = 0xFF` and `TL0 = 0xA3` initialize the timer count.
- `TR0 = 1` starts Timer 0.
- `controller(int a)` generates the software PWM pattern according to the selected brightness level.
- Different threshold values are used for brightness levels 1 to 10.
- `TF0` is monitored to detect timer overflow.
- The timer is cleared and reloaded after each overflow.
- The main loop updates `count` and reverses `direction` at the brightness limits to create the fading sequence.

### 3. Inference

The experiment demonstrates LED brightness control using software PWM and the AT89S52 hardware timer. By varying the HIGH and LOW durations of the LED signal, different brightness levels are produced. Repeatedly increasing and decreasing the brightness level creates a continuous fading effect without using conventional software delay loops.