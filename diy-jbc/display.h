#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "graph.h"
#include "mainscreen.h"
#include "menue.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Display{ 
  private: 
    U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

    bool display_menue;
    bool display_main;
    bool display_graph;

    Graph graph_obj;
    MainScreen mainscreen_obj;
    MenueScreen menuescreen_obj;    
    
  public:
    Display();
    void begin();  
    
};

#endif
