# CAT7 – Task 7B: LCD Cursor Positioning and Dynamic Value Update

## Experiment Details

| Parameter | Description |
|---|---|
| Experiment | CAT7 – Task 7B |
| Date | 24/08/2026 (Week 6) |
| Microcontroller | AT89S52 |
| Development Board | 8051 Universal Development Board |
| Display | 16×2 Character LCD |
| LCD Controller | HD44780 Compatible |
| Interface | 4-bit GPIO Mode |
| Operating Voltage | +5V |
| Crystal Frequency | As configured on the development board |
| Programming Environment | Keil µVision |
| Programming Language | Embedded C |

## Objective

To interface a 16×2 LCD with the AT89S52 microcontroller and implement functions for cursor positioning, string display and numerical value updates. The experiment uses these functions to create a continuously updating counter on the LCD.

## 1. Circuit Diagram

The LCD is interfaced with the AT89S52 through Port 3 using 4-bit communication.

[Circuit Diagram](circuit.png)

### LCD Pin Connections

| LCD Pin | AT89S52 Connection |
|---|---|
| RS | P3.2 |
| RW | GND |
| E | P3.3 |
| D4 | P3.4 |
| D5 | P3.5 |
| D6 | P3.6 |
| D7 | P3.7 |
| VSS | GND |
| VDD | +5V |
| V0 | Contrast potentiometer |

**Note:** The LCD data lines are connected to P3.4–P3.7. The lower nibble of Port 3 is preserved during data transfer, allowing the RS and E control pins to operate independently.

## 2. Working Principle

The program initializes the LCD in 4-bit mode and displays a counter that continuously increments.

The main execution sequence is:

1. Initialize the LCD and configure it for 4-bit communication.
2. Position the cursor at the beginning of the first row.
3. Display the text `Counter Value:`.
4. Move the cursor to the beginning of the second row.
5. Display the current counter value.
6. Write blank spaces after the number to remove any leftover digits.
7. Increment the counter.
8. Reset the counter to zero after it exceeds 99999.
9. Wait for 500 milliseconds before updating the display again.

## 3. LCD Driver Functions

The program implements reusable functions to simplify LCD operations.

| Function | Description |
|---|---|
| `delay_ms()` | Generates the required software delay |
| `lcd_enable()` | Generates the enable pulse for the LCD |
| `lcd_send_nibble()` | Sends a 4-bit data portion to the LCD |
| `lcd_cmd()` | Sends commands to the LCD |
| `lcd_data()` | Sends character data to the LCD |
| `lcd_init()` | Initializes the LCD in 4-bit mode |
| `lcd_goto(row, column)` | Positions the cursor at the specified location |
| `lcd_puts(str)` | Displays a string on the LCD |
| `lcd_print_number(value)` | Converts and displays an unsigned integer |

## 4. Cursor Positioning

The `lcd_goto(row, column)` function selects the required LCD location using DDRAM addresses.

- Row 0 starts at DDRAM address `0x80`.
- Row 1 starts at DDRAM address `0xC0`.
- The column value is added to the corresponding row address.

This allows text and numerical values to be displayed at specific positions without clearing the entire display.

## 5. Numerical Display and Dynamic Counter

The `lcd_print_number()` function converts an unsigned integer into individual decimal digits.

The conversion process uses:

- Modulo 10 to extract the last digit.
- Integer division by 10 to remove the extracted digit.
- A temporary array to store the digits.
- Reverse-order printing to display the number correctly.

The main function continuously updates the counter at the beginning of the second LCD row.

Blank spaces are printed after the counter value to overwrite any remaining digits from the previous value.

The counter resets to zero when it exceeds 99999.

## 6. Source Files

| File | Description |
|---|---|
| `task7B.c` | Contains the LCD driver functions and dynamic counter implementation |
| `STARTUP.A51` | 8051 startup assembly file |
| `CAT7_TaskB.uvproj` | Keil µVision project configuration |
| `CAT7_TaskB.hex` | Generated HEX file |
| `circuit.png` | LCD interfacing circuit diagram |

## 7. Programming Concepts

- Bare-metal Embedded C programming
- Direct Port 3 register manipulation
- 4-bit LCD interfacing
- LCD command and data transmission
- DDRAM-based cursor positioning
- String display
- Integer-to-character conversion
- Software delays
- Dynamic counter implementation

## 8. Observations

- The LCD initializes successfully in 4-bit mode.
- The first row displays the message `Counter Value:`.
- The second row displays the current counter value.
- The counter increments continuously at approximately 500 ms intervals.
- Previous digits are overwritten using blank spaces.
- The counter restarts from zero after reaching 99999.

## 9. Conclusion

The experiment demonstrates 4-bit LCD interfacing and dynamic data display using the AT89S52 microcontroller. Cursor positioning is achieved through DDRAM address commands, while dedicated functions handle string and numerical output.

A continuously updating counter is implemented to demonstrate how numerical values can be modified and refreshed at specific LCD positions without repeatedly initializing the display.