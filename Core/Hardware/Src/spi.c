
#include "spi.h"

void SPI__Init(void) {

    /* GPIO Configuration */

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_SPI_SCK;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(PIN_SPI_SCK_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_SPI_MISO;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(PIN_SPI_MISO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_SPI_TEMP_CS;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_SPI_TEMP_CS_PORT, &GPIO_InitStruct);

    /* SPI Initialization */

    LL_SPI_InitTypeDef SPI_InitStruct = {0};
    SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX; // only RX is needed but full duplex allows better control over the clock
    SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
    SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_16BIT;
    SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
    SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;
    SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
    SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly = 7;
    LL_SPI_Init(SPI, &SPI_InitStruct);
    LL_SPI_SetStandard(SPI, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_DisableNSSPulseMgt(SPI);

    // Enable SPI
    LL_SPI_Enable(SPI);

    // Set CS high
    LL_GPIO_SetOutputPin(PIN_SPI_TEMP_CS_PORT, PIN_SPI_TEMP_CS);
}

