#ifndef SCREEN_H_
#define SCREEN_H_

#include "input.h"

class Screen {
    public:
        virtual bool handle_input(Input* input)=0;
        virtual void display()=0;
};

#endif /* SCREEN_H_ */