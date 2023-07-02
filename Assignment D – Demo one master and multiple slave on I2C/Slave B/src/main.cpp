#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x42

byte receivedByte = 0;

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void receiveData(int byteCount) {
  while (Wire.available()) {
    receivedByte = Wire.read();  // Read the received data from master
    Serial.print("Received data from master: ");
    Serial.println(receivedByte);
  }
}

void sendData() {
  byte responseByte;
  
  if (receivedByte > 100) {
    responseByte = 2;  // Send back 2 if receivedByte is larger than 100
  } else {
    responseByte = 4;  // Send back 4 if receivedByte is less than or equal to 100
  }

  Wire.write(responseByte);  // Send the response back to master
}


void setup() {
  Wire.begin(SLAVE_ADDRESS);  // Initialize I2C communication as slave
  Wire.onRequest(sendData);  // Register callback function for master's request
  Wire.onReceive(receiveData);  // Register callback function for master's data
  Serial.begin(9600);  // Initialize serial communication
}