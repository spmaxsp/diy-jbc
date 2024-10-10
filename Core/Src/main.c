

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "eeprom.h"
#include "encoder.h"
#include "ser_ui.h"
#include "settings.h"
#include "display.h"
#include "temperature.h"
#include "ws2812b.h"
#include "pwr_ctrl.h"

#include <stdio.h>

settings_t settings;


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    /* SysTick_IRQn interrupt configuration */
    // NVIC_SetPriority(SysTick_IRQn, 3);   // SysTick_ISR not used in this project

    /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
    LL_SYSCFG_DisableDBATT(LL_SYSCFG_UCPD1_STROBE | LL_SYSCFG_UCPD2_STROBE);

    /* Configure the system clock */
    SystemClock_Config();

    LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);
    LL_RCC_SetTIMClockSource(LL_RCC_TIM1_CLKSOURCE_PCLK1);

    /* Peripherals clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM14);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);

    /* Configure and Initialize Hardware Peripherals */

    /* DMA */
    DMA_Ser_Ui__Init();
    DMA_WS2812B__Init();

    /* GPIO */
    GPIO_Button__Init();
    GPIO_PWR__Init();

    /* I2C */
    I2C__Init();
    /* Init Display */
    Display_Init();

    /* SPI */
    SPI__Init();

    /* TIM */
    TIM_Encoder__Init();
    TIM_Encoder__Enable();
    TIM_WS2812B__Init();

    /* USART */
    USART_Ser_Ui__Init();


    /* Enable Serial UI DMA */
    DMA_Ser_Ui__Enable();

    /* Configure MainloopTick */
    MainLoopTimer_Config(10);  // 10Hz = 100ms


    /* EEPROM */
    Recover_from_EEPROM();

    /* Infinite loop */
    while (1)
    {
    }
}

void TIM_MainLoop__IRQHandler(void){
    static uint32_t counter = 0;
    static uint32_t temperature = 0;

    /* Clear the update interrupt flag */
    LL_TIM_ClearFlag_UPDATE(TIM_MAIN_LOOP);

    /* Get Encoder Counter */
    //int encoder = Encoder_GetCounter();

    /* Get Temperature */
    switch (counter)
    {
    case 0:
        Temperature_StartConversion();
        break;
    case 3:
        temperature = Temperature_Read();
        temperature = Temperature_Convert_Celsius(temperature);
        break;
    default:
        break;
    }
    
    WS2812B_SetColor(0, 0, 0, counter*25);
    WS2812B_SetColor(1, 0, counter*25, 0);
    WS2812B_SetColor(2, counter*25, 0, 0);

    WS2812B_UpdateLEDs();
    
    /* Send data to serial interface */
    //USART_Ser_Ui__Tx_Blocking((uint8_t *)"Counter: ", 9);
    //static char buffer[10];
    //sprintf(buffer, "%i \n", encoder);
    //USART_Ser_Ui__Tx_Blocking((uint8_t *)buffer, 9);
    
    /* Display */
    //Display_Render_Test(temperature);
    Display_Render_Main();

    /* Increment counter */
    counter++;
    if(counter > 10){
        counter = 0;
    }
}