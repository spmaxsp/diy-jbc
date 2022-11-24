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
}

void SerialInterface::read_loop(){
  char in_char;
  while (this->serStreamRef->available() > 0) {
    in_char = this->serStreamRef->read();
    if (in_char == '\n') {
      this->phrase_command();
      this->buf_cursor = 0;
    } else {        
      if (this->buf_cursor < MAX_MESSAGE) {
        this->buffer[this->buf_cursor++] = in_char;
      }
    }
  }
}