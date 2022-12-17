#include "graph.h"

Graph::Graph(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int x, int y, int xs, int ys, int min, int max){
  this->u8g2ref = u8g2ref;

  xpos = x;
  ypos = y;
  xsize = xs;
  ysize = ys;
  minx = min;
  maxx = max;
}

//void Graph::init(){
//  this->u8g2ref = u8g2ref;
//}

void Graph::push(int n){
  if (size == GraphBufSize){
    start = (start + 1)%GraphBufSize;
  }
  else {
    size++;
  }
  buffer[(start+size)%GraphBufSize] = n;
}

void Graph::draw_cord(){
  //u8g2ref->drawLine(xpos, ypos+ysize, xpos, ypos);
  //u8g2ref->drawLine(xpos, ypos, xpos+3, ypos+4);
  //u8g2ref->drawLine(xpos, ypos, xpos-3, ypos+4);

  //u8g2ref->drawLine(xpos, ypos+ysize, xpos+xsize, ypos+ysize);
  //u8g2ref->drawLine(xpos+xsize, ypos+ysize, xpos+xsize-4, ypos+ysize+3);
  //u8g2ref->drawLine(xpos+xsize, ypos+ysize, xpos+xsize-4, ypos+ysize-3);
  u8g2ref->drawXBMP(0, 0, 128, 64, graph_bits);
}

void Graph::draw_graph(){
  draw_cord();
  int xprev = 0;
  int yprev = 0;

  for(int i = 0; i < size; i++){

    int y = map(buffer[(start+i+1)%GraphBufSize], minx, maxx, ypos+ysize, ypos);
    int x = map(i, 0, GraphBufSize, xpos, xpos+xsize);

    if (i >= 1){
      u8g2ref->drawLine(xprev, yprev, x, y);
    }

    xprev = x;
    yprev = y;
  } 
}