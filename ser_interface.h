#ifndef SER_INTERFACE_H_
#define SER_INTERFACE_H_
#include <Arduino.h>
#include "state.h"
#include "settings.h"

#define MAX_MESSAGE 30

class SerialInterface { 
  private: 
    char buffer[10];
    int buf_cursor;
    Stream *serStreamRef;
    State *state;
    SettingsEEPROM* settings;

    bool graph_enable;
    
    void phrase_command();
    int read_number(char input[], int start);
    bool teststr(char input[], int start, char search[]);

  public:  
    SerialInterface(Stream* serStreamRef, State* state, SettingsEEPROM settings*);
    void read_loop();
    void print_graph(double is_temperature, double set_temperature, double pid_output);
};

#endif