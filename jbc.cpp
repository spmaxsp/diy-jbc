#include <Arduino.h>
#include "jbc.h"

Jbc::Jbc(int max_cycles){
  this->max_cycles = max_cycles;
  this->main_cycle = 0;
  this->active_cycles = 0;
  this->heating_phase = false;
}

void Jbc::begin(int ZERO_CROSSING_PIN, int GATE_PIN) {
  this->ZERO_CROSSING_PIN = ZERO_CROSSING_PIN;
  this->GATE_PIN = GATE_PIN;
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, LOW);
  pinMode(ZERO_CROSSING_PIN, INPUT_PULLUP);
}

void Jbc::run_heating_phase() {
  this->heating_phase = true;
  this->main_cycle = 0;
}

void Jbc::end_heaing_phase() {
  this->heating_phase = false;
  digitalWrite(GATE_PIN, LOW);
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
      digitalWrite(GATE_PIN,HIGH);
     }
     else{
      digitalWrite(GATE_PIN,LOW);
      this->end_heaing_phase();
     }
     main_cycle++;
  }
  else {
    digitalWrite(GATE_PIN,LOW);
  }
}
