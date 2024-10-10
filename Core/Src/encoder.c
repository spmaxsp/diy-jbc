#include "encoder.h"

#include <math.h>

// Private variables
int16_t min = 0;
int16_t max = 0;

const float acel = 1.4;

// Public functions
void Encoder_SetMinMax(int16_t new_min, int16_t new_max)
{
    if (new_min < new_max)
    {
        min = new_min;
        max = new_max;

        LL_TIM_SetAutoReload(TIM_ENCODER, (max - min)*2);
    }
}

void Encoder_SetCounter(int16_t value)
{
    if (value >= min && value <= max)
    {
        LL_TIM_SetCounter(TIM_ENCODER, value*2);
    }
    else if (value < min)
    {
        LL_TIM_SetCounter(TIM_ENCODER, min*2);
    }
    else
    {
        LL_TIM_SetCounter(TIM_ENCODER, max*2);
    }
}

int16_t Encoder_GetCounter(void)
{
    return min + (LL_TIM_GetCounter(TIM_ENCODER)/2);
}


int16_t Encoder_ResetAndGetDelta(void)
{
    int16_t delta = Encoder_GetCounter();
    Encoder_SetCounter(0);
    return delta;
}

int16_t Encoder_ResetAndGetDelta_Acel(void)
{
    int16_t delta = Encoder_GetCounter();
    Encoder_SetCounter(0);
    return floor(delta*delta*acel);
}