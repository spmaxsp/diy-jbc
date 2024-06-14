#ifndef JBC_H_
#define JBC_H_
#include <Arduino.h>

class Jbc {  
  private:
      //pins
      int zerro_crossing_pin;
      int gate_pin;

      //power
      int main_cycle;
      int active_cycles;
      int max_cycles;

      bool heating_phase;
      unsigned long int last_heat;

  public:  
      Jbc(int max_cycles, int zerro_crossing_pin, int gate_pin);
      void begin();

      void set_power_target(int target);
      void end_heaing_phase();
      void run_heating_phase();

      void zeroCrossingInterrupt();
      
      bool get_heating_phase();
      unsigned long int get_last_heat();
};

#endif
