/**
  ******************************************************************************
  * @file    ws2812b.h
  * @brief   This file contains the function prototypes for the ws2812b.c and ws2812b_tim.c and ws2812b_dma.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WS2812B_H__
#define __WS2812B_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "dma_ws2812b.h"
#include "tim_ws2812b.h"

/* Exported types ------------------------------------------------------------*/

void WS2812B_UpdateLEDs(void);
void WS2812B_SetColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif

#endif /* __WS2812B_H__ */