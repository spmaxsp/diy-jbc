#ifndef SERIAL_H
#define SERIAL_H
#include <Arduino.h>

class Serial {  


  public:  
      Serial(int max_cycles);
      void begin(int ZERO_CROSSING_PIN, int GATE_PIN);
      void set_power_target(int target);
      void end_heaing_phase();
      void run_heating_phase();
      void zeroCrossingInterrupt();
      bool heating_phase;
      unsigned long int last_heat;
};

#endif