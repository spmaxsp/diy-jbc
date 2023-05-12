#include "mainscreen.h"

MainScreen::MainScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  this->u8g2ref = u8g2ref;
}

void MainScreen::display(){
  u8g2ref->clearBuffer();
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr(0, 10, "Main Screen");
  u8g2ref->sendBuffer();
}

bool MainScreen::handle_input(Input* input){
  if (input->button_blue_pressed or input->button_rotary_pressed){
    return false;
  }
  return true;  
}