#include "ser_interface.h"

SerialInterface::SerialInterface(Stream* serStreamRef, State* state){
  this->serStreamRef = serStreamRef;
  this->state = state;
  this->buf_cursor = 0;
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

    if (this->teststr(this->buffer, 0, cmd_set)) {
      if (this->teststr(this->buffer, strlen(cmd_set), cmd_temp)){
        
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

    }
    else if (this->teststr(this->buffer, 0, cmd_disable)) {
      
    }
   
}

bool SerialInterface::teststr(char input[], int start, char search[]){
  return strncmp(input+start, search, strlen(search));
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