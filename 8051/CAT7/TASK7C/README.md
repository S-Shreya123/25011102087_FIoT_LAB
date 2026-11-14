# CAT7 – 16×2 LCD Driver Development and Dynamic Display Control

## Experiment Overview

This experiment focuses on interfacing a 16×2 character LCD and a 4×4 matrix keypad with the AT89S52 microcontroller. It covers LCD initialization, character and string display, cursor positioning, keypad scanning, and interactive character movement.

| Parameter | Details |
|---|---|
| Experiment | CAT7 |
| Date | 24/08/2026 (Week 6) |
| Microcontroller | AT89S52 |
| Development Board | 8051 Development Board |
| Display | 16×2 HD44780-compatible LCD |
| Input Device | 4×4 Matrix Keypad |
| LCD Interface | 4-bit GPIO Mode |
| Programming Language | Embedded C |
| IDE | Keil µVision |

## 1. Hardware Connections

The LCD and keypad are interfaced with the AT89S52 using Port 3 and Port 2 respectively.

### LCD Connections

| LCD Signal | AT89S52 Pin |
|---|---|
| RS | P3.2 |
| E | P3.3 |
| D4 | P3.4 |
| D5 | P3.5 |
| D6 | P3.6 |
| D7 | P3.7 |
| RW | GND |
| VSS | GND |
| VDD | +5V |
| V0 | Contrast potentiometer |

The LCD operates in 4-bit mode, using D4–D7 for data transfer. The RW pin is grounded for write-only operation.

### Keypad Connections

| Keypad Signal | AT89S52 Pin |
|---|---|
| Row 1 | P2.7 |
| Row 2 | P2.6 |
| Row 3 | P2.5 |
| Row 4 | P2.4 |
| Column 1 | P2.3 |
| Column 2 | P2.2 |
| Column 3 | P2.1 |
| Column 4 | P2.0 |

### Circuit Diagram

[Circuit Diagram](circuit.png)

*The diagram represents the pin connections derived from the submitted source files. Verify the physical board layout, supply connections and contrast circuit against the actual development board schematic.*

## 2. LCD Driver Implementation

The LCD driver is developed using GPIO-based 4-bit communication. It provides functions for initialization, command transmission, character output and cursor positioning.

The main routines include:

| Function | Purpose |
|---|---|
| `lcd_init()` | Initializes the LCD in 4-bit mode |
| `lcd_cmd()` | Sends instruction commands |
| `lcd_data()` | Transfers character data |
| `lcd_send_nibble()` | Sends the upper four bits to the LCD |
| `lcd_enable()` | Generates the LCD Enable pulse |
| `lcd_string()` | Displays a null-terminated string |
| `lcd_goto()` | Positions the cursor at a specified row and column |

The LCD configuration uses the following commands:

- `0x28` – 4-bit interface, 2-line display
- `0x0F` – Display ON, cursor ON and blinking cursor
- `0x06` – Increment cursor after writing
- `0x01` – Clear display

## 3. Keypad Scanning

The 4×4 matrix keypad is scanned by activating one row at a time and checking the column inputs.

The `keypad_scan()` function identifies the pressed key and returns its corresponding key code.

- Numeric keys return codes from 0 to 9.
- Keys A–D, `*` and `#` return codes from 10 to 15.
- A return value of 255 indicates that no key is detected.

This scanning method allows the microcontroller to identify the pressed key without requiring a separate input pin for every key.

## 4. Keypad-Controlled LCD Character Movement

The main application combines the LCD driver and keypad scanning functionality to move a `*` character across the LCD.

The initial character position is row 0, column 0.

| Key | Movement |
|---|---|
| 2 | Up |
| 8 | Down |
| 4 | Left |
| 6 | Right |

### Movement Logic

1. Initialize the LCD and keypad interface.
2. Display the `*` character at the initial position.
3. Scan the keypad for a pressed key.
4. Identify the corresponding movement direction.
5. Clear the previous character position by writing a space.
6. Update the row or column based on the pressed key.
7. Check the display boundaries before accepting the movement.
8. Display the character at its new position.
9. Introduce a delay between movement updates.

The character remains within the LCD's two-row, sixteen-column display area.

## 5. Source Files

| File | Description |
|---|---|
| `LCD.c` | LCD driver implementation and keypad-controlled character movement |
| `keypad.c` | 4×4 matrix keypad scanning routine |
| `delay.c` | Software delay implementation |
| `DAY6TASK1.uvproj` | Keil µVision project configuration |
| `STARTUP.A51` | 8051 startup assembly file |
| `circuit.png` | LCD and keypad circuit diagram |

## 6. Implementation Notes

- The LCD driver and character movement application are implemented in `LCD.c`.
- The LCD string-display routine is named `lcd_string()` in the submitted source rather than `lcd_puts()`.
- The submitted source does not include an `lcd_print_number()` implementation, although this function is specified in the Task 7B evaluation requirements.
- `LCD.c` calls `keypad_scan()` without including a keypad header or function prototype in the supplied source.
- `keypad.c` references `keypad.h`, while `delay.c` references `delay.h`. These header files were not included in the submitted ZIP.
- The directional movement functionality for Task 7C is present in the submitted implementation.
- The project uses direct GPIO programming and software delays, without Arduino APIs, HAL libraries or RTOS services.

## 7. Programming Concepts

- Bare-metal Embedded C programming
- AT89S52 GPIO interfacing
- 4-bit LCD communication
- LCD initialization and command handling
- DDRAM-based cursor positioning
- Character and string display
- 4×4 matrix keypad scanning
- Row-column input detection
- Conditional logic and display boundary checking
- Interactive character movement

## 8. Observations

- The LCD is configured to operate in 4-bit, 2-line mode.
- Text and characters can be displayed using dedicated LCD driver routines.
- The cursor can be positioned at specific display locations.
- The keypad scanning routine detects the pressed key and returns its corresponding code.
- Keys 2, 8, 4 and 6 control the character's movement.
- The previous character position is cleared before displaying the updated position.
- Movement is restricted to the available LCD boundaries.

## 9. Conclusion

The experiment demonstrates the development of a GPIO-based LCD driver and its integration with a 4×4 matrix keypad using the AT89S52 microcontroller.

The LCD driver supports initialization, command transmission, string display and cursor positioning, while the keypad scanning routine enables user input. These components are combined to implement an interactive application in which a character moves across the 16×2 LCD using directional keypad inputs.

The experiment provides practical experience with LCD interfacing, matrix keypad scanning, GPIO programming and the development of reusable Embedded C driver routines.