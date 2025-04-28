
/**
 * @file main.cpp
 * @author Narges Kurkani
 * @brief This code is sending user data from ESP32 (Master) to FRDM-K64F (Slave) that includes
 *        red,green,blue, and off using I2C protocol and receives confirmation message that is sent by Freedom board.
 * @version 0.1
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Wire.h>
#include <Arduino.h>

#define SLAVE_ADDR 0x50 // Slave address
char buffer[32];        // Buffer for received data (adjust size as needed)

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // Start I2C as master
}

void loop()
{
    if (Serial.available() > 0)
    {

        // Read user input from serial monitor
        String message = Serial.readStringUntil('\n'); // Read the message until newline character

        // Remove any unwanted characters (like '\r' at the end of the string)
        message.trim();

        Serial.print("Sent: ");
        Serial.println(message);

        // Send the message over I2C
        Wire.beginTransmission(SLAVE_ADDR);
        Wire.write(message.length()); // Send length of the message
        Wire.endTransmission();

        delay(10); // Wait for slave to be ready

        // Start I2C transmission to the slave
        Wire.beginTransmission(SLAVE_ADDR);

        // Send the string byte by byte
        for (int i = 0; i < message.length(); i++)
        {
            Wire.write(message[i]); // Send each byte of the string
        }

        Wire.endTransmission(); // End transmission

        delay(10);

        // Now receive the same message back from the slave

        Wire.requestFrom(SLAVE_ADDR, 4); // Request same number of bytes as the message length
        int i = 0;
        while (Wire.available())
        {
            buffer[i++] = Wire.read(); // Read each byte into buffer
        }

        // Print the received message
        Serial.print("Received: ");
        for (int j = 0; j < i; j++) // <-- use 'i' instead of fixed 4
        {
            Serial.print(buffer[j]);
        }
        Serial.println();
        delay(1000); // Wait b
    }
}
