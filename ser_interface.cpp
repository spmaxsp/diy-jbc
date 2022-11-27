#include "ser_interface.h"

SerialInterface::SerialInterface(Stream* serStreamRef, State* state){
  this->serStreamRef = serStreamRef;
  this->state = state;
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
      if (this->teststr(this->buffer, strlen(cmd_set), cmd_temp)){
        int start_char = strlen(cmd_set)+strlen(cmd_temp);
        int temp_read = this->read_number(this->buffer, start_char);
        
        if (temp_read >= 0 && temp_read <= 450){
          this->state->userTemp = 1.0 * temp_read;
          this->serStreamRef->println("OK");
        }
        else {      
          this->serStreamRef->println("INPUT NOT VALID");        
        } 
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_p)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_i)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_pid_d)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_s_time)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_h_time)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_s_tmp)){
        
      }
      else if (this->teststr(this->buffer, strlen(cmd_set), cmd_h_tmp)){
        
      }
    }
    else if (this->teststr(this->buffer, 0, cmd_enable)) {
      this->state->USER_DISABLE_HEATER = false;
      this->serStreamRef->println("OK");     
    }
    else if (this->teststr(this->buffer, 0, cmd_disable)) {
      this->state->USER_DISABLE_HEATER = true;
      this->serStreamRef->println("OK");
    }
    else if (this->teststr(this->buffer, 0, cmd_set_eeprom)) {
      
    }
    else if (this->teststr(this->buffer, 0, cmd_print_settings)) {
      
    }
    else if (this->teststr(this->buffer, 0, cmd_start_graph)) {
      this->graph_enable = true;
      this->serStreamRef->println("OK");
    }
    else if (this->teststr(this->buffer, 0, cmd_stop_graph)) {
      this->graph_enable = false;
      this->serStreamRef->println("OK");
    }
   
}

int SerialInterface::read_number(char input[], int start){
  int index = 0;
  int output = 0; 
  while (isdigit(input[index+start])) {
    output = output + int(input[index+start] - '0') * pow(10, index);
    index++;
  }
  return output;
}

bool SerialInterface::teststr(char input[], int start, char search[]){
  return strncmp(input+start, search, strlen(search));
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