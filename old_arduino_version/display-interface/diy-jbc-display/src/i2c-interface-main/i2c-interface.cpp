#include "i2c-interface.h"

I2CInterface::I2CInterface(byte device_address) {
    this->device_address = device_address;
}

I2CInterface::~I2CInterface() {
}

void I2CInterface::init() {
    Wire.begin(); 
}

void I2CInterface::master_write_int(byte address, int value) {
    uint8_t length = sizeof(value);
    uint8_t* bytes = (uint8_t*) &value;

    Wire.beginTransmission(device_address);
    Wire.write(address);
    Wire.write(length);
    for (int i = 0; i < length; i++) {
        Wire.write(bytes[i]);
    }
    Wire.endTransmission();
}

void I2CInterface::write_double(byte address, double value) {
    uint8_t length = sizeof(value);
    uint8_t* bytes = (uint8_t*) &value;

    Wire.beginTransmission(device_address);
    Wire.write(address);
    Wire.write(length);
    for (int i = 0; i < length; i++) {
        Wire.write(bytes[i]);
    }
    Wire.endTransmission();
}

void I2CInterface::write_bool(byte address, bool value) {
    Wire.beginTransmission(device_address);
    Wire.write(address);
    Wire.write(1);
    int val = (value ? 1 : 0);
    Wire.write(val);
    Wire.endTransmission();
}

int I2CInterface::read_int(byte address) {
    Wire.beginTransmission(device_address);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(device_address, 1);
    uint8_t length = Wire.read();
    uint8_t bytes[length];
    Wire.requestFrom(device_address, length);
    for (int i = 0; i < length; i++) {
        bytes[i] = Wire.read();
    }
    int value = *(int*) bytes;
    return value;
}

double I2CInterface::read_double(byte address) {
    Wire.beginTransmission(device_address);
    Wire.write(address);
    Wire.endTransmission();
    
    Wire.requestFrom(device_address, 1);
    uint8_t length = Wire.read();
    uint8_t bytes[length];
    Wire.requestFrom(device_address, length);
    for (int i = 0; i < length; i++) {
        bytes[i] = Wire.read();
    }
    double value = *(double*) bytes;
    return value;
}

bool I2CInterface::read_bool(byte address) {
    Wire.beginTransmission(device_address); 
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(device_address, 1);
    int value = Wire.read();
    return (value == 1);
}

