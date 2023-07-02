#include <Arduino.h>
#include <Wire.h>
#include "bme280_definitions.h"

Bme280 sensor;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sensor.Reset();
  sensor.GetID();
  sensor.ReadCalibrationData();
  sensor.ControlTemperatureAndPressure();
  sensor.ControlMeasurement();
  sensor.ControlHumidity();

  Serial.print("ID: ");
}

void loop()
{
  Serial.print("Temperature: ");
  Serial.print(sensor.ReadTemperature());
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(sensor.ReadPressure());
  Serial.println(" Pa");

  Serial.print("Humidity: ");
  Serial.print(sensor.ReadHumidity());
  Serial.println(" %");

  Serial.println();
  delay(3000);
}
