#ifndef STATE_H
#define STATE_H

typedef struct {
    double userTemp = 0;    
    bool SLEEP = false;
    bool HIBERNATE = false;
    bool USER_DISABLE_HEATER = false;
    bool READING_ERROR = false;
} State;

#endif