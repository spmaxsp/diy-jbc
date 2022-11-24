#ifndef SER_INTERFACE_H_
#define SER_INTERFACE_H_
#include <Arduino.h>
#include "state.h"

class SerialInterface { 
  private: 
    char buffer[10];
    int buf_cursor;
    Stream *serStreamRef;
    State *state;

  public:  
      SerialInterface(Stream* serStreamRef, State* state);
};

#endif