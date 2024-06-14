#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include <Arduino.h>
#include <Wire.h>

#define SET_TEMP 0x01   // READ/WRITE
#define IS_TEMP 0x02    // READ
#define PID 0x03        // READ

#define SET_KP 0x04     // READ/WRITE
#define SET_KI 0x05     // READ/WRITE
#define SET_KD 0x06     // READ/WRITE

#define SET_TC_A 0x07   // READ/WRITE
#define SET_TC_B 0x08   // READ/WRITE
#define SET_TC_C 0x09   // READ/WRITE

#define SET_SLEEP_DELAY 0x0A // READ/WRITE
#define SET_SLEEP_TEMP 0x0B  // READ/WRITE

#define SET_HIBERNATE_DELAY 0x0C // READ/WRITE
#define SET_HIBERNATE_TEMP 0x0D  // READ/WRITE

#define WRITE_EEPROM 0x0E   // WRITE(no value)

#define ENABLE 0x0F         // READ/WRITE

#define ERROR 0x10          // READ

#define _READ b10000000
#define _WRITE b00000000

class I2CInterface {
    private:
        byte device_address;
    public:
        I2CInterface(byte address);
        ~I2CInterface();

        void init();

        void write_int(byte address, int value);
        void write_double(byte address, double value);
        void write_bool(byte address, bool value);

        int read_int(byte address);
        double read_double(byte address);
        bool read_bool(byte address);
};

#endif /* I2C_INTERFACE_H_ */