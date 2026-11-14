# CAT8 – Task 8C: Debounced Button with Short Press Toggle and Long Press Blink Mode

## Experiment Overview

This experiment demonstrates advanced GPIO input handling using the STM32F103C8T6 (Blue Pill) microcontroller.

An external push button connected to PB13 is used to control the onboard LED connected to PC13. The program implements software debouncing using `HAL_GetTick()` to filter out unwanted transitions caused by mechanical button bounce.

Two button actions are supported:

- **Short Press:** Toggles the LED state once when the button is released.
- **Long Press:** Activates an automatic LED blinking mode with a 500 ms interval.

## Hardware Setup

| Component | Specification |
|---|---|
| Microcontroller | STM32F103C8T6 (Blue Pill) |
| Architecture | ARM Cortex-M3 |
| Development Environment | STM32CubeMX / Keil µVision |
| Programming Interface | ST-Link V2 |
| Operating Voltage | 3.3V |
| LED | Onboard LED (PC13) |
| Push Button | External push button (PB13) |
| Button Configuration | GPIO Input Pull-Up |

## Hardware Connections

| Component | STM32 Pin | Configuration |
|---|---|---|
| External Push Button | PB13 | GPIO Input Pull-Up |
| Onboard LED | PC13 | GPIO Output Push-Pull |
| Power Supply | 3.3V | Through ST-Link |
| Ground | GND | Common ground |

**Connection Notes:**
- Connect one terminal of the external push button to PB13.
- Connect the other terminal to GND.
- PB13 uses an internal pull-up configuration.
- The onboard LED is connected to PC13 and operates in active-low mode.
- The Blue Pill is powered through the ST-Link at 3.3V.

## Circuit Diagram

[Circuit Diagram](circuit.png)

## GPIO Configuration

| Pin | Mode | Behaviour |
|---|---|---|
| PB13 | Input Pull-Up | Reads push button state |
| PC13 | Output Push-Pull | Controls onboard LED |

**Active-Low Operation:**
- Button released → PB13 reads HIGH.
- Button pressed → PB13 reads LOW.
- PC13 LOW → LED ON.
- PC13 HIGH → LED OFF.

## Software Debouncing

Mechanical push buttons can produce multiple rapid electrical transitions when pressed or released. These unwanted transitions are known as switch bounce.

To avoid false button detections, the program implements software debouncing using `HAL_GetTick()`.

The program:
1. Reads the current button input.
2. Compares it with the previous reading.
3. Updates the candidate timestamp whenever a change is detected.
4. Accepts the new button state only after it remains stable for the configured debounce interval.

This ensures that button presses and releases are processed reliably.

## Short Press and Long Press Detection

The program uses the time for which the button remains pressed to distinguish between the two actions.

| Button Action | Behaviour |
|---|---|
| Short Press | Toggles the LED once on release |
| Long Press | Activates automatic blinking mode |
| Blink Interval | 500 ms |

**Short Press:**
- The press start time is recorded.
- If the button is released before the long-press threshold, the LED state is toggled once.

**Long Press:**
- The duration of the button press is continuously checked.
- When the long-press threshold is exceeded, `blinkMode` is enabled.
- The LED automatically toggles every 500 ms.

A flag such as `longPressHandled` prevents the long-press action from being triggered repeatedly during the same press.

## Program Logic

1. Initialize the HAL library and system clock.
2. Configure PC13 as GPIO Output Push-Pull.
3. Configure PB13 as GPIO Input Pull-Up.
4. Read the button state and perform software debouncing.
5. Detect a valid button press and record its start time.
6. Check whether the button duration exceeds the long-press threshold.
7. If it is a long press, activate blinking mode.
8. If it is a short press, toggle the LED once after release.
9. When blinking mode is active, toggle the LED every 500 ms.
10. Continue monitoring the button and updating the LED behaviour.

## LED Control Functions

The implementation uses helper functions to manage the active-low onboard LED:

| Function | Purpose |
|---|---|
| `LED_On()` | Turns the LED ON |
| `LED_Off()` | Turns the LED OFF |
| `LED_Toggle()` | Changes the current LED state |

These functions simplify LED control and keep the main program logic easier to follow.

## Programming Concepts

- STM32 HAL programming
- GPIO input and output configuration
- Active-low button and LED operation
- Software debouncing
- Time measurement using `HAL_GetTick()`
- Short-press and long-press detection
- State-based control using flags
- Periodic LED toggling
- Embedded event handling

## Observations

- Software debouncing filters unwanted transitions caused by mechanical switch bounce.
- A short press toggles the LED once.
- A long press activates automatic blinking mode.
- The LED toggles at 500 ms intervals in blinking mode.
- The active-low configuration determines the GPIO output levels required to turn the LED ON and OFF.

## Conclusion

The experiment demonstrates reliable push-button handling using GPIO on the STM32F103C8T6. Software debouncing and time-based press detection allow the same button to perform different actions depending on how long it is held.

The implementation provides practical experience with GPIO configuration, switch debouncing, `HAL_GetTick()`, short- and long-press detection, and state-based LED control.