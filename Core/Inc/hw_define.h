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
#define TIM_MAIN_LOOP      TIM14
#define TIM_MAIN_LOOP_IRQn TIM14_IRQn
// TIMER IRQ Handler Remap
#define TIM_MainLoop__IRQHandler TIM14_IRQHandler


// ---   ENCODER   ---
// GPIO
#define PIN_ENCODER_A_PORT GPIOA
#define PIN_ENCODER_A      LL_GPIO_PIN_5
#define PIN_ENCODER_B_PORT GPIOA
#define PIN_ENCODER_B      LL_GPIO_PIN_1
// TIMER
#define TIM_ENCODER        TIM2

// ---   WS2812B   ---
#define WS2812B_LED_COUNT   3
// GPIO
#define PIN_WS2812B_PORT        GPIOA
#define PIN_WS2812B             LL_GPIO_PIN_6
// TIMER
#define TIM_WS2812B             TIM3
#define TIM_WS2812B_CHANNEL     LL_TIM_CHANNEL_CH1
#define TIM_WS2812B_CCR_DMA_ADR (uint32_t)&(WS2812B_TIMER->CCR1)
// DMA
#define DMA_WS2812B         DMA1
#define DMA_WS2812B_CHANNEL LL_DMA_CHANNEL_2
#define DMA_WS2812B_REQUEST LL_DMAMUX_REQ_TIM3_CH1
#define DMA_WS2812B_IRQn    DMA1_Channel2_3_IRQn
// DMA IRQ Handler Remap
#define DMA_WS2812B__IRQHandler DMA1_Channel2_3_IRQHandler

// ---   BUTTON   ---
// GPIO
#define PIN_BUTTON_ENCODER_PORT GPIOD
#define PIN_BUTTON_ENCODER      LL_GPIO_PIN_0
#define PIN_BUTTON_BLUE_PORT    GPIOD
#define PIN_BUTTON_BLUE         LL_GPIO_PIN_1
#define PIN_BUTTON_RED_PORT     GPIOD
#define PIN_BUTTON_RED          LL_GPIO_PIN_2


// ---  SPI   ---
// GPIO
#define PIN_SPI_SCK_PORT   GPIOA
#define PIN_SPI_SCK        LL_GPIO_PIN_0
#define PIN_SPI_MISO_PORT  GPIOD
#define PIN_SPI_MISO       LL_GPIO_PIN_3
#define PIN_SPI_MOSI_PORT  GPIOB
#define PIN_SPI_MOSI       LL_GPIO_PIN_15
// SPI
#define SPI                SPI2


// ---   TEMP SENSOR   ---
// GPIO
#define PIN_SPI_TEMP_CS_PORT    GPIOB
#define PIN_SPI_TEMP_CS         LL_GPIO_PIN_6


// ---  I2C   ---
// GPIO
#define PIN_I2C_SCL_PORT   GPIOB
#define PIN_I2C_SCL        LL_GPIO_PIN_8
#define PIN_I2C_SDA_PORT   GPIOB
#define PIN_I2C_SDA        LL_GPIO_PIN_7
// I2C
#define I2C                I2C1

// ---   DISPLAY   ---
// I2C
#define I2C_DISP_ADDR       0x3C

// ---   POWER   ---
// GPIO
#define PIN_PWR_TRIAC_EN_PORT   GPIOA
#define PIN_PWR_TRIAC_EN        LL_GPIO_PIN_8
#define PIN_PWR_ZERO_IN_PORT    GPIOA
#define PIN_PWR_ZERO_IN         LL_GPIO_PIN_12
#define PIN_STATION_SENS_PORT   GPIOB
#define PIN_STATION_SENS        LL_GPIO_PIN_15
// EXTI
#define EXTI_PWR_ZC_CONFIG_LINE LL_EXTI_CONFIG_LINE12
#define EXTI_PWR_ZC_CONFIG_PORT LL_EXTI_CONFIG_PORTA
#define EXTI_PWR_ZC_LINE        LL_EXTI_LINE_12
#define EXTI_PWR_ZC_IRQn        EXTI4_15_IRQn

// EXTI IRQ Handler Remap
#define GPIO_PWR_ZC__IRQHandler EXTI4_15_IRQHandler

// ---   SERIAL UI   ---
// GPIO
#define PIN_SER_UI_RX_TX_PORT   GPIOA
#define PIN_SER_UI_TX       LL_GPIO_PIN_2
#define PIN_SER_UI_RX       LL_GPIO_PIN_3

// UART
#define UART_SER_UI            USART2
#define UART_SER_UI_BAUDRATE   115200
#define UART_SER_UI_IRQn       USART2_IRQn
// UART IRQ Handler Remap
#define UART_Ser_Ui__IRQHandler USART2_IRQHandler

// DMA
#define DMA_SER_UI                DMA1
#define DMA_SER_UI_RX_CHANNEL     LL_DMA_CHANNEL_1
#define DMA_SER_UI_RX_BUFFER_SIZE 64
#define DMA_SER_UI_RX_REQUEST     LL_DMAMUX_REQ_USART2_RX
#define DMA_SER_UI_IRQn           DMA1_Channel1_IRQn
// DMA IRQ Handler Remap
#define DMA_Ser_Ui__IRQHandler     DMA1_Channel1_IRQHandler


#ifdef __cplusplus
}
#endif

#endif /*__ GPIO_H__ */
