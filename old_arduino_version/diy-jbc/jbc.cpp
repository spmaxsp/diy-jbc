#include <Arduino.h>
#include "jbc.h"

Jbc::Jbc(int max_cycles, int zerro_crossing_pin, int gate_pin){
  this->zerro_crossing_pin = zerro_crossing_pin;
  this->gate_pin = gate_pin;
  this->max_cycles = max_cycles;
  this->main_cycle = 0;
  this->active_cycles = 0;
  this->heating_phase = false;
}

void Jbc::begin() {
  pinMode(gate_pin, OUTPUT);
  digitalWrite(gate_pin, LOW);
  pinMode(zerro_crossing_pin, INPUT_PULLUP);
}

void Jbc::run_heating_phase() {
  this->heating_phase = true;
  this->main_cycle = 0;
}

void Jbc::end_heaing_phase() {
  this->heating_phase = false;
  digitalWrite(gate_pin, LOW);
  this->last_heat = millis();
}

bool Jbc::get_heating_phase(){
  return this->heating_phase;
}
      
unsigned long int Jbc::get_last_heat(){
  return this->last_heat;
}

void Jbc::set_power_target(int target){
  this->active_cycles = map(target,0,100,0,this->max_cycles);
}

void Jbc::zeroCrossingInterrupt(){
  if (this->heating_phase){  
     if(this->main_cycle < this->active_cycles){
      digitalWrite(gate_pin,HIGH);
     }
     else{
      digitalWrite(gate_pin,LOW);
      this->end_heaing_phase();
     }
     main_cycle++;
  }
  else {
    digitalWrite(gate_pin,LOW);
  }
}
