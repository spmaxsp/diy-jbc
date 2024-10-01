/**
  ******************************************************************************
  * @file    usart_ser_ui.h
  * @brief   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_SER_UI_H__
#define __USART_SER_UI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

#include "hw_define.h"

/* Exported types ------------------------------------------------------------*/

void UART_Ser_Ui__IRQHandler(void);

void USART_Ser_Ui__Init(void);
void USART_Ser_Ui__Tx_Blocking(uint8_t *data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* __USART_SER_UI_H__ */