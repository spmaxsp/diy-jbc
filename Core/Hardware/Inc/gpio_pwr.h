/**
  ******************************************************************************
  * @file    gpio_pwr.h
  * @brief   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_PWR_H__
#define __GPIO_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_exti.h"

#include "hw_define.h"

/* Exported types ------------------------------------------------------------*/

void GPIO_PWR_ZC__IRQHandler(void);

void GPIO_PWR__Init(void);

void GPIO_Station_Sense__GetState(void);
void GPIO_Triac__Enable(void);
void GPIO_Triac__Disable(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_PWR_H__ */