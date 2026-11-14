# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION-12  
**DATE:** 15/10/2026  
**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO and User Input Programming  
**HARDWARE SETUP:** STM32 NUCLEO-F401RE Development Board  
**PLATFORM:** STM32CubeMX + Keil MDK

## TASK 12A: On-board LED Bring-Up

### 1. Circuit Diagram

The on-board user LED (LD2) of the NUCLEO-F401RE is connected to PA5. No external LED connection is required.

**Hardware Configuration:**
- Microcontroller: STM32F401RE Cortex-M4
- LED: On-board user LED (LD2)
- GPIO Pin: PA5
- LED Configuration: Output Push-Pull

### 2. Core Logic

**Working Principle:**

The GPIO pin PA5 is configured as a digital output using STM32 HAL. The LED is turned ON by setting the pin HIGH and turned OFF by setting it LOW. A delay of one second is introduced between each state change to produce continuous blinking.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO peripherals.
4. Configure PA5 as an output.
5. Continuously:
   - Set PA5 HIGH to turn ON the LED.
   - Wait for 1 second.
   - Set PA5 LOW to turn OFF the LED.
   - Wait for 1 second.

**Code Base:**
- `HAL_Init()` – Initializes the HAL library.
- `SystemClock_Config()` – Configures the system clock.
- `MX_GPIO_Init()` – Initializes GPIO pins and configures PA5 as an output.
- `HAL_GPIO_WritePin()` – Controls the LED by setting or resetting PA5.
- `HAL_Delay(1000)` – Introduces a one-second delay between LED state changes.

### 3. Inference

The on-board LED of the STM32 NUCLEO-F401RE blinks continuously at a fixed interval. This verifies the GPIO output configuration and basic hardware functionality of the development board.