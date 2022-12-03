#include "ser_interface.h"

SerialInterface::SerialInterface(Stream* serStreamRef, State* state, SettingsEEPROM* settings){
  this->serStreamRef = serStreamRef;
  this->state = state;
  this->settings = settings;
  this->buf_cursor = 0;
  this->graph_enable = false;
}

void SerialInterface::phrase_command(){
    //Commands:
    //  -SET TEMP 100
    //  -ENABLE
    //  -DISABLE    

    char cmd_set[] = "SET ";
    char cmd_temp[] = "TEMP ";
    char cmd_pid_p[] = "KP ";
    char cmd_pid_i[] = "KI ";
    char cmd_pid_d[] = "KD ";
    char cmd_tc_a[] = "TC_A ";
    char cmd_tc_b[] = "TC_B ";
    char cmd_tc_c[] = "TC_C ";
    char cmd_s_time[] = "T_SLEEP ";
    char cmd_h_time[] = "T_HIBERNATE ";
    char cmd_s_tmp[] = "TMP_SLEEP ";
    char cmd_h_tmp[] = "TMP_HIBERNATE "; 

    char cmd_enable[] = "ENABLE";

    char cmd_disable[] = "DISABLE";

    char cmd_set_eeprom[] = "SAVE";

    char cmd_print_settings[] = "SETTINGS";  

    char cmd_start_graph[] = "START"; 
    
    char cmd_stop_graph[] = "STOP"; 

    if (this->teststr(this->buffer, 0, cmd_set)) {
      this->serStreamRef->println("SET OK");
      if (this->teststr(this->buffer, strlen(cmd_set), cmd_temp)){
        int start_char = strlen(cmd_set)+strlen(cmd_temp);
        this->read_double(this->buffer, start_char, 0, 450, &(this->state->userTemp));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_p)){
        int start_char = strlen(cmd_set)+strlen(cmd_pid_p);
        this->read_double(this->buffer, start_char, 0, 10, &(this->settings->KP));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_i)){
        int start_char = strlen(cmd_set)+strlen(cmd_pid_i);
        this->read_double(this->buffer, start_char, 0, 10, &(this->settings->KI));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_d)){
        int start_char = strlen(cmd_set)+strlen(cmd_pid_d);
        this->read_double(this->buffer, start_char, 0, 10, &(this->settings->KD));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_tc_a)){
        int start_char = strlen(cmd_set)+strlen(cmd_tc_a);
        this->read_double(this->buffer, start_char, -10, 10, &(this->settings->TC_A));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_tc_b)){
        int start_char = strlen(cmd_set)+strlen(cmd_tc_b);
        this->read_double(this->buffer, start_char, -10, 10, &(this->settings->TC_B));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_tc_c)){
        int start_char = strlen(cmd_set)+strlen(cmd_tc_c);
        this->read_double(this->buffer, start_char, -10, 10, &(this->settings->TC_C));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_s_time)){
        int start_char = strlen(cmd_set)+strlen(cmd_s_time);
        this->read_int(this->buffer, start_char, 0, 3600, &(this->settings->SLEEP_DELAY));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_h_time)){
        int start_char = strlen(cmd_set)+strlen(cmd_h_time);
        this->read_int(this->buffer, start_char, 0, 3600, &(this->settings->HIBERNATE_DELAY));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_s_tmp)){
        int start_char = strlen(cmd_set)+strlen(cmd_s_tmp);
        this->read_int(this->buffer, start_char, 0, 450, &(this->settings->SLEEP_TEMP));
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_h_tmp)){
        int start_char = strlen(cmd_set)+strlen(cmd_h_tmp);
        this->read_int(this->buffer, start_char, 0, 450, &(this->settings->HIBERNATE_TEMP));
      }
      
    }
    else if (this->teststr(this->buffer, 0, cmd_enable)) {
      this->state->USER_DISABLE_HEATER = false;
      this->serStreamRef->println("CMD OK");     
    }
    else if (this->teststr(this->buffer, 0, cmd_disable)) {
      this->state->USER_DISABLE_HEATER = true;
      this->serStreamRef->println("CMD OK");
    }
    else if (this->teststr(this->buffer, 0, cmd_set_eeprom)) {
      this->settings->save_settings(); 
      this->serStreamRef->println("CMD OK");
    }
    else if (this->teststr(this->buffer, 0, cmd_print_settings)) {
      this->serStreamRef->println("DUMPING SETTINGS:");
      this->serStreamRef->print("KP:");
      this->serStreamRef->println(this->settings->KP, 4);
      this->serStreamRef->print("KI:");
      this->serStreamRef->println(this->settings->KI, 4);
      this->serStreamRef->print("KD:");
      this->serStreamRef->println(this->settings->KD, 4);
      this->serStreamRef->print("TC_A:");
      this->serStreamRef->println(this->settings->TC_A, 4);
      this->serStreamRef->print("TC_B:");
      this->serStreamRef->println(this->settings->TC_B, 4);
      this->serStreamRef->print("TC_C:");
      this->serStreamRef->println(this->settings->TC_C, 4);
      this->serStreamRef->print("SLEEP_DELAY:");
      this->serStreamRef->println(this->settings->SLEEP_DELAY);
      this->serStreamRef->print("SLEEP_TEMP:");
      this->serStreamRef->println(this->settings->SLEEP_TEMP);
      this->serStreamRef->print("HIBERNATE_DELAY:");
      this->serStreamRef->println(this->settings->HIBERNATE_DELAY);
      this->serStreamRef->print("HIBERNATE_TEMP:");
      this->serStreamRef->println(this->settings->HIBERNATE_TEMP); 
    }
    else if (this->teststr(this->buffer, 0, cmd_start_graph)) {
      this->graph_enable = true;
      this->serStreamRef->println("CMD OK");
    }
    else if (this->teststr(this->buffer, 0, cmd_stop_graph)) {
      this->graph_enable = false;
      this->serStreamRef->println("CMD OK");
    }
   
}

void SerialInterface::read_int(char input[], int start, int min_val, int max_val, int* output){
  double read_double = atof(input+start);
  int read_int = (int) round(read_double);
        
  if (read_int >= min_val && read_int <= max_val){
    *output = read_int;
    this->serStreamRef->println("INPUT OK");
  }
  else {      
    this->serStreamRef->println("INPUT NOT VALID");        
  } 
}

void SerialInterface::read_double(char input[], int start, double min_val, double max_val, double* output){
  double read_double = atof(input+start);
        
  if (read_double >= min_val && read_double <= max_val){
    *output = read_double;
    this->serStreamRef->println("INPUT OK");
  }
  else {      
    this->serStreamRef->println("INPUT NOT VALID");        
  } 
}

bool SerialInterface::teststr(char input[], int start, char search[]){ 
  if (strncmp(input+start, search, strlen(search)) == 0){
    return true;
  }
  return false;
}

void SerialInterface::print_graph(double is_temperature, double set_temperature, double pid_output){
  if (this->graph_enable){
    this->serStreamRef->print(is_temperature);
    this->serStreamRef->print('\t');
    this->serStreamRef->print(set_temperature);
    this->serStreamRef->print('\t');
    this->serStreamRef->print(pid_output);
    this->serStreamRef->print('\n');
  }
}

void SerialInterface::read_loop(){
  char in_char;
  while (this->serStreamRef->available() > 0) {
    in_char = this->serStreamRef->read();
    if (in_char == '\n') {
      this->serStreamRef->print(">>");
      this->serStreamRef->println(this->buffer);
      this->phrase_command();
      this->buf_cursor = 0;
      this->buffer[0] = '\0';
    } else {        
      if (this->buf_cursor < MAX_MESSAGE) {
        this->buffer[this->buf_cursor++] = in_char;
        this->buffer[buf_cursor] = '\0';
      }
    }
  }
}