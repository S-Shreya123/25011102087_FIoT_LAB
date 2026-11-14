
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "SNUC";
const char* password = "snu12345";

// MQTT broker
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

// MQTT topic
const char* sensor_topic = "sensor/bme280";

WiFiClient espClient;
PubSubClient client(espClient);

// UART receive buffer
char uart_buffer[160];
int buffer_index = 0;

void setup_wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void reconnect()
{
    while (!client.connected())
    {
        String clientId = "BME280_Wemos_";
        clientId += String(ESP.getChipId(), HEX);

        if (!client.connect(clientId.c_str()))
        {
            delay(3000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.swap();

    setup_wifi();

    client.setServer(mqtt_server, mqtt_port);
    client.setBufferSize(256);

    reconnect();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        setup_wifi();
    }

    if (!client.connected())
    {
        reconnect();
    }

    client.loop();

    while (Serial.available())
    {
        char received = Serial.read();

        if (received == '\n')
        {
            uart_buffer[buffer_index] = '\0';

            if (buffer_index > 0)
            {
                client.publish(sensor_topic, uart_buffer);
            }

            buffer_index = 0;
        }
        else if (received != '\r')
        {
            if (buffer_index < sizeof(uart_buffer) - 1)
            {
                uart_buffer[buffer_index++] = received;
            }
            else
            {
                // Discard an incomplete oversized message
                buffer_index = 0;
            }
        }
    }
}
