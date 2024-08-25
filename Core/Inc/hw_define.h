/**
  ******************************************************************************
  * @file    hw_define.h
  * @brief   This file contains the definitions of the hardware resources used in the project.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Definitions ---------------------------------------------------------------*/

// ---  MAIN LOOP TIMER  ---
// TIMER
#define MAIN_LOOP_TIMER   TIM14
#define MAIN_LOOP_TIMER_IRQn TIM14_IRQn
// TIMER IRQ Handler Remap
#define MainLoopTimer_IRQHandler TIM14_IRQHandler


// ---   ENCODER   ---
// GPIO
#define ENCODER_A_PORT  GPIOA
#define ENCODER_A_PIN   LL_GPIO_PIN_5
#define ENCODER_B_PORT  GPIOA
#define ENCODER_B_PIN   LL_GPIO_PIN_1
// TIMER
#define ENCODER_TIMER   TIM2

// ---   WS2812B   ---
#define WS2812B_LED_COUNT   3
// GPIO
#define WS2812B_PORT        GPIOA
#define WS2812B_PIN         LL_GPIO_PIN_6
// TIMER
#define WS2812B_TIMER       TIM3
#define WS2812B_TIMER_CHANNEL     LL_TIM_CHANNEL_CH1
#define WS2812B_CCR_DMA_ADR (uint32_t)&(WS2812B_TIMER->CCR1)
// DMA
#define WS2812B_DMA         DMA1
#define WS2812B_DMA_CHANNEL LL_DMA_CHANNEL_2
#define WS2812B_DMA_REQUEST LL_DMAMUX_REQ_TIM3_CH1
#define WS2812B_DMA_IRQn    DMA1_Channel2_3_IRQn
// DMA IRQ Handler Remap
#define WS2812B_DMA_IRQHandler DMA1_Channel2_3_IRQHandler

// ---   BUTTON   ---
// GPIO
#define BUTTON_ENCODER_PORT GPIOA
#define BUTTON_ENCODER_PIN  LL_GPIO_PIN_0
#define BUTTON_BLUE_PORT    GPIOA
#define BUTTON_BLUE_PIN     LL_GPIO_PIN_1
#define BUTTON_RED_PORT     GPIOA
#define BUTTON_RED_PIN      LL_GPIO_PIN_2

// ---   TEMP SENSOR   ---
// GPIO
#define TEMP_SPI_SCK_PORT   GPIOA
#define TEMP_SPI_SCK_PIN    LL_GPIO_PIN_0
#define TEMP_SPI_MISO_PORT  GPIOD
#define TEMP_SPI_MISO_PIN   LL_GPIO_PIN_3
#define TEMP_SPI_CS_PORT    GPIOB
#define TEMP_SPI_CS_PIN     LL_GPIO_PIN_6
// SPI
#define TEMP_SPI            SPI2

// ---   DISPLAY   ---
// GPIO
#define DISP_I2C_SCL_PORT   GPIOB
#define DISP_I2C_SCL_PIN    LL_GPIO_PIN_8
#define DISP_I2C_SDA_PORT   GPIOB
#define DISP_I2C_SDA_PIN    LL_GPIO_PIN_7
// I2C
#define DISP_I2C            I2C1
#define DISP_I2C_ADDR       0x3C

// ---   POWER   ---
// GPIO
#define PWR_TRIAC_EN_PORT   GPIOA
#define PWR_TRIAC_EN_PIN    LL_GPIO_PIN_8
#define PWR_ZERO_IN_PORT    GPIOA
#define PWR_ZERO_IN_PIN     LL_GPIO_PIN_12
#define STATION_SENS_PORT   GPIOB
#define STATION_SENS_PIN    LL_GPIO_PIN_15
// TIMER
#define PWR_TIMER           TIM1
#define PWR_TIMER_CHANNEL   LL_TIM_CHANNEL_CH1

// ---   SERIAL UI   ---
// GPIO
#define SER_UI_RX_TX_PORT   GPIOA
#define SER_UI_TX_PIN       LL_GPIO_PIN_2
#define SER_UI_RX_PIN       LL_GPIO_PIN_3

// UART
#define SER_UI_UART            USART2
#define SER_UI_UART_BAUDRATE   115200
#define SER_UI_UART_IRQn       USART2_IRQn
// UART IRQ Handler Remap
#define Ser_Ui_USART_IRQHandler USART2_IRQHandler

// DMA
#define SER_UI_DMA                DMA1
#define SER_UI_DMA_RX_CHANNEL     LL_DMA_CHANNEL_1
#define SER_UI_DMA_RX_BUFFER_SIZE 64
#define SER_UI_DMA_RX_REQUEST     LL_DMAMUX_REQ_USART2_RX
#define SER_UI_DMA_IRQn           DMA1_Channel1_IRQn
// DMA IRQ Handler Remap
#define Ser_Ui_DMA_IRQHandler     DMA1_Channel1_IRQHandler


#ifdef __cplusplus
}
#endif

#endif /*__ GPIO_H__ */
