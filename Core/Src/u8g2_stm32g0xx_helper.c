
#include "u8g2_stm32g0xx_helper.h"

uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
	case U8X8_MSG_GPIO_AND_DELAY_INIT:
		/* Insert codes for initialization */
		break;
	case U8X8_MSG_DELAY_MILLI:
		/* ms Delay */
		LL_mDelay(arg_int*10);
		break;
	case U8X8_MSG_GPIO_CS:
		/* Insert codes for SS pin control */
		break;
	case U8X8_MSG_GPIO_DC:
		/* Insert codes for DC pin control */
		break;
	case U8X8_MSG_GPIO_RESET:
		/* Insert codes for RST pin control */
		break;
	}
	return 1;
}

uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
	static uint8_t buffer[32];
	static uint8_t buf_idx;
	uint8_t *data;

	switch(msg)
	{
	case U8X8_MSG_BYTE_SEND:
		__NOP();
		data = (uint8_t *)arg_ptr;
		while( arg_int > 0 )
		{
	        buffer[buf_idx++] = *data;
            data++;
            arg_int--;
		}
		break;
	case U8X8_MSG_BYTE_INIT:
		
		break;
	case U8X8_MSG_BYTE_SET_DC:
		break;
	case U8X8_MSG_BYTE_START_TRANSFER:
		__NOP();
		buf_idx = 0;
		break;
	case U8X8_MSG_BYTE_END_TRANSFER:
		//if(HAL_I2C_Master_Transmit(&hi2c1, (DEVICE_ADDRESS << 1), buffer, buf_idx, TX_TIMEOUT) != HAL_OK) return 0;

		// Check if the bus is busy
		while(LL_I2C_IsActiveFlag_BUSY(I2C));

		// Generate Start condition
        LL_I2C_HandleTransfer(I2C, (I2C_DISP_ADDR << 1), LL_I2C_ADDRSLAVE_7BIT, buf_idx, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE); 


        for(uint8_t i = 0; i < buf_idx; i++)
        {
			// check if the TXIS flag is set
			while(!(LL_I2C_IsActiveFlag_TXIS(I2C)));
			
			// Write in the DR register the data to be sent
			LL_I2C_TransmitData8(I2C, buffer[i]);
        }

		// Check end of transfer
		while(!(LL_I2C_IsActiveFlag_STOP(I2C)));

		break;
	default:
		return 0;
	}
	return 1;
}