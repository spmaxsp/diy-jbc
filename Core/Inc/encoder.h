/**
  ******************************************************************************
  * @file    encoder_tim.h
  * @brief   This file contains the function prototypes for the encoder.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_TIM_H__
#define __ENCODER_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "tim_encoder.h"

/* Exported types ------------------------------------------------------------*/

void Encoder_SetMinMax(int16_t min, int16_t max);
void Encoder_SetCounter(int16_t value);
int16_t Encoder_GetCounter(void);
int16_t Encoder_ResetAndGetDelta(void);
int16_t Encoder_ResetAndGetDelta_Acel(void);

#ifdef __cplusplus
}
#endif

#endif /* __ENCODER_TIM_H__ */