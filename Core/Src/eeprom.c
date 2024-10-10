#include "eeprom.h"

                        // 0b 1 0 1 0 A2 A1 A0 R/W
const uint8_t eeprom_adr = 0x50; // 0b10100000

void EEPROM_Write(uint16_t address, uint8_t length, uint8_t *data){
    
    // Check if the bus is busy
    while(LL_I2C_IsActiveFlag_BUSY(I2C));

    // Start condition
    LL_I2C_HandleTransfer(I2C, (eeprom_adr << 1), LL_I2C_ADDRSLAVE_7BIT, length+2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

    while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
    LL_I2C_TransmitData8(I2C, address >> 8);
    while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
    LL_I2C_TransmitData8(I2C, address & 0xFF);
    
    for(uint8_t i = 0; i < length; i++)
    {
        // check if the TXIS flag is set
        while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
        
        // Write in the DR register the data to be sent
        LL_I2C_TransmitData8(I2C, data[i]);
    }

    // Check end of transfer
    while(!(LL_I2C_IsActiveFlag_STOP(I2C)));
}


void EEPROM_Read(uint16_t address, uint8_t length, uint8_t *data){
    
    // Check if the bus is busy
    while(LL_I2C_IsActiveFlag_BUSY(I2C));

    // Start condition for dummy write
    LL_I2C_HandleTransfer(I2C, (eeprom_adr << 1), LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

    while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
    LL_I2C_TransmitData8(I2C, address >> 8);
    while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
    LL_I2C_TransmitData8(I2C, address & 0xFF);

    // Check end of transfer
    while(!(LL_I2C_IsActiveFlag_STOP(I2C)));

    // Start condition for read
    LL_I2C_HandleTransfer(I2C, (eeprom_adr << 1), LL_I2C_ADDRSLAVE_7BIT, length, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

    for(uint8_t i = 0; i < length; i++)
    {
        // check if the RXNE flag is set
        while(!(LL_I2C_IsActiveFlag_RXNE(I2C)));
        
        // Read the data received in the DR register
        data[i] = LL_I2C_ReceiveData8(I2C);
    }

    // Check end of transfer
    while(!(LL_I2C_IsActiveFlag_STOP(I2C)));
}