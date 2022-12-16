#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "graph.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define GraphBufSize 50

typedef struct {
  char title[20];
  double value;
  char type;
  double max_value;
  double min_value;
} menueitem;

typedef struct {
  char title[20];
  int selected;
  bool active;
  menueitem menue_items[];
} submenue;

typedef struct {
  char title[20];
  int selected;
  bool active;
  submenue menue_items[];
} menue;

class MainPage {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
  public:
    MainPage();
    void init(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
};

class Menue {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
    menue menue_structure;
    void display_menue();
    void display_submenue();
    void display_menueitem();
  public:
    Menue();
    void init(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void display();
};

class Graph {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
    
    int buffer[GraphBufSize];
    int start = 0;
    int size = 0;

    int xpos;
    int ypos;
    int xsize;
    int ysize;

    int minx;
    int maxx;

    void draw_cord();

  public:
    Graph(int x, int y, int xs, int ys, int min, int max);
    void init(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void push(int n);
    void draw_graph();
};

class Display{ 
  private: 
    U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

    bool display_menue;
    bool display_main;
    bool display_graph;

    MainPage mainpage_obj;
    Graph graph_obj;
    Menue menue_obj;
    
    
  public:
    Display();
    void begin();  
    
};

#endif
