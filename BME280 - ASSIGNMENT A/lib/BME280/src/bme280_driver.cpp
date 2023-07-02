#include <Wire.h>
#include <Arduino.h>
#include "bme280_definitions.h"

Bme280::Bme280() {
  // Initialize the BME280 sensor
  Wire.begin();
}

void Bme280::Reset() {
  // Reset the BME280 sensor
  Wire.beginTransmission(ADDRESS);
  Wire.write(RESET);
  Wire.write(RESET_COMPLETE);
  Wire.endTransmission();
  delay(100);
}

void Bme280::GetID() {
  // Read the sensor ID
  Wire.beginTransmission(ADDRESS);
  Wire.write(ID_ASK);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);
  if (Wire.available()) {
    ID = Wire.read();
  }
}

void Bme280::ReadCalibrationData() {
  // Read calibration data from the sensor
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x88);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 24);
  if (Wire.available() >= 24) {
    dig_T1 = GetTwoBytes(Wire.read());
    dig_T2 = GetTwoBytes(Wire.read());
    dig_T3 = GetTwoBytes(Wire.read());
    dig_P1 = GetTwoBytes(Wire.read());
    dig_P2 = GetTwoBytes(Wire.read());
    dig_P3 = GetTwoBytes(Wire.read());
    dig_P4 = GetTwoBytes(Wire.read());
    dig_P5 = GetTwoBytes(Wire.read());
    dig_P6 = GetTwoBytes(Wire.read());
    dig_P7 = GetTwoBytes(Wire.read());
    dig_P8 = GetTwoBytes(Wire.read());
    dig_P9 = GetTwoBytes(Wire.read());
    dig_H1 = GetSingleByte(Wire.read());

    Wire.beginTransmission(ADDRESS);
    Wire.write(0xE1);
    Wire.endTransmission();

    Wire.requestFrom(ADDRESS, 7);
    if (Wire.available() >= 7) {
      dig_H2 = GetTwoBytes(Wire.read());
      dig_H3 = Wire.read();
      dig_H4 = (Wire.read() << 4) | (Wire.read() & 0x0F);
      dig_H5 = (Wire.read() << 4) | ((Wire.read() >> 4) & 0x0F);
      dig_H6 = static_cast<int8_t>(Wire.read());
    }
  }
}

void Bme280::ControlTemperatureAndPressure() {
  // Configure temperature and pressure control settings
  Wire.beginTransmission(ADDRESS);
  Wire.write(CONTROL_MEASUREMENTS_ADDRESS);
  Wire.write(CONTROL_MEASUREMENTS);
  Wire.endTransmission();
}

void Bme280::ControlMeasurement() {
  // Start measurement
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x27);
  Wire.endTransmission();
}

void Bme280::ControlHumidity() {
  // Configure humidity control settings
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xF2);
  Wire.write(0x01);
  Wire.endTransmission();
}

uint32_t Bme280::ReadPressure() {
  // Read pressure data
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xF7);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 3);
  if (Wire.available() >= 3) {
    uint32_t msb = Wire.read();
    uint32_t lsb = Wire.read();
    uint32_t xlsb = Wire.read();

    return ((msb << 12) | (lsb << 4) | (xlsb >> 4));
  }

  return 0;
}

int32_t Bme280::ReadTemperature() {
  // Read temperature data
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xFA);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 3);
  if (Wire.available() >= 3) {
    uint32_t msb = Wire.read();
    uint32_t lsb = Wire.read();
    uint32_t xlsb = Wire.read();

    int32_t rawTemperature = (msb << 12) | (lsb << 4) | (xlsb >> 4);
    return rawTemperature / 22061;
  }

  return 0;
}

int32_t Bme280::ReadRawHumidity() {
  // Read raw humidity data
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xFD);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 2);
  if (Wire.available() >= 2) {
    uint32_t msb = Wire.read();
    uint32_t lsb = Wire.read();

    return (msb << 8) | lsb;
  }

  return 0;
}

double Bme280::ReadHumidity() {
  // Read humidity data
  int32_t rawHumidity = ReadRawHumidity();
  return rawHumidity / 1024.0;
}

uint16_t Bme280::GetTwoBytes(uint8_t firstByte) {
  uint16_t value = firstByte;
  value <<= 8;

  Wire.beginTransmission(ADDRESS);
  Wire.write(0x89);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);
  if (Wire.available()) {
    value |= Wire.read();
  }

  return value;
}

uint8_t Bme280::GetSingleByte(uint8_t byte) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xA1);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);
  if (Wire.available()) {
    return Wire.read();
  }

  return byte;
}