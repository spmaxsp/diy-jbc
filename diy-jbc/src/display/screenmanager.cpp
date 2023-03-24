#include "screenmanager.h"

ScreenManager::ScreenManager(){
    this->active_screen = nullptr;
}

void ScreenManager::display(){
    if (this->active_screen != nullptr){
        this->active_screen->display();
    }
}

void ScreenManager::handle_input(Input* input){
    if (this->active_screen != nullptr){
        if (this-> active_screen != this->screens[0]){
            if (this->active_screen->handle_input(input) == false){
                set_active_screen(0);
            }
        } 
        else {
            if (this->active_screen->handle_input(input) == false){
                if (input->button_blue_pressed){
                    set_active_screen(1);
                }
                if (input->button_rotary_pressed){
                    set_active_screen(2);
                }
            }
        }
    }
}

void ScreenManager::add_screen(Screen* screen){
    this->screens[this->screen_count] = screen;
    this->screen_count++;
}

void ScreenManager::set_active_screen(int screen_id){
    this->active_screen = this->screens[screen_id];
}