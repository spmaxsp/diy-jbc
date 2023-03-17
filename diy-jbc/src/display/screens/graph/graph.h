#ifndef GRAPH_H_
#define GRAPH_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "../../screenmanager.h"

#include "./graphics/graph_graphics.h"

#define GraphBufSize 50

class Graph: public Screen {
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
    void draw_graph();
    void push(int n);

  public:
    Graph(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int x, int y, int xs, int ys, int min, int max);
    void display();
    bool handle_input(Input input);
};

#endif