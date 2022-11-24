#ifndef SER_INTERFACE_H_
#define SER_INTERFACE_H_
#include <Arduino.h>
#include "state.h"

#define MAX_MESSAGE 30

class SerialInterface { 
  private: 
    char buffer[10];
    int buf_cursor;
    Stream *serStreamRef;
    State *state;
    
    void phrase_command();

  public:  
    SerialInterface(Stream* serStreamRef, State* state);
    void read_loop();
};

#endif