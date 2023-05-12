#include "display.h"

Display::Display(int button_red, int button_blue, int rotary_sw, int rotary_clk, int rotary_dt):
                    u8g2(U8G2_R0, U8X8_PIN_NONE),
                    graph_obj(&u8g2, 10, 10, 100, 50, 0, 300),
                    mainscreen_obj(&u8g2),
                    menuescreen_obj(&u8g2),
                    screenmanager(),
                    input(button_red, button_blue, rotary_sw, rotary_clk, rotary_dt){
}

void Display::begin(){
    u8g2.begin();

    screenmanager.add_screen(&mainscreen_obj);  // 0
    screenmanager.add_screen(&menuescreen_obj); // 1
    screenmanager.add_screen(&graph_obj);       // 2

    screenmanager.set_active_screen(0);
}

void Display::update(){
    input.update();
    u8g2.clearBuffer();	
    screenmanager.handle_input(&input);
    screenmanager.display();
    u8g2.sendBuffer();
}





