
#include "tim_ws2812b.h"

void TIM_WS2812B__Init(void) 
{

    /* GPIO Configuration */
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_WS2812B;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(PIN_WS2812B_PORT, &GPIO_InitStruct);

    /* Timer Configuration */

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 79;   // 64MHz / 80 = 800kHz
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM_WS2812B, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM_WS2812B);
    LL_TIM_SetClockSource(TIM_WS2812B, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_OC_EnablePreload(TIM_WS2812B, TIM_WS2812B_CHANNEL);

    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM_WS2812B, TIM_WS2812B_CHANNEL, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM_WS2812B, TIM_WS2812B_CHANNEL);
    LL_TIM_SetTriggerOutput(TIM_WS2812B, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM_WS2812B);

    // Enable DMA
    LL_TIM_EnableDMAReq_CC1(TIM_WS2812B);

    // Enable Output
    LL_TIM_CC_EnableChannel(TIM_WS2812B, TIM_WS2812B_CHANNEL);
    LL_TIM_DisableCounter(TIM_WS2812B);
}


