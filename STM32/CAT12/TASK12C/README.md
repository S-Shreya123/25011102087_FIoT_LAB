## TASK 12C: Short-Press and Long-Press Detection

### 1. Circuit Diagram

The NUCLEO-F401RE's on-board push button and user LED are used to implement short-press and long-press detection.

[Circuit Diagram](circuit.png)

**Hardware Configuration:**
- Microcontroller: STM32F401RE Cortex-M4
- Push Button: On-board user button (B1)
- Button GPIO: PC13
- LED: On-board user LED (LD2)
- LED GPIO: PA5

No external components are required.

### 2. Core Logic

**Working Principle:**

The push button connected to PC13 is monitored continuously. The program uses `HAL_GetTick()` to measure the time associated with button presses and distinguishes between short and long presses using a threshold of 500 milliseconds.

- **Short Press:** A press duration of less than 500 ms sets `led = 0` and executes the short-press LED pattern.
- **Long Press:** A press duration of 500 ms or more sets `led = 1` and executes the long-press LED pattern.

Different LED sequences are generated using GPIO output operations and timed delays. The program also checks for additional button presses while executing the patterns.

**Pseudocode:**

1. Initialize the HAL library and configure the system clock.
2. Initialize GPIO:
   - Configure PC13 as input.
   - Configure PA5 as output.
3. Initialize the LED mode variable.
4. Continuously monitor the push button.
5. When a button press is detected:
   - Wait for the button to be released.
   - Measure the elapsed time using `HAL_GetTick()`.
   - If the duration is at least 500 ms, select the long-press mode.
   - Otherwise, select the short-press mode.
6. Execute the corresponding LED pattern:
   - Short-press mode: Generate the short-press LED sequence.
   - Long-press mode: Generate the long-press LED sequence.
7. Continue monitoring for subsequent button presses.

**Code Base:**
- `HAL_GPIO_ReadPin()` – Detects button presses and releases through PC13.
- `HAL_GetTick()` – Provides millisecond timing for press-duration measurement.
- `HAL_GPIO_WritePin()` – Controls the on-board LED through PA5.
- `HAL_Delay()` – Generates timed intervals in the LED patterns.
- `led` – Stores the selected short-press or long-press mode.
- `prev` – Stores a tick-count reference for elapsed-time comparisons.
- `while()` – Continuously monitors the button and executes the selected LED sequence.

### 3. Inference

The STM32F401RE distinguishes between short and long button presses using a 500 ms threshold. Each press selects a corresponding LED pattern, demonstrating GPIO input handling, time-based event detection, and LED control using STM32 HAL functions.