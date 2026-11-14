# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-8

**DATE:** 24/09/2026

**NAME OF EXP:** STM32 GPIO Interfacing – Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** STM32 Development Board + Push Button + LED + STM32CubeMX + Keil MDK

---

## TASK 8A: GPIO Input/Output – Switch-Controlled LED

### 1. Circuit Diagram

The experiment interfaces a push button and an LED with the STM32 microcontroller using GPIO input and output pins.

[Circuit Diagram](circuit.png)

**Connections:**

- PA5 → Push-button input
- PB5 → LED output (through a current-limiting resistor)
- Push button connects PA5 to GND when pressed.
- PA5 uses the internal pull-up resistor.
- Connect the LED and microcontroller grounds appropriately.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 is configured to read the push-button state through GPIO pin PA5 and control an LED through GPIO pin PB5.

PA5 is configured as an input with an internal pull-up resistor. Therefore, the pin reads HIGH when the button is released and LOW when it is pressed.

The program continuously reads the input state using `HAL_GPIO_ReadPin()`. Based on the result, `HAL_GPIO_WritePin()` sets the LED output accordingly.

- Button released (HIGH) → LED OFF (LOW).
- Button pressed (LOW) → LED ON (HIGH).

**GPIO Configuration:**

| Pin | Configuration | Purpose |
|---|---|---|
| PA5 | Input with Pull-up | Reads push-button state |
| PB5 | Output Push-Pull | Controls LED |
 
**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize the GPIO peripherals.
4. Configure PA5 as an input with an internal pull-up.
5. Configure PB5 as a push-pull output.
6. Continuously read the state of PA5.
7. If PA5 is HIGH, set PB5 LOW.
8. If PA5 is LOW, set PB5 HIGH.
9. Repeat the process continuously.

**Code Base:**

The program is developed in Embedded C using STM32 HAL libraries.

- `HAL_Init()` initializes the HAL library and system tick.
- `SystemClock_Config()` configures the STM32 system clock.
- `MX_GPIO_Init()` enables GPIO port clocks and configures PA5 and PB5.
- `HAL_GPIO_ReadPin()` reads the push-button state.
- `HAL_GPIO_WritePin()` controls the LED output.
- `main()` continuously monitors the button and updates the LED state.

### 3. Inference

The experiment demonstrates basic GPIO input and output interfacing on an STM32 development board using HAL libraries. The push-button state is continuously monitored, and the LED output is controlled accordingly. It introduces GPIO configuration, internal pull-up resistors, digital input reading and output control.