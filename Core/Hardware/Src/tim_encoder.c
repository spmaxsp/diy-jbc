#include "tim_encoder.h"

// Public functions
void TIM_Encoder__Init(void)
{

    /* GPIO Configuration */
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ENCODER_A;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    LL_GPIO_Init(PIN_ENCODER_A_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_ENCODER_B;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    LL_GPIO_Init(PIN_ENCODER_B_PORT, &GPIO_InitStruct);


    /* Timer Configuration */

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 4294967295;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM_ENCODER, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(   TIM_ENCODER);
    LL_TIM_SetEncoderMode(      TIM_ENCODER, LL_TIM_ENCODERMODE_X2_TI1);

    LL_TIM_IC_SetActiveInput(   TIM_ENCODER, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetPrescaler(     TIM_ENCODER, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetFilter(        TIM_ENCODER, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPolarity(      TIM_ENCODER, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);

    LL_TIM_IC_SetActiveInput(   TIM_ENCODER, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetPrescaler(     TIM_ENCODER, LL_TIM_CHANNEL_CH2, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetFilter(        TIM_ENCODER, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPolarity(      TIM_ENCODER, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);

    LL_TIM_SetTriggerOutput(    TIM_ENCODER, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM_ENCODER);
}

void TIM_Encoder__Enable(void)
{
    LL_TIM_EnableCounter(TIM_ENCODER);
}