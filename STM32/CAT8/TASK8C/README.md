# CAT8 – Task 8C: Debounced Button with Short Press Toggle and Long Press Blink Mode

## Experiment Details

| Field | Description |
| :--- | :--- |
| **Experiment ID** | CAT8 |
| **Date** | 24/09/2026 |
| **Experiment Name** | Debounced Button with Short Press Toggle and Long Press Blink Mode |
| **Task Number** | Task 8C |
| **Microcontroller** | STM32F103C8T6 (Blue Pill) |
| **Architecture** | ARM Cortex-M3 |
| **Programming Language** | Embedded C |

## Objective

To implement reliable push-button handling using the STM32F103C8T6 microcontroller. The experiment uses software debouncing and time-based press detection to distinguish between short and long button presses.

- **Short Press:** Toggles the onboard LED once when the button is released.
- **Long Press:** Activates automatic LED blinking mode with a 500 ms interval.

## Hardware Requirements

| Component | Specification |
| :--- | :--- |
| Microcontroller | STM32F103C8T6 (Blue Pill) |
| Architecture | ARM Cortex-M3 |
| Development Environment | STM32CubeMX / Keil µVision |
| Programming Interface | ST-Link V2 |
| Operating Voltage | 3.3V |
| LED | Onboard LED (PC13) |
| Push Button | External push button (PB13) |
| Button Configuration | GPIO Input Pull-Up |

## Circuit Diagram

[Circuit Diagram](circuit.png)

### Hardware Connections

| Component | STM32 Pin | Configuration |
| :--- | :--- | :--- |
| External Push Button | PB13 | GPIO Input Pull-Up |
| Onboard LED | PC13 | GPIO Output Push-Pull |
| Power Supply | 3.3V | Through ST-Link |
| Ground | GND | Common ground |

**Connection Notes:**
- Connect one terminal of the external push button to PB13.
- Connect the other terminal to GND.
- PB13 uses the internal pull-up configuration.
- The onboard LED is connected to PC13 and operates in active-low mode.
- The Blue Pill is powered through the ST-Link V2 at 3.3V.

## GPIO Configuration

| Pin | Mode | Behaviour |
| :--- | :--- | :--- |
| PB13 | Input Pull-Up | Reads push button state |
| PC13 | Output Push-Pull | Controls onboard LED |

### Active-Low Operation

- Button released → PB13 reads HIGH.
- Button pressed → PB13 reads LOW.
- PC13 LOW → LED ON.
- PC13 HIGH → LED OFF.

## Working Principle

The program uses software debouncing and time-based press detection to process button inputs reliably.

### Software Debouncing

Mechanical push buttons can produce multiple rapid electrical transitions when pressed or released. These unwanted transitions are known as switch bounce.

To filter these transitions, the program uses `HAL_GetTick()` to measure how long the input remains stable.

The process is as follows:

1. Read the current button input.
2. Compare it with the previous reading.
3. Update the candidate timestamp whenever a change is detected.
4. Accept the new button state only after it remains stable for the configured debounce interval.

This ensures that button presses and releases are processed reliably.

### Short Press and Long Press Detection

The duration for which the button remains pressed determines the action.

| Button Action | Behaviour |
| :--- | :--- |
| Short Press | Toggles the LED once on release |
| Long Press | Activates automatic blinking mode |
| Blink Interval | 500 ms |

**Short Press:**
- Record the button press start time.
- If the button is released before the long-press threshold, toggle the LED once.

**Long Press:**
- Continuously check the duration of the button press.
- When the long-press threshold is exceeded, enable `blinkMode`.
- Toggle the LED automatically at 500 ms intervals.

A flag such as `longPressHandled` prevents the long-press action from being triggered repeatedly during the same press.

## LED Control Functions

The implementation uses helper functions to manage the active-low onboard LED.

| Function | Purpose |
| :--- | :--- |
| `LED_On()` | Turns the LED ON |
| `LED_Off()` | Turns the LED OFF |
| `LED_Toggle()` | Changes the current LED state |

These functions simplify LED control and keep the main program logic organized.

## Program Flow

```text id="8cflow"
              Start
                |
                v
         Initialize HAL
                |
                v
       Configure System Clock
                |
                v
         Initialize GPIO
                |
                v
       Configure PB13 as
        Input Pull-Up
                |
                v
       Configure PC13 as
       Output Push-Pull
                |
                v
            Main Loop
                |
                v
         Read Button State
                |
                v
       Perform Debouncing
        Using HAL_GetTick()
                |
                v
        Valid Button Press?
                |
                v
       Record Press Start Time
                |
                v
       Check Press Duration
                |
          Long Press?
          /        \
        Yes         No
         |           |
         v           v
    Enable Blink   Wait for
       Mode        Release
         |           |
         |           v
         |      Short Press?
         |           |
         |           v
         |       Toggle LED
         |           |
         |___________|
                |
                v
        Blink Mode Active?
          /         \
        Yes          No
         |            |
         v            |
    Toggle LED        |
     Every 500 ms     |
         |            |
         |____________|
                |
                v
           Repeat Loop
```

## Implementation Logic

The program uses `HAL_GetTick()` for software debouncing, press-duration measurement, and periodic LED toggling.

The main control logic includes:

- Tracking the stable button state.
- Recording the button press start time.
- Identifying short and long presses.
- Using `longPressHandled` to prevent repeated long-press detection.
- Enabling or disabling LED behaviour through state flags.
- Toggling the LED at 500 ms intervals when blinking mode is active.

## Testing and Observations

The program was tested by pressing and releasing the external push button connected to PB13.

**Observed Results:**

- Software debouncing filtered unwanted transitions caused by mechanical switch bounce.
- A short press toggled the LED once after release.
- A long press activated automatic blinking mode.
- The LED toggled at 500 ms intervals in blinking mode.
- The active-low configuration determined the GPIO output levels required to turn the LED ON and OFF.

## Key Concepts Demonstrated

- STM32 HAL programming.
- GPIO input and output configuration.
- Active-low button and LED operation.
- Software debouncing.
- Time measurement using `HAL_GetTick()`.
- Short-press and long-press detection.
- State-based control using flags.
- Periodic LED toggling.
- Embedded event handling.

## Inference

The experiment successfully demonstrated reliable push-button handling using GPIO on the STM32F103C8T6. Software debouncing and time-based press detection allowed the same button to perform different actions depending on how long it was held.

## Conclusion

The experiment provided practical experience with GPIO configuration, switch debouncing, time measurement using `HAL_GetTick()`, and short- and long-press detection. The implementation demonstrated how state-based control can be used to create multiple LED behaviours using a single push button.