## TASK 11B: HTTP Request Detection and Response using ESP8266

### 1. Circuit Diagram

The STM32 communicates with the Wemos ESP8266 module through UART1. A browser on a device connected to the same Wi-Fi network accesses the ESP8266 server using its assigned IP address and port 80.

```text
       PC / Browser
             |
          Wi-Fi
             |
       Wemos D1 Mini
          ESP8266
             |
           UART
             |
        STM32 Board
```

[Circuit Diagram](circuit.png)

**Connections:**
- ESP8266 TX → STM32 UART1 RX
- ESP8266 RX → STM32 UART1 TX
- ESP8266 GND → STM32 GND
- STM32 UART2 → PC terminal for debugging and displaying messages

### 2. Core Logic

**Working Principle:**

After configuring the ESP8266 as a TCP server in Task 11A, the STM32 continuously monitors UART1 for incoming data from the module.

When a browser sends an HTTP request, the ESP8266 forwards the received data to the STM32 in an `+IPD` notification. The STM32 detects the request, extracts the connection ID, constructs a static HTML response, and sends it back through the ESP8266.

**Pseudocode:**

1. Initialize the request buffer and set the buffer index to zero.
2. Continuously receive data from the ESP8266 through UART1, one byte at a time.
3. Append received bytes to the request buffer.
4. Search for the `+IPD` notification and the HTTP header terminator (`\r\n\r\n`).
5. Extract the TCP connection ID and received data length.
6. Construct an HTTP response containing:
   - HTTP status: `200 OK`
   - Content type: `text/html`
   - Content length
   - HTML page content
7. Send the `AT+CIPSEND` command with the connection ID and response length.
8. Wait for the ESP8266 prompt (`>`).
9. Transmit the HTTP response through UART1.
10. Close the TCP connection using `AT+CIPCLOSE`.
11. Clear the request buffer and continue listening for new requests.

**HTML Response:**

```html
<html>
<body>
    <h1>STM32 IoT Node</h1>
    <p>Hello from STM32</p>
</body>
</html>
```

**Code Base:**
- `HAL_UART_Receive()` – Receives incoming data from the ESP8266.
- `strstr()` – Detects the `+IPD` notification and HTTP header terminator.
- `sscanf()` – Extracts the TCP connection ID and data length.
- `snprintf()` – Constructs the HTTP response and AT command.
- `HAL_UART_Transmit()` – Sends commands and the HTTP response.
- `HAL_GetTick()` – Provides timeout control while waiting for the `>` prompt.
- `AT+CIPSEND` – Initiates transmission of the HTTP response.
- `AT+CIPCLOSE` – Closes the client connection.

### 3. Inference

The STM32 successfully implements the basic HTTP request-handling logic by receiving browser requests through the ESP8266, generating a static HTML response, and transmitting it to the client. This demonstrates how an STM32 microcontroller can serve a simple web page over Wi-Fi using an ESP8266 module as the network interface.