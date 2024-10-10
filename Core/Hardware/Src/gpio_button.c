
#include "gpio_button.h"

void GPIO_Button__Init(void){
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    // BUTTON_ENCODER
    GPIO_InitStruct.Pin = PIN_BUTTON_ENCODER;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_BUTTON_ENCODER_PORT, &GPIO_InitStruct);

    // BUTTON_BLUE
    GPIO_InitStruct.Pin = PIN_BUTTON_BLUE;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_BUTTON_BLUE_PORT, &GPIO_InitStruct);

    // BUTTON_RED
    GPIO_InitStruct.Pin = PIN_BUTTON_RED;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(PIN_BUTTON_RED_PORT, &GPIO_InitStruct);
}

uint8_t GPIO_Button_Encoder__GetState(void){
    static uint8_t last_state;
    uint8_t current_state = !(LL_GPIO_IsInputPinSet(PIN_BUTTON_ENCODER_PORT, PIN_BUTTON_ENCODER));
    if (current_state != last_state && current_state == 1){
        last_state = current_state;
        return 1;
    }
    last_state = current_state;
    return 0;
}

uint8_t GPIO_Button_Blue__GetState(void){
    static uint8_t last_state;
    uint8_t current_state = !(LL_GPIO_IsInputPinSet(PIN_BUTTON_BLUE_PORT, PIN_BUTTON_BLUE));
    if (current_state != last_state && current_state == 1){
        last_state = current_state;
        return 1;
    }
    last_state = current_state;
    return 0;
}

uint8_t GPIO_Button_Red__GetState(void){
    static uint8_t last_state;
    uint8_t current_state = !(LL_GPIO_IsInputPinSet(PIN_BUTTON_RED_PORT, PIN_BUTTON_RED));
    if (current_state != last_state && current_state == 1){
        last_state = current_state;
        return 1;
    }
    last_state = current_state;
    return 0;
}