#include <Arduino.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x50
#define inA 0x21
#define inB 0x22
#define MIN 0x23
#define MAX 0x24

byte inputA = 4;
byte inputB = 12;

// Function to find minimum of x and y
// x and y are parameters of the function
void receiveData(int byteCount) {
  while (Wire.available()) {
    byte registerAddress = Wire.read();

    switch (registerAddress) {
      case inA:
        inputA = Wire.read();
        break;

      case inB:
        inputB = Wire.read();
        break;

      case MIN:
        Wire.write(min(inputA, inputB));
        break;

      case MAX:
        Wire.write(max(inputA, inputB));
        break;

      default:
        break;
    }
  }
}

// Function to find maximum of x and y
void sendData() {
  Wire.write(min(inputA, inputB));  // Sending minimum value
  Wire.write(max(inputA, inputB));  // Sending maximum value
}

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Initialize as a slave with address 0x50
  Wire.onReceive(receiveData);// Function to run when data received from master
  Wire.onRequest(sendData);// Function to run when data requested from master
}

void loop() {

}
