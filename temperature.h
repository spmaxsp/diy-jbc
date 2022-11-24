#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_
#include <Arduino.h>
#include <max6675.h>
#include "state.h"


class Temperature{
  private:
      int correct_temp(int raw);
      MAX6675* thermocouple;
      State* state;

  public:
      Temperature(MAX6675* thermocouple, State* state);
      bool testTemp();
      int messureTemp();
};


#endif