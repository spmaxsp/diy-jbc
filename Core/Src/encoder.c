#include "encoder.h"

// Private variables
static int16_t min = 0;
static int16_t max = 0;

// Public functions
void Encoder_SetMinMax(int16_t new_min, int16_t new_max)
{
    if (new_min < new_max)
    {
        min = min;
        max = max;

        LL_TIM_SetAutoReload(TIM_ENCODER, max - min);
    }
}

void Encoder_SetCounter(int16_t value)
{
    if (value >= min && value <= max)
    {
        LL_TIM_SetCounter(TIM_ENCODER, value);
    }
    else if (value < min)
    {
        LL_TIM_SetCounter(TIM_ENCODER, min);
    }
    else
    {
        LL_TIM_SetCounter(TIM_ENCODER, max);
    }
}

int16_t Encoder_GetCounter(void)
{
    return LL_TIM_GetCounter(TIM_ENCODER);
}