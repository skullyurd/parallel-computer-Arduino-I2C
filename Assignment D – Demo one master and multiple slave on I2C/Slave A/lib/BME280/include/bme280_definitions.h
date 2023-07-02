#ifndef BME280_DEFENITION_H
#define BME280_DEFENITION_H

class Bme280
{
public:
    Bme280();
    void Reset();
    void GetID();
    void ReadCalibrationData();
    void ControlTemperatureAndPressure();
    void ControlMeasurement();
    void ControlHumidity();
    uint32_t ReadPressure();
    int32_t ReadTemperature();
    int32_t ReadRawHumidity();
    double ReadHumidity();

private:
    // calibration data
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6;
    uint16_t ID;
    uint32_t t_fine;

    // commands and registers
    const uint8_t ADDRESS = 0x76;
    const uint8_t READ_AFTER_ADDRESS = 1;
    const uint8_t RESET = 0xE0;
    const uint8_t RESET_COMPLETE = 0xB6;
    const uint8_t ID_ASK = 0xD0;
    const uint8_t CONTROL_MEASUREMENTS = 244;
    const uint8_t CONTROL_MEASUREMENTS_ADDRESS = 242;
    
    uint16_t GetTwoBytes(uint8_t firstBit);
    uint8_t GetSingleByte(uint8_t Bit);
};

#endif
