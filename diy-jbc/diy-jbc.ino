#include <PID_v1.h>
#include <max6675.h>

#include "jbc.h"
#include "temperature.h"
#include "src/display/display.h"
#include "src/ser_interface/ser_interface.h"
#include "src/led/led.h"
#include "settings.h"

#include "state.h"

//                ------Pin Definitions------
#define thermoDO  8
#define thermoCS  7
#define thermoCLK 6

#define stationIN A5 //(pullup)

#define ROT_BUTTON 9
#define ROT_A      10
#define ROT_B      2 //INT1

//         ------Variables for Temperature Controll------
#define MAX_CYCLES 30
#define SLEEP_READ 350  //wait bevore reading tc

#define OUTPUT_MIN 0
#define OUTPUT_MAX 100

double is_temperature, set_temperature, pid_output;

//  #################################################################################
//  #                               SETUP                                           #
//  #################################################################################

SettingsEEPROM settings;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
PID myPID(&is_temperature, &set_temperature, &pid_output, settings.KP, settings.KI, settings.KD, DIRECT);

State state;

Jbc jbc(MAX_CYCLES);
Temperature temperature(&thermocouple, &state, &settings);
SerialInterface ser_interface(&Serial , &state, &settings);
StatusLed status_led;

void setup() {

  settings.read_settings();  

  jbc.begin();
  status_led.begin();
    
  Serial.begin(9600);
  delay(500);

  myPID.SetOutputLimits(OUTPUT_MIN, OUTPUT_MAX);
  myPID.SetMode(AUTOMATIC);

  if (temperature.testTemp()){
    Serial.println("Error reading TC");
    while(1){}
  }

  attachInterrupt(digitalPinToInterrupt(ZERO_CROSSING_PIN), isr, FALLING);
}

void isr(){
  jbc.zeroCrossingInterrupt();
}

//  #################################################################################
//  #                             MAIN LOOP                                         #
//  #################################################################################

void loop() {
  if(settings.new_pid_gains){
    myPID.SetTunings(settings.KP, settings.KI, settings.KD);
    Serial.println("set gains");
    settings.gains_set();
  }
  
  ser_interface.read_loop();
  
  if(state.USER_DISABLE_HEATER or state.READING_ERROR){
    set_temperature = 0;
  }
  else if(state.HIBERNATE){
    set_temperature = settings.HIBERNATE_TEMP;
  }
  else if(state.SLEEP){
    set_temperature = settings.SLEEP_TEMP;
  }
  else {
    set_temperature = state.userTemp;
  }

  if(!jbc.get_heating_phase()){
    if(millis() - jbc.get_last_heat() > SLEEP_READ){
      is_temperature = temperature.messureTemp();
      if(state.READING_ERROR){
        Serial.println("READING_ERROR");
      }
      else{
        myPID.Compute();
        ser_interface.print_graph(is_temperature, set_temperature, pid_output);
        status_led.update(is_temperature);
        jbc.set_power_target(pid_output);
        jbc.run_heating_phase();
      }
    }    
  }
}
