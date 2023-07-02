#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x50
#define inA 0x21
#define inB 0x22
#define MIN 0x23
#define MAX 0x24

byte inputA = 4;
byte inputB = 12;

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

void sendData() {
  Wire.write(min(inputA, inputB));  // Sending minimum value
  Wire.write(max(inputA, inputB));  // Sending maximum value
}

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {

}
