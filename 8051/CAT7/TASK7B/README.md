# CAT7 – Task 7B: LCD Cursor Positioning and Dynamic Value Update Using AT89S52

## Experiment Details

| Field | Description |
| :--- | :--- |
| **Experiment ID** | CAT7 |
| **Date** | 27/08/2026 |
| **Experiment Name** | LCD Cursor Positioning and Dynamic Value Update |
| **Task Number** | Task 7B |
| **Microcontroller** | AT89S52 |
| **Development Board** | 8051 Universal Development Board |
| **Display** | 16×2 Character LCD (HD44780 Compatible) |
| **Interface Mode** | 4-bit GPIO |
| **Programming Language** | Embedded C |

## Objective

To interface a 16×2 LCD with the AT89S52 microcontroller and implement reusable functions for cursor positioning, string display, and numerical value updates. These functions are used to create a continuously updating counter on the LCD.

## Hardware Requirements

| Component | Specification |
| :--- | :--- |
| Microcontroller | AT89S52 |
| Development Board | 8051 Universal Development Board |
| Display | 16×2 Character LCD |
| LCD Controller | HD44780 Compatible |
| Interface | 4-bit GPIO Mode |
| Operating Voltage | +5V |
| Crystal Frequency | As configured on the development board |
| Programming Environment | Keil µVision |
| Programming Language | Embedded C |

## Circuit Diagram

[Circuit Diagram](circuit.png)

### LCD Pin Connections

| LCD Pin | AT89S52 Connection | Description |
| :--- | :--- | :--- |
| RS | P3.2 | Register Select |
| RW | GND | Write-only operation |
| E | P3.3 | Enable |
| D4 | P3.4 | Data Line 4 |
| D5 | P3.5 | Data Line 5 |
| D6 | P3.6 | Data Line 6 |
| D7 | P3.7 | Data Line 7 |
| VSS | GND | Ground |
| VDD | +5V | Power supply |
| V0 | Contrast potentiometer | Display contrast adjustment |

**Connection Note:** The LCD operates in 4-bit mode using P3.4–P3.7 for data transfer. The RS and E control pins operate independently.

## Working Principle

The program initializes the LCD in 4-bit mode and displays a counter that continuously increments.

The main execution sequence is:

1. Initialize the LCD and configure it for 4-bit communication.
2. Position the cursor at the beginning of the first row.
3. Display the message `Counter Value:`.
4. Move the cursor to the beginning of the second row.
5. Display the current counter value.
6. Print blank spaces after the number to remove leftover digits from the previous value.
7. Increment the counter.
8. Reset the counter to zero when it exceeds 99999.
9. Wait for 500 milliseconds before updating the display again.

## LCD Driver Functions

The program implements reusable functions to simplify LCD operations.

| Function | Description |
| :--- | :--- |
| `delay_ms()` | Generates software delays |
| `lcd_enable()` | Generates the enable pulse for the LCD |
| `lcd_send_nibble()` | Sends a 4-bit data portion to the LCD |
| `lcd_cmd()` | Sends commands to the LCD |
| `lcd_data()` | Sends character data to the LCD |
| `lcd_init()` | Initializes the LCD in 4-bit mode |
| `lcd_goto(row, column)` | Positions the cursor at the specified location |
| `lcd_puts(str)` | Displays a string on the LCD |
| `lcd_print_number(value)` | Converts and displays an unsigned integer |

## Cursor Positioning

The `lcd_goto(row, column)` function positions the cursor using the LCD's DDRAM addresses.

- Row 0 starts at DDRAM address `0x80`.
- Row 1 starts at DDRAM address `0xC0`.
- The column value is added to the corresponding row address.

This allows text and numerical values to be displayed at specific positions without clearing the entire display.

## Numerical Display and Dynamic Counter

The `lcd_print_number()` function converts an unsigned integer into individual decimal digits before displaying it.

The conversion process uses:

1. Modulo 10 to extract the last digit.
2. Integer division by 10 to remove the extracted digit.
3. A temporary array to store the extracted digits.
4. Reverse-order printing to display the number correctly.

The main program continuously updates the counter at the beginning of the second LCD row.

Blank spaces are printed after the counter value to overwrite any remaining digits from the previous value. The counter resets to zero when it exceeds 99999.

## Program Flow

```text
          Start
            |
            v
       Initialize LCD
         in 4-bit mode
            |
            v
    Position Cursor (Row 0)
            |
            v
   Display "Counter Value:"
            |
            v
    Position Cursor (Row 1)
            |
            v
    Display Counter Value
            |
            v
     Print Blank Spaces
            |
            v
      Increment Counter
            |
            v
     Counter > 99999?
        /       \
      Yes        No
       |          |
       v          |
   Reset to 0     |
       |          |
       |__________|
            |
            v
      Delay 500 ms
            |
            v
       Repeat Loop
```

## Source Files

| File | Description |
| :--- | :--- |
| `task7B.c` | LCD driver functions and dynamic counter implementation |
| `STARTUP.A51` | 8051 startup assembly file |
| `CAT7_TaskB.uvproj` | Keil µVision project configuration |
| `CAT7_TaskB.hex` | Generated HEX file for microcontroller programming |
| `circuit.png` | LCD interfacing circuit diagram |

## Testing and Observations

The program was tested by running the firmware on the AT89S52 development board with the 16×2 LCD connected.

**Observed Results:**

- The LCD initialized successfully in 4-bit mode.
- The first row displayed the message `Counter Value:`.
- The second row displayed the current counter value.
- The counter incremented continuously at approximately 500 ms intervals.
- Previous digits were overwritten using blank spaces.
- The counter restarted from zero after exceeding 99999.

## Key Concepts Demonstrated

- Bare-metal Embedded C programming.
- Direct Port 3 register manipulation.
- 4-bit LCD interfacing.
- LCD command and data transmission.
- DDRAM-based cursor positioning.
- String display using reusable functions.
- Integer-to-character conversion.
- Software delay generation.
- Dynamic numerical display and counter implementation.

## Inference

The experiment successfully demonstrated 4-bit LCD interfacing and dynamic data display using the AT89S52 microcontroller. Cursor positioning was achieved through DDRAM address commands, while dedicated functions handled string and numerical output.

## Conclusion

The experiment provided practical understanding of LCD interfacing, cursor positioning, and numerical data conversion using Embedded C. A continuously updating counter was implemented to demonstrate how values can be refreshed at specific LCD positions without repeatedly initializing or clearing the display.