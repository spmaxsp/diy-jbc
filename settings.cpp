#include <Arduino.h>
#include "settings.h"

SettingsEEPROM::SettingsEEPROM(){
  KP = 4.4;
  KI = 0.9;
  KD = 0.05;
  TC_A = 0;
  TC_B = 1;
  TC_C = 0;
  SLEEP_DELAY = 1.5 * 60;
  SLEEP_TEMP = 150;
  HIBERNATE_DELAY = 3 * 60;
  HIBERNATE_TEMP = 0; 
}

bool SettingsEEPROM::check_eeprom(MemObj mem_object){
  if (mem_object.testdata_a == TEST_DATA && mem_object.testdata_a == TEST_DATA){
    return true;
  }
  else {
    return false;
  }
}

void SettingsEEPROM::read_settings(){
  MemObj mem_object;

  EEPROM.get(EE_ADRESS, mem_object);
  
  if(this->check_eeprom(mem_object)){
    this->KP = mem_object.KP;
    this->KI = mem_object.KI;
    this->KD = mem_object.KD;
    this->TC_A = mem_object.TC_A;
    this->TC_B = mem_object.TC_B;
    this->TC_C = mem_object.TC_C;
    this->SLEEP_DELAY = mem_object.SLEEP_DELAY;
    this->SLEEP_TEMP = mem_object.SLEEP_TEMP;
    this->HIBERNATE_DELAY = mem_object.HIBERNATE_DELAY;
    this->HIBERNATE_TEMP = mem_object.HIBERNATE_TEMP; 
  }    
}

void SettingsEEPROM::save_settings(){
  MemObj mem_object;  

  mem_object.testdata_a = TEST_DATA;
  mem_object.testdata_b = TEST_DATA;

  mem_object.KP = this->KP;
  mem_object.KI = this->KI;
  mem_object.KD = this->KD;
  mem_object.TC_A = this->TC_A;
  mem_object.TC_B = this->TC_B;
  mem_object.TC_C = this->TC_C;
  mem_object.SLEEP_DELAY = this->SLEEP_DELAY;
  mem_object.SLEEP_TEMP = this->SLEEP_TEMP;
  mem_object.HIBERNATE_DELAY = this->HIBERNATE_DELAY;
  mem_object.HIBERNATE_TEMP = this->HIBERNATE_TEMP;
  
  EEPROM.put(EE_ADRESS, mem_object);     
}