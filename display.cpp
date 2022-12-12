#include "display.h"

Menue::Menue(){
  submenue functions_menue = {
    "Functions",
    0,
    false,
    {
      {"Sleep D. (s)", 0, "i", 1, 3600},
      {"Sleep T. (C)", 0, "f", 0, 500},
      {"Hib. D. (s)", 0, "i", 1, 3600},
      {"Hib T. (C)", 0, "f", 0, 500}
    }
  };

  submenue pid_menue = {
    "PID",
    0,
    false,
    {
      {"KP", 0, "f", 0, 100},
      {"KI", 0, "f", 0, 100},
      {"KD", 0, "f", 0, 100}
    }
  };

  submenue temp_calib_menue = {
    "Temp. Calibration",
    0,
    false,
    {
      {"A", 0, "f", -100, 100},
      {"B", 0, "f", -100, 100},
      {"C", 0, "f", -100, 100},
    }
  };

  menue menue_structure = {
    "Main Menue",
    0,
    false,
    {functions_menue,pid_menue,temp_calib_menue}
  };
}

void Menue::display_menue(){
  u8g2.setFontMode(1);

  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, u8g2.getDisplayWidth(), 13);

  u8g2.setDrawColor(1);
  u8g2.drawHLine(0, 15, u8g2.getDisplayWidth());

  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr( 0, 12, "Main Menue");

  u8g2.setDrawColor(1);
  u8g2.drawBox(u8g2.getDisplayWidth()-15, 25, 6, 26);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(u8g2.getDisplayWidth()-16, 25, 9652);
  u8g2.drawGlyph(u8g2.getDisplayWidth()-16, 60, 9662);
  
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_profont12_mr);
  u8g2.drawStr( 10, 30, "Entry 1");
  u8g2.drawStr( 10, 40, "Entry 2");
  u8g2.drawStr( 10, 50, "Entry 3");
  u8g2.drawStr( 10, 60, "Entry 4");
  
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(0, 40+2, 9658);
}

void Menue::display_submenue(){
  u8g2.setFontMode(1);

  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, u8g2.getDisplayWidth(), 13);

  u8g2.setDrawColor(1);
  u8g2.drawHLine(0, 15, u8g2.getDisplayWidth());

  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr( 0, 12, "Main Menue");

  u8g2.setDrawColor(1);
  u8g2.drawBox(u8g2.getDisplayWidth()-15, 25, 6, 26);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(u8g2.getDisplayWidth()-16, 25, 9652);
  u8g2.drawGlyph(u8g2.getDisplayWidth()-16, 60, 9662);
  
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_profont12_mr);
  u8g2.drawStr( 10, 30, "Entry 1");
  u8g2.drawStr( 10, 40, "Entry 2");
  u8g2.drawStr( 10, 50, "Entry 3");
  u8g2.drawStr( 10, 60, "Entry 4");
  
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(0, 40+2, 9658);
}

void Menue::display_menueitem(){

}

Graph::Graph(int x, int y, int xs, int ys, int min, int max){
  xpos = x;
  ypos = y;
  xsize = xs;
  ysize = ys;
  minx = min;
  maxx = max;
}

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
  //u8g2.drawLine(xpos, ypos+ysize, xpos, ypos);
  //u8g2.drawLine(xpos, ypos, xpos+3, ypos+4);
  //u8g2.drawLine(xpos, ypos, xpos-3, ypos+4);

  //u8g2.drawLine(xpos, ypos+ysize, xpos+xsize, ypos+ysize);
  //u8g2.drawLine(xpos+xsize, ypos+ysize, xpos+xsize-4, ypos+ysize+3);
  //u8g2.drawLine(xpos+xsize, ypos+ysize, xpos+xsize-4, ypos+ysize-3);
  u8g2.drawXBMP(0, 0, 128, 64, graph_bits);
}

void Graph::draw_graph(){
  draw_cord();
  int xprev = 0;
  int yprev = 0;

  for(int i = 0; i < size; i++){

    int y = map(buffer[(start+i+1)%GraphBufSize], minx, maxx, ypos+ysize, ypos);
    int x = map(i, 0, GraphBufSize, xpos, xpos+xsize);

    if (i >= 1){
      u8g2.drawLine(xprev, yprev, x, y);
    }

    xprev = x;
    yprev = y;
  } 
}


