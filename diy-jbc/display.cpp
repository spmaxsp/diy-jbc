#include "display.h"

Display::Display():u8g2(U8G2_R0, U8X8_PIN_NONE),graph_obj(&u8g2, 10, 10, 100, 50, 0, 300),mainscreen_obj(&u8g2),menuescreen_obj(&u8g2){
  
}

void Display::begin(){

}





