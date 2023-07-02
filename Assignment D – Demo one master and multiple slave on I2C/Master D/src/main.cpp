#include <Arduino.h>
#include <Wire.h>

// I2C slave address
#define SLAVE_ADDRESS_A 0x76
#define SLAVE_ADDRESS_B 0x42
#define SLAVE_ADDRESS_C 0x50

#define DATA_SIZE sizeof(float)

void setup()
{
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  Serial.println("coming from A");
  byte temperature, humidity, pressure;

  //3 bytes incomning from slave address A
  Wire.requestFrom(SLAVE_ADDRESS_A, 3);

  // Wait until slave sends all data
  while (Wire.available() < 3);

  // Read the data
  temperature = Wire.read();
  humidity = Wire.read();
  pressure = Wire.read();

  // Print the received values
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C");

  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.print(" %");

  Serial.print(" Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.println("-----");

  Serial.println("coming from B");
  Wire.requestFrom(SLAVE_ADDRESS_B, 1);  // Request data from slave

  if (Wire.available()) {
    byte receivedData = Wire.read();  // Read the data received from slave
    Serial.print("Received data from slave: ");
    Serial.println(receivedData);
    Serial.println("-----");
  }

  Wire.beginTransmission(SLAVE_ADDRESS_B);  // Begin transmission to slave
  Wire.write(random(256));  // Send a random byte to slave
  Wire.endTransmission();  // End transmission

  delay(1000);  // Wait for 1 second before sending the next byte

    //get both values, print the lowest and highest number
    Serial.println("coming from C");
  Wire.requestFrom(SLAVE_ADDRESS_C, 2);
  int first = Wire.read();
  int second = Wire.read();
  Serial.print("First: ");
  Serial.println(first);
  Serial.print("Second: ");
  Serial.println(second);
  Serial.println("-----");

  delay(1000);

}

