/**
  ******************************************************************************
  * @file    gpio_button.h
  * @brief   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_BUTTON_H__
#define __GPIO_BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g0xx_ll_gpio.h"

#include "hw_define.h"

/* Exported types ------------------------------------------------------------*/

void GPIO_Button__Init(void);

uint8_t GPIO_Button_Encoder__GetState(void);
uint8_t GPIO_Button_Blue__GetState(void);
uint8_t GPIO_Button_Red__GetState(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_BUTTON_H__ */