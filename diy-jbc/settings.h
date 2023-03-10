#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <Arduino.h>
#include <EEPROM.h>

typedef struct {
    int testdata_a;
    
    double KP;
    double KI;
    double KD;

    double TC_A;
    double TC_B;
    double TC_C;    

    int SLEEP_DELAY;
    int SLEEP_TEMP;
    int HIBERNATE_DELAY;
    int HIBERNATE_TEMP; 
    
    int testdata_b;
} MemObj;

#define EE_ADRESS 0
#define TEST_DATA 2735 //b0000101010101111

class SettingsEEPROM{ 
  private: 
  	int eeAddress;
    bool check_eeprom(MemObj mem_object); 
    void change_pid_changegain_flagg(MemObj mem_object);
    
  public:  
    SettingsEEPROM();
    void read_settings();
    void save_settings();
    void gains_set();

    double KP;
    double KI;
    double KD;

    double TC_A;
    double TC_B;
    double TC_C;  

    int SLEEP_DELAY;
    int SLEEP_TEMP;
    int HIBERNATE_DELAY;
    int HIBERNATE_TEMP; 

    bool new_pid_gains;
};

#endif