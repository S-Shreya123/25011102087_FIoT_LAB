# CAT8 – Task 8B: Push Button Controlled LED Using GPIO on STM32F103C8T6

## Experiment Details

| Field | Description |
| :--- | :--- |
| **Experiment ID** | CAT8 |
| **Date** | 24/09/2026 |
| **Experiment Name** | Push Button Controlled LED Using GPIO |
| **Task Number** | Task 8B |
| **Microcontroller** | STM32F103C8T6 (Blue Pill) |
| **Architecture** | ARM Cortex-M3 |
| **Programming Language** | Embedded C |

## Objective

To implement basic GPIO input and output control using the STM32F103C8T6 microcontroller. An external push button connected to PB13 is used to control the onboard LED connected to PC13. The experiment demonstrates active-low input handling, GPIO configuration, and polling-based control using STM32 HAL functions.

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
- Connect the other terminal of the button to GND.
- PB13 uses the internal pull-up configuration, so no external pull-up resistor is required.
- The onboard LED is connected to PC13 and operates in active-low mode.
- The Blue Pill is powered with 3.3V through the ST-Link V2.

## GPIO Configuration

| Pin | Mode | Behaviour |
| :--- | :--- | :--- |
| PB13 | Input Pull-Up | Reads push button state |
| PC13 | Output Push-Pull | Controls onboard LED |

### Active-Low Operation

- When the button is released, PB13 reads HIGH.
- When the button is pressed, PB13 reads LOW.
- PC13 LOW turns the onboard LED ON.
- PC13 HIGH turns the onboard LED OFF.

## Working Principle

The program uses a continuous polling mechanism to monitor the push button and control the onboard LED.

1. Initialize the HAL library and configure the system clock.
2. Configure PC13 as a GPIO output in push-pull mode.
3. Configure PB13 as a GPIO input with pull-up.
4. Enter the infinite loop.
5. Read the current state of PB13 using `HAL_GPIO_ReadPin()`.
6. If PB13 reads LOW, set PC13 LOW to turn the LED ON.
7. Otherwise, set PC13 HIGH to turn the LED OFF.
8. Repeat continuously.

The LED remains ON only while the push button is held down. Releasing the button turns the LED OFF.

## Program Flow

```text id="7bflow"
             Start
               |
               v
        Initialize HAL
               |
               v
      Configure System Clock
               |
               v
       Initialize GPIO Pins
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
       Read Button (PB13)
               |
               v
        Button Pressed?
          /       \
        Yes        No
         |          |
         v          v
     PC13 LOW    PC13 HIGH
     LED ON      LED OFF
         |          |
         |__________|
               |
               v
          Repeat Loop
```

## Implementation

The main control logic is implemented using STM32 HAL GPIO functions.

```c
while (1)
{
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    }
}
```

## Testing and Observations

The program was tested by pressing and releasing the external push button connected to PB13.

**Observed Results:**

- PB13 reads LOW when the push button is pressed.
- PB13 reads HIGH when the button is released.
- The onboard LED turns ON while the button is pressed.
- Releasing the button turns the LED OFF.
- The button state is continuously checked through polling in the main loop.

## Key Concepts Demonstrated

- STM32 HAL programming.
- GPIO input and output configuration.
- Input pull-up configuration.
- Active-low push button operation.
- Active-low LED control.
- Digital input reading using `HAL_GPIO_ReadPin()`.
- Digital output control using `HAL_GPIO_WritePin()`.
- Polling-based input handling.

## Inference

The experiment successfully demonstrated push-button-based LED control using GPIO on the STM32F103C8T6 microcontroller. PB13 was configured as an input with an internal pull-up, while PC13 was configured as an output to control the onboard LED.

## Conclusion

The experiment provided practical understanding of GPIO configuration, active-low signals, and STM32 HAL functions. The onboard LED responded directly to the external push button, demonstrating basic polling-based input handling and output control.