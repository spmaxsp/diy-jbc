
#include "temperature.h"

void Temperature_StartConversion(void){

    // Start the conversion by pulling the CS pin low
    LL_GPIO_ResetOutputPin(PIN_SPI_TEMP_CS_PORT, PIN_SPI_TEMP_CS);
    LL_mDelay(1);
    LL_GPIO_SetOutputPin(PIN_SPI_TEMP_CS_PORT, PIN_SPI_TEMP_CS);
}

uint16_t Temperature_Read(void){

    // Slave select
    LL_GPIO_ResetOutputPin(PIN_SPI_TEMP_CS_PORT, PIN_SPI_TEMP_CS);
    
    // read 16 bits from the SPI
    LL_SPI_TransmitData16(SPI, 0x0000); // dummy data to read 16 bits
    while (!LL_SPI_IsActiveFlag_TXE(SPI));
    while (!LL_SPI_IsActiveFlag_RXNE(SPI));
    uint16_t data = LL_SPI_ReceiveData16(SPI);

    // Slave deselect
    LL_GPIO_SetOutputPin(PIN_SPI_TEMP_CS_PORT, PIN_SPI_TEMP_CS);
    

    // data from 14th to 3rd bit
    data = (data >> 3) & 0x0FFF;

    return data;
}

uint16_t Temperature_Convert_Celsius(uint16_t data){

    // 0x000 -> 0°C
    // 0xFFF -> +1023.75°C

    uint16_t temperature = (data * 1024) / 4096;

    return temperature;
}


