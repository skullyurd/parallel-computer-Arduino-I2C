#include <Arduino.h>
#include <Wire.h>
#include "bme280_definitions.h"

#define SLAVE_ADDRESS 0x76
#define HUMIDITY_ADDRESS 0xFD
#define TEMPERATURE_ADDRESS 0xFA
#define PRESSURE_ADDRESS 0xF7

byte temperature, humidity, pressure;

Bme280 sensor;

void setup()
{
  Serial.begin(9600); // start serial for output
  Wire.begin(SLAVE_ADDRESS); // join i2c bus 
  sensor.Reset();//reset sensor
  sensor.GetID(); //get sensor ID
  sensor.ReadCalibrationData(); //read calibration data
  sensor.ControlTemperatureAndPressure();// control temperature and pressure
  sensor.ControlMeasurement(); //control measurement
  sensor.ControlHumidity(); //control humidity
}

void loop()
{
  //read temperature data, humidity data and pressure data
  temperature = sensor.ReadTemperature();
  delay(10);
  humidity = sensor.ReadHumidity();
  delay(10);
  pressure = sensor.ReadPressure();
  delay(10);

  //print temperature data, humidity data and pressure data to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print("\n");
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.print("%\n");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.print("\n");

  Wire.write(temperature);   // Send the first float
  Wire.write(humidity);   // Send the second float
  Wire.write(humidity);   // Send the third float

  delay(1000);
}
