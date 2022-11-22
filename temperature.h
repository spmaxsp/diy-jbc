#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <Arduino.h>
#include <max6675.h>
#include "state.h"
#include "timers.h"

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