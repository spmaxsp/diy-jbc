#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_
#include <Arduino.h>
#include <max6675.h>
#include "state.h"
#include "settings.h"


class Temperature{
  private:
      int correct_temp(int raw);
      MAX6675* thermocouple;
      State* state;
      SettingsEEPROM* settings;

  public:
      Temperature(MAX6675* thermocouple, State* state, SettingsEEPROM settings*);
      bool testTemp();
      int messureTemp();
};


#endif