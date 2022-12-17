#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_
#include <Arduino.h>
#include <U8g2lib.h>

class MainScreen {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
  public:
    MainScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
};

#endif