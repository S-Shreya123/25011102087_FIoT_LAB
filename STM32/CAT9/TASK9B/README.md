# CAT9 – Task 9B: UART Command-Controlled LED on STM32F103C8T6

## Experiment Overview

This experiment demonstrates UART-based command communication using the STM32F103C8T6 (Blue Pill) microcontroller.

The microcontroller receives text commands through USART1 from a PC serial terminal. Each command is collected character by character and processed when a newline character is received. Based on the command, the onboard LED connected to PC13 is turned ON, turned OFF, or toggled.

The experiment introduces serial communication, string-based command parsing, and GPIO control using STM32 HAL functions.

## Hardware Setup

| Component | Specification |
|---|---|
| Microcontroller | STM32F103C8T6 (Blue Pill) |
| Architecture | ARM Cortex-M3 |
| Development Environment | STM32CubeMX / Keil µVision |
| Programming Interface | ST-Link V2 |
| Communication Interface | USART1 |
| UART Transmit Pin | PA9 (USART1_TX) |
| UART Receive Pin | PA10 (USART1_RX) |
| LED | Onboard LED (PC13) |
| Serial Adapter | USB-to-Serial Adapter |
| Operating Voltage | 3.3V |

## Hardware Connections

| STM32 Pin | Connection |
|---|---|
| PA9 (USART1_TX) | RX of USB-to-Serial Adapter |
| PA10 (USART1_RX) | TX of USB-to-Serial Adapter |
| PC13 | Onboard LED |
| GND | Common GND |
| 3.3V | Power through ST-Link |

**Connection Notes:**
- Connect PA9 (TX) to the adapter's RX pin.
- Connect PA10 (RX) to the adapter's TX pin.
- Connect the grounds of the Blue Pill and serial adapter.
- Use a USB-to-Serial adapter compatible with the STM32's 3.3V UART logic.
- The onboard LED is connected to PC13 and operates in active-low mode.
- The Blue Pill is powered at 3.3V through the ST-Link.

## Circuit Diagram

[Circuit Diagram](circuit.png)

## USART1 Configuration

USART1 is used for bidirectional serial communication between the STM32 and the PC.

| Parameter | Configuration |
|---|---|
| Peripheral | USART1 |
| TX Pin | PA9 |
| RX Pin | PA10 |
| Communication | UART |
| Serial Adapter | USB-to-Serial |
| Baud Rate | As configured in the project |

The PC serial terminal sends text commands to the microcontroller, while USART1 receives the incoming data.

## Command Processing

The program receives commands one character at a time using `HAL_UART_Receive()`.

Characters are stored in a buffer until a carriage return (`\r`) or newline (`\n`) is detected. At that point, the buffer is null-terminated and compared against the supported commands using `strcmp()`.

### Supported Commands

| UART Command | LED Behaviour |
|---|---|
| `LED ON` | Turns the onboard LED ON |
| `LED OFF` | Turns the onboard LED OFF |
| `LED TOGGLE` | Changes the current LED state |

**Command Processing Steps:**

1. Receive one character through USART1.
2. Check whether the received character is a carriage return or newline.
3. If it is a normal character, append it to the command buffer.
4. If a command terminator is received, add the null character (`\0`) to the buffer.
5. Compare the received string with the supported commands.
6. Execute the corresponding LED operation.
7. Reset the buffer index to prepare for the next command.

## LED Control

The onboard LED is connected to PC13 and uses active-low logic.

| GPIO Operation | LED State |
|---|---|
| PC13 LOW | ON |
| PC13 HIGH | OFF |
| `HAL_GPIO_TogglePin()` | Toggles current state |

The LED responds to the commands received through USART1.

## Implementation Snippet

The following code illustrates the command reception and processing logic:

```c
HAL_UART_Receive(&huart1, &rx, 1, HAL_MAX_DELAY);

if (rx == '\r' || rx == '\n')
{
    buffer[index] = '\0';

    if (strcmp(buffer, "LED ON") == 0)
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    else if (strcmp(buffer, "LED OFF") == 0)
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    else if (strcmp(buffer, "LED TOGGLE") == 0)
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

    index = 0;
}
else
{
    buffer[index++] = rx;
}
```

## Programming Concepts

- STM32 HAL programming
- USART1 configuration and serial communication
- UART data reception using `HAL_UART_Receive()`
- Character-by-character data handling
- String buffering and null termination
- Command parsing using `strcmp()`
- GPIO output control
- Active-low LED operation
- Serial terminal communication and debugging

## Observations

- Text commands sent from the PC terminal are received through USART1.
- Incoming characters are accumulated until a newline or carriage return is detected.
- `LED ON` turns the onboard LED ON.
- `LED OFF` turns the onboard LED OFF.
- `LED TOGGLE` changes the current LED state.
- The buffer index is reset after each completed command.

## Conclusion

The experiment demonstrates UART-based command control of an onboard LED using the STM32F103C8T6. By receiving serial data, assembling complete commands, and processing them using string comparison, the microcontroller can perform GPIO operations based on instructions sent from a PC terminal.

This provides practical experience with USART communication, command parsing, string handling, and GPIO control using STM32 HAL.