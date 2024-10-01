#include "i2c.h"

void I2C__Init(void)
{

    /* GPIO Configuration */
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_I2C_SDA;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
    LL_GPIO_Init(PIN_I2C_SDA_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_I2C_SCL;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
    LL_GPIO_Init(PIN_I2C_SCL_PORT, &GPIO_InitStruct);

    /* I2C Initialization */

    LL_I2C_Disable(I2C);   // Disable I2C1 before configuration

    LL_I2C_InitTypeDef I2C_InitStruct = {0};
    I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
    I2C_InitStruct.Timing = 0x00310C38;     // Fast Mode + 800kHz 
    I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_DISABLE;
    I2C_InitStruct.DigitalFilter = 0;
    I2C_InitStruct.OwnAddress1 = 0;
    I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
    I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
    LL_I2C_Init(I2C, &I2C_InitStruct);

    LL_I2C_EnableAutoEndMode(I2C);
    LL_I2C_SetOwnAddress2(I2C, 0, LL_I2C_OWNADDRESS2_NOMASK);
    LL_I2C_DisableOwnAddress2(I2C);
    LL_I2C_DisableGeneralCall(I2C);
    LL_I2C_DisableClockStretching(I2C);

    LL_I2C_Enable(I2C);

}
