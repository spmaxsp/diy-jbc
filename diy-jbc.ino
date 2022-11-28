#include <AutoPID.h>
#include <max6675.h>

#include "jbc.h"
#include "temperature.h"
#include "display.h"
#include "ser_interface.h"
#include "input.h"
#include "led.h"

#include "state.h"

//                ------Pin Definitions------
#define thermoDO  8
#define thermoCS  7
#define thermoCLK 6


#define ZERO_CROSSING_PIN  2 //INT0 (pullup)
#define GATE_PIN    4

#define stationIN A5 //(pullup)

#define ROT_BUTTON 9
#define ROT_A      10
#define ROT_B      2 //INT1

//         ------Variables for Temperature Controll------
#define MAX_CYCLES 30
#define SLEEP_TEMP 250  //wait bevore reading tc

#define OUTPUT_MIN 0
#define OUTPUT_MAX 100
#define KP 4.4
#define KI 0.9
#define KD 0.05

#define SLEEP_DELAY 1.5 * 60
#define SLEEP_TEMP 150
#define HIBERNATE_DELAY 3 * 60
#define HIBERNATE_TEMP 0

double is_temperature, set_temperature, pid_output;

//  #################################################################################
//  #                               SETUP                                           #
//  #################################################################################


MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
AutoPID myPID(&is_temperature, &set_temperature, &pid_output, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

State state;

Jbc jbc(MAX_CYCLES);
Temperature temperature(&thermocouple, &state);
SerialInterface ser_interface(&Serial , &state);
StatusLed status_led;

void setup() {

  jbc.begin(ZERO_CROSSING_PIN, GATE_PIN);
  status_led.begin();
    
  Serial.begin(9600);
  delay(500);

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
  
  ser_interface.read_loop();
  
  if(state.USER_DISABLE_HEATER or state.READING_ERROR){
    set_temperature = 0;
  }
  else if(state.HIBERNATE){
    set_temperature = HIBERNATE_TEMP;
  }
  else if(state.SLEEP){
    set_temperature = SLEEP_TEMP;
  }
  else {
    set_temperature = state.userTemp;
  }

  if(!jbc.get_heating_phase()){
    if(millis() - jbc.get_last_heat() > SLEEP_TEMP){
      is_temperature = temperature.messureTemp();
      if(state.READING_ERROR){
        Serial.println("READING_ERROR");
      }
      else{
        myPID.run();
        ser_interface.print_graph(is_temperature, set_temperature, pid_output);
        status_led.update(is_temperature);
        jbc.set_power_target(pid_output);
        jbc.run_heating_phase();
      }
    }    
  }
}
