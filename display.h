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

class Display{ 
  private: 

  public:  
    
};

class MainPage{

};

class Menue{
  private:
    menue menue_structure;
    void display_menue();
    void display_submenue();
    void display_menueitem();
  public:
    Menue();
    void display();
};

class Graph{
  private:
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
    Graph(int, int, int, int, int, int);
    void push(int n);
    void draw_graph();
};

#endif
