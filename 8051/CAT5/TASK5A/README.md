# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-5

**DATE:** 13/08/2026

**NAME OF EXP:** Hardware Timer-Based LED Control using 8051

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK 5A: Timer-Based LED Toggle using Timer 0

### 1. Circuit Diagram

The experiment uses Timer 0 of the AT89S52 microcontroller to generate periodic overflows and control an LED.

- **Microcontroller:** AT89S52
- **Timer:** Timer 0 (16-bit Mode 1)
- **Crystal Frequency:** 11.0592 MHz
- **LED GPIO Pin:** P3.1
- **Power Supply:** 5V DC

[Circuit Diagram](circuit.png)

**Connections:**

- Connect the LED to P3.1 through a current-limiting resistor.
- Connect the microcontroller to the 5V supply and common ground.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer 0 is configured in 16-bit Mode 1 and loaded with the initial value `0xFC66`. For a classic 12-clock 8051 operating with an 11.0592 MHz crystal, each machine cycle takes approximately 1.085 µs. Loading the timer with 922 counts produces an overflow interval of approximately 1 ms.

The program continuously monitors the Timer 0 overflow flag (`TF0`). On each overflow, the counter is incremented, the flag is cleared and the timer is reloaded. After 600 overflows, the LED connected to P3.1 is toggled and the counter is reset.

**Pseudocode:**

1. Include the 8051 register definition header file.
2. Assign the LED to Port 3, Pin 1.
3. Initialize the overflow counter to zero.
4. Configure Timer 0 in 16-bit Mode 1.
5. Load `TH0` and `TL0` with `0xFC` and `0x66`.
6. Start Timer 0.
7. Continuously check the overflow flag `TF0`.
8. When an overflow occurs:
   - Increment the counter.
   - Clear the overflow flag.
   - Reload the timer registers.
   - Restart Timer 0.
9. When the counter reaches 600, toggle the LED and reset the counter.
10. Repeat continuously.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides the 8051 register definitions.
- `sbit led = P3^1` assigns the LED to pin P3.1.
- `TMOD = 0x01` configures Timer 0 in 16-bit Mode 1.
- `TH0 = 0xFC` and `TL0 = 0x66` load the calculated timer value.
- `TR0 = 1` starts Timer 0.
- `TF0` is monitored to detect timer overflow.
- `cnt` counts the number of timer overflows.
- The timer is reloaded after each overflow.
- `led = ~led` toggles the LED when the counter reaches 600.

### 3. Inference

The experiment demonstrates hardware timer configuration, overflow monitoring and GPIO control using the AT89S52 microcontroller. Timer 0 provides a periodic timing reference, allowing the LED to be toggled without using software delay loops.