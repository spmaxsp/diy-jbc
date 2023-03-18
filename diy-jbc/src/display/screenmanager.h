#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include "input.h"

class Screen {
    public:
        virtual bool handle_input(Input* input)=0;
        virtual void display()=0;
};

class ScreenManager {
    private:
        Screen* active_screen;
        Screen* screens[3];
        int screen_count = 0;
    public:
        ScreenManager();
        void display();
        void handle_input(Input* input);
        void add_screen(Screen* screen);
        void set_active_screen(int screen_id);
};

#endif /* SCREENMANAGER_H_ */

