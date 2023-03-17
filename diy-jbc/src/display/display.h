#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <Arduino.h>
#include <U8g2lib.h>


#include "./screens/graph/graph.h"
#include "./screens/mainscreen/mainscreen.h"
#include "./screens/menue/menue.h"

#include "screenmanager.h"

#include "input.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Display{ 
  private: 
    U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

    Graph graph_obj;
    MainScreen mainscreen_obj;
    MenueScreen menuescreen_obj;  

    ScreenManager screenmanager;

    Input input;  
    
  public:
    Display(int button_red, int button_blue, int rotary_sw, int rotary_clk, int rotary_dt);
    void begin();  
    void update();
};

#endif
