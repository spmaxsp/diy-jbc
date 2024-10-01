/**
  ******************************************************************************
  * @file    temperature.h
  * @brief   This file contains the function prototypes for the temperature.c and temperature_spi.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "spi.h"

/* Exported types ------------------------------------------------------------*/

void Temperature_StartConversion(void);
uint16_t Temperature_Read(void);
uint16_t Temperature_Convert_Celsius(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif /* __TEMPERATURE_H__ */