#ifndef GRAPH_H_
#define GRAPH_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "graph_graphics.h"

#define GraphBufSize 50

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
    Graph(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int x, int y, int xs, int ys, int min, int max);
    //void init(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void push(int n);
    void draw_graph();
};

#endif