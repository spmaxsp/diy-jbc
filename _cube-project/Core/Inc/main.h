/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TEMP_SPI_SCK_Pin LL_GPIO_PIN_0
#define TEMP_SPI_SCK_GPIO_Port GPIOA
#define ENCODER_B_Pin LL_GPIO_PIN_1
#define ENCODER_B_GPIO_Port GPIOA
#define SER_UI_TX_Pin LL_GPIO_PIN_2
#define SER_UI_TX_GPIO_Port GPIOA
#define SER_UI_RX_Pin LL_GPIO_PIN_3
#define SER_UI_RX_GPIO_Port GPIOA
#define ENCODER_A_Pin LL_GPIO_PIN_5
#define ENCODER_A_GPIO_Port GPIOA
#define WS2812B_Pin LL_GPIO_PIN_6
#define WS2812B_GPIO_Port GPIOA
#define STATION_SENS_Pin LL_GPIO_PIN_15
#define STATION_SENS_GPIO_Port GPIOB
#define PWR_TRIAC_EN_Pin LL_GPIO_PIN_8
#define PWR_TRIAC_EN_GPIO_Port GPIOA
#define PWR_ZERO_IN_Pin LL_GPIO_PIN_12
#define PWR_ZERO_IN_GPIO_Port GPIOA
#define BUTTON_ENCODER_Pin LL_GPIO_PIN_0
#define BUTTON_ENCODER_GPIO_Port GPIOD
#define BUTTON_BLUE_Pin LL_GPIO_PIN_1
#define BUTTON_BLUE_GPIO_Port GPIOD
#define BUTTON_RED_Pin LL_GPIO_PIN_2
#define BUTTON_RED_GPIO_Port GPIOD
#define TEMP_SPI_MISO_Pin LL_GPIO_PIN_3
#define TEMP_SPI_MISO_GPIO_Port GPIOD
#define TEMP_SPI_CS_Pin LL_GPIO_PIN_6
#define TEMP_SPI_CS_GPIO_Port GPIOB
#define DISP_I2C_SDA_Pin LL_GPIO_PIN_7
#define DISP_I2C_SDA_GPIO_Port GPIOB
#define DISP_I2C_SCL_Pin LL_GPIO_PIN_8
#define DISP_I2C_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
