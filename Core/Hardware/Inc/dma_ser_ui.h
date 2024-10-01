/**
  ******************************************************************************
  * @file    dma_ser_ui.h
  * @brief   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA_SER_UI_H__
#define __DMA_SER_UI_H__

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

void DMA_Ser_Ui__IRQHandler(void);

void DMA_Ser_Ui__Init(void);
void DMA_Ser_Ui__Enable(void);
void DMA_Ser_Ui__Reset(void);
uint32_t DMA_Ser_Ui__GetDataLength(void);


#ifdef __cplusplus
}
#endif

#endif /* __DMA_SER_UI_H__ */