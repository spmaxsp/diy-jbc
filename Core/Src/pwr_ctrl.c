#include "pwr_ctrl.h"

int request_heating = 0;
int heating_active = 0;

int power_set = 0;
int mains_half_wave_counter = 0;

const int max_heating_half_waves = 100;  // 100 half waves @ 50Hz = 1 second


void Pwr_Handle_Zero_Crossing(void){

    if (request_heating){
        heating_active = 1;
        request_heating = 0;
        mains_half_wave_counter = 0;
    }

    if (heating_active == 1){
        if (mains_half_wave_counter < power_set){
            GPIO_Triac__Enable();
        } else {
            GPIO_Triac__Disable();
            heating_active = 0;
        }
        mains_half_wave_counter++;
    }
    else {
        GPIO_Triac__Disable();
    }
}

void Request_Heating(int power){
    if (!request_heating && !heating_active){
    
        if (power > max_heating_half_waves){
            power = max_heating_half_waves;
        }
        if (power < 0){
            power = 0;
        }

        power_set = power;
        request_heating = 1;
    }
}

uint8_t Get_Heating(void){
    return (heating_active || request_heating);
}