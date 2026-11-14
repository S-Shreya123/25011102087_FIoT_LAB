## TASK 12B: On-board Switch Control with LED State Remembrance

### 1. Circuit Diagram

The NUCLEO-F401RE has an on-board push button connected to PC13 and an on-board user LED (LD2) connected to PA5. No external components are required.

**Hardware Configuration:**
- Push Button: On-board user button (B1)
- Button GPIO: PC13
- LED: On-board user LED (LD2)
- LED GPIO: PA5

### 2. Core Logic

**Working Principle:**

The push button is configured as a GPIO input, while PA5 is configured as a GPIO output. Since the button is active-low, pressing it makes PC13 read LOW.

The program checks for a button press, applies a short debounce delay, and waits for the button to be released. Once a valid press is detected, the LED state is toggled and retained even after the button is released.

**Pseudocode:**

1. Initialize the HAL library and configure the system clock.
2. Initialize GPIO pins:
   - Configure PC13 as input.
   - Configure PA5 as output.
3. Initialize the LED state variable.
4. Continuously monitor the push button.
5. When PC13 reads LOW:
   - Apply a short debounce delay.
   - Verify that the button is still pressed.
   - Wait until the button is released.
   - Toggle the LED state.
6. Update the LED output according to the stored state.

**Code Base:**
- `HAL_GPIO_ReadPin()` – Reads the push-button input on PC13.
- `HAL_Delay(10)` – Provides a short debounce delay.
- `HAL_GPIO_WritePin()` – Controls the LED connected to PA5.
- `led` – Stores the LED state between button presses.
- `while()` – Waits for button release to ensure one toggle per press.

### 3. Inference

The on-board push button successfully controls the LED on the NUCLEO-F401RE. Each valid button press toggles the LED between ON and OFF states. The LED retains its selected state after the button is released, demonstrating GPIO input handling, debouncing, and state management.