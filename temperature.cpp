#include "temperature.h"

Temperature::Temperature(MAX6675* thermocouple, State* state, SettingsEEPROM* settings){
  this->thermocouple = thermocouple;
  this->state = state;
  this->settings = settings;
}

bool Temperature::testTemp(){
  return isnan(this->thermocouple->readCelsius());
}

int Temperature::messureTemp(){
  int raw = this->thermocouple->readCelsius();
  if (raw <= 10 or raw > 500){
    this->state->READING_ERROR = true;
    return(-1);
  }
  else{
    return(this->correct_temp(raw));
  }
}

int Temperature::correct_temp(int raw){
  int corrected = this->settings->TC_A * raw * raw + this->settings->TC_B * raw + this->settings->TC_C;   //Ax² + Bx + C
  return(corrected);
}