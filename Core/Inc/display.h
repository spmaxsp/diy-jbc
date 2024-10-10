/**
  ******************************************************************************
  * @file    display.h
  * @brief   This file contains the function prototypes for the display_i2c.c and display.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "i2c.h"
#include "gpio_button.h"
#include "encoder.h"

// Display Library
#include "u8g2.h"
#include "u8g2_stm32g0xx_helper.h"

/* Exported types ------------------------------------------------------------*/

void Display_Init(void);
void Display_Render_Main(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H__ */