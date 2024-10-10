
#include "gpio_button.h"

extern void Pwr_Handle_Zero_Crossing(void);

void GPIO_PWR_ZC__IRQHandler(void){
    if (LL_EXTI_IsActiveRisingFlag_0_31(EXTI_PWR_ZC_LINE) != SET)
    {
        Pwr_Handle_Zero_Crossing();
    }
    LL_EXTI_ClearRisingFlag_0_31(EXTI_PWR_ZC_LINE);
    LL_EXTI_ClearFallingFlag_0_31(EXTI_PWR_ZC_LINE);
}


void GPIO_PWR__Init(void){
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    // TRIAC ENABLE
    GPIO_InitStruct.Pin = PIN_PWR_TRIAC_EN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(PIN_PWR_TRIAC_EN_PORT, &GPIO_InitStruct);

    // ZERO CROSSING INTERRUPT
    GPIO_InitStruct.Pin = PIN_PWR_ZERO_IN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_PWR_ZERO_IN_PORT, &GPIO_InitStruct);

    // STATION SENSOR INPUT
    GPIO_InitStruct.Pin = PIN_STATION_SENS;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_STATION_SENS_PORT, &GPIO_InitStruct);


    // EXTI interrupt init
    LL_EXTI_SetEXTISource(EXTI_PWR_ZC_CONFIG_PORT, EXTI_PWR_ZC_CONFIG_LINE);

    LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
    EXTI_InitStruct.Line_0_31 = EXTI_PWR_ZC_LINE;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);

    NVIC_SetPriority(EXTI_PWR_ZC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(EXTI_PWR_ZC_IRQn);

}

void GPIO_Station_Sense__GetState(void){
    return LL_GPIO_IsInputPinSet(PIN_STATION_SENS_PORT, PIN_STATION_SENS);
}

void GPIO_Triac__Enable(void){
    LL_GPIO_SetOutputPin(PIN_PWR_TRIAC_EN_PORT, PIN_PWR_TRIAC_EN);
}

void GPIO_Triac__Disable(void){
    LL_GPIO_ResetOutputPin(PIN_PWR_TRIAC_EN_PORT, PIN_PWR_TRIAC_EN);
}