#include "ser_interface.h"

SerialInterface::SerialInterface(Stream* serStreamRef, State* state){
  this->serStreamRef = serStreamRef;
  this->state = state;
  this->buf_cursor = 0;
}