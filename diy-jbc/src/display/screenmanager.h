#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include "input.h"

class ScreenManager {
    private:
        Screen* active_screen;
        Screen* screens[3];
        int screen_count = 0;
        void set_active_screen(int screen_id);
    public:
        ScreenManager();
        void display();
        void handle_input(Input* input);
        void add_screen(Screen* screen);
};

class Screen {
    public:
        virtual bool handle_input(Input* input)=0;
        virtual void display()=0;
};

#endif /* SCREENMANAGER_H_ */

