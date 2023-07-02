#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS_B 0x42

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS_B, 1);  // Request data from slave

  if (Wire.available()) {
    byte receivedData = Wire.read();  // Read the data received from slave
    Serial.print("Received data from slave: ");
    Serial.println(receivedData);
  }

  Wire.beginTransmission(SLAVE_ADDRESS_B);  // Begin transmission to slave
  Wire.write(random(256));  // Send a random byte to slave
  Wire.endTransmission();  // End transmission

  delay(1000);  // Wait for 1 second before sending the next byte
}
