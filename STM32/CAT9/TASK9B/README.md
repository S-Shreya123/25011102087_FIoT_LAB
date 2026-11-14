# CAT9 – Task 9B: UART Command-Controlled LED Using STM32F103C8T6

## Experiment Details

| Parameter | Description |
|---|---|
| Experiment | CAT9 – Task 9B |
| Date | 01/10/2026 |
| Microcontroller | STM32F103C8T6 (Blue Pill) |
| Architecture | ARM Cortex-M3 |
| Development Environment | STM32CubeMX / Keil µVision |
| Communication Interface | USART1 |
| Programming Interface | ST-Link V2 |

## Objective

To establish UART communication between an STM32F103C8T6 microcontroller and a PC serial terminal using USART1. The experiment receives text commands from the PC and controls the onboard LED connected to PC13 based on the received command.

## Hardware Requirements

- STM32F103C8T6 (Blue Pill) development board
- USB-to-Serial adapter (3.3V-compatible)
- ST-Link V2 programmer/debugger
- USB cable
- PC with a serial terminal application

## Circuit Diagram

[Circuit Diagram](circuit.png)

## Hardware Connections

| STM32 Pin | Connection |
|---|---|
| PA9 (USART1_TX) | RX of USB-to-Serial adapter |
| PA10 (USART1_RX) | TX of USB-to-Serial adapter |
| PC13 | Onboard LED |
| GND | Common GND |
| 3.3V | Power through ST-Link |

### Connection Notes

- Connect PA9 (TX) to the RX pin of the USB-to-Serial adapter.
- Connect PA10 (RX) to the TX pin of the USB-to-Serial adapter.
- Connect the grounds of the Blue Pill and USB-to-Serial adapter.
- Use a serial adapter compatible with the STM32's 3.3V UART logic.
- The onboard LED is connected to PC13 and operates in active-low mode.
- The Blue Pill is powered at 3.3V through the ST-Link.

## USART1 Configuration

USART1 is used for serial communication between the STM32 and the PC.

| Parameter | Configuration |
|---|---|
| Peripheral | USART1 |
| TX Pin | PA9 |
| RX Pin | PA10 |
| Communication Mode | UART |
| Serial Adapter | USB-to-Serial |
| Baud Rate | As configured in the project |

The PC serial terminal sends commands to the microcontroller, which receives them through USART1.

## Working Principle

The program receives UART data one character at a time using `HAL_UART_Receive()`.

Each received character is stored in a command buffer until a carriage return (`\r`) or newline (`\n`) is detected. Once a command terminator is received, the buffer is null-terminated and compared against the supported commands using `strcmp()`.

Depending on the received command, the microcontroller performs the corresponding GPIO operation on PC13.

### Supported Commands

| UART Command | LED Behaviour |
|---|---|
| `LED ON` | Turns the onboard LED ON |
| `LED OFF` | Turns the onboard LED OFF |
| `LED TOGGLE` | Toggles the current LED state |

## LED Control

The onboard LED connected to PC13 uses active-low logic.

| GPIO Operation | LED State |
|---|---|
| PC13 LOW (`GPIO_PIN_RESET`) | ON |
| PC13 HIGH (`GPIO_PIN_SET`) | OFF |
| `HAL_GPIO_TogglePin()` | Toggles the LED state |

The LED responds to commands received through USART1.

## Program Flow

1. Initialize the microcontroller peripherals, GPIO, and USART1.
2. Wait for a character to arrive through USART1.
3. Receive one character using `HAL_UART_Receive()`.
4. Check whether the character is `\r` or `\n`.
5. If it is a normal character, append it to the command buffer.
6. If a command terminator is received, null-terminate the buffer.
7. Compare the completed command using `strcmp()`.
8. Execute the corresponding LED operation.
9. Reset the buffer index.
10. Continue waiting for the next command.

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

## Source Files

| File | Description |
|---|---|
| `main.c` | Contains UART command reception and LED control logic |
| `main.h` | Header file containing declarations |
| `startup` files | Startup and initialization support |
| `circuit.png` | Circuit connection diagram |

## Testing and Observations

- Text commands sent from the PC serial terminal are received through USART1.
- Incoming characters are accumulated in a buffer.
- Command processing begins when a carriage return or newline is detected.
- `LED ON` turns the onboard LED ON.
- `LED OFF` turns the onboard LED OFF.
- `LED TOGGLE` changes the current LED state.
- The command buffer index is reset after processing each completed command.

## Key Concepts

- STM32 HAL programming
- USART1 configuration and UART communication
- UART data reception using `HAL_UART_Receive()`
- Character-by-character data handling
- String buffering and null termination
- Command parsing using `strcmp()`
- GPIO output control
- Active-low LED operation
- Serial terminal communication and debugging

## Inference

The experiment demonstrates how UART communication can be used to receive text-based commands from a PC and translate them into hardware operations. It also illustrates the use of buffers and string comparison for processing serial commands.

## Conclusion

The experiment successfully demonstrates UART-based command control of an onboard LED using the STM32F103C8T6. By receiving serial data through USART1, assembling complete commands, and processing them using string comparison, the microcontroller can perform GPIO operations based on instructions sent from a PC terminal.

This experiment provides practical experience with USART communication, command parsing, string handling, and GPIO control using STM32 HAL.