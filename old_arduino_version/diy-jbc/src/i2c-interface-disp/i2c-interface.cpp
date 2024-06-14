#include <Arduino.h>
#include "i2c-interface.h"

I2CInterface::I2CInterface(byte address) {
    this->device_address = address;
}

I2CInterface::~I2CInterface() {
}

void I2CInterface::init() {
    Wire.begin(this->device_address);
    Wire.onReceive(onReceive);
    Wire.onRequest(onRequest);
    this_instance = this;
}

void I2CInterface::onReceive(int numBytes) {
    this_instance->handleReceive(numBytes);
}

void I2CInterface::onRequest() {
    this_instance->handleRequest();
}

void I2CInterface::handleRequest() {

}

void I2CInterface::handleReceive(int numBytes) {
    // check if there are at least 2 bytes to read
    if (numBytes < 2) {
        return;
    }

    // first byte is the address of the register to write/read
    request_addr_buffer = Wire.read();

    // check if a write or read request (check the MSB)
    if (request_addr_buffer & _READ) {
        // read request
        return; // nothing to do -> wait for request
    }
    else {
        // write request
        // check if the number of bytes received is correct
        int datalen = Wire.read();
        if(numBytes - 2 != datalen) {
            return;
        }
        // call the correct read function
}

