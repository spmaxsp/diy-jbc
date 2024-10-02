
#include "ws2812b.h"

uint8_t leds_color_data[WS2812B_LED_COUNT][3] = {0};

extern uint32_t ws2812b_dma_buffer[WS2812B_LED_COUNT * 24];

void WS2812B_UpdateLEDs(void){
    const uint32_t arr = TIM_WS2812B->ARR + 1;
    const uint32_t pulse_high = (3 * arr / 4) - 1;
    const uint32_t pulse_low = (1 * arr / 4) - 1;

    for(uint8_t i = 0; i < WS2812B_LED_COUNT; i++){
        for(uint8_t j = 0; j < 3; j++){
            for(uint8_t k = 0; k < 8; k++){
                if(leds_color_data[i][j] & (1 << (7 - k))){
                    ws2812b_dma_buffer[i * 24 + j * 8 + k] = pulse_high;
                } else {
                    ws2812b_dma_buffer[i * 24 + j * 8 + k] = pulse_low;
                }
            }
        }
    }

    DMA_WS2812B__ReEnable();
}

void WS2812B_SetColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b){
    leds_color_data[led][0] = g;
    leds_color_data[led][1] = r;
    leds_color_data[led][2] = b;
}

