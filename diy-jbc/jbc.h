#ifndef JBC_H_
#define JBC_H_
#include <Arduino.h>

#define ZERO_CROSSING_PIN  2 //INT0 (pullup)
#define GATE_PIN    4

class Jbc {  
      //power
      int main_cycle;
      int active_cycles;
      int max_cycles;

      bool heating_phase;
      unsigned long int last_heat;

  public:  
      Jbc(int max_cycles);
      void begin();

      void set_power_target(int target);
      void end_heaing_phase();
      void run_heating_phase();

      void zeroCrossingInterrupt();
      
      bool get_heating_phase();
      unsigned long int get_last_heat();
};

#endif
