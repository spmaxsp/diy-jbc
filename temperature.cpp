#include "temperature.h"

Temperature::Temperature(MAX6675* thermocouple, State* state){
  this->thermocouple = thermocouple;
  this->state = state;
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
  int corrected = raw;
  return(corrected);
}