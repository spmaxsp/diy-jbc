/**
  ******************************************************************************
  * @file    u8g2_stm32g0xx_helper.h
  * @brief   This file contains the function prototypes for the u8g2_stm32g0xx_helper.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __U8G2_STM32G0XX_HELPER_H__
#define __U8G2_STM32G0XX_HELPER_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "i2c.h"

// Display Library
#include "u8g2.h"

/* Exported functions prototypes ---------------------------------------------*/
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#ifdef __cplusplus
}
#endif

#endif /* __U8G2_STM32G0XX_HELPER_H__ */
