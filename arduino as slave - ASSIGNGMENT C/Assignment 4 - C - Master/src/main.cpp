#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS_C 0x50

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  //get both values, print the lowest and highest number
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
