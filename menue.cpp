#include "menue.h"

MenueScreen::MenueScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  this->u8g2ref = u8g2ref;

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
  mainmenue menue_structure = {
    "Main Menue",
    0,
    false,
    {functions_menue,pid_menue,temp_calib_menue}
  };
}

void MenueScreen::display_menue(){
  u8g2ref->setFontMode(1);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(0, 0, u8g2ref->getDisplayWidth(), 13);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawHLine(0, 15, u8g2ref->getDisplayWidth());

  u8g2ref->setDrawColor(0);
  u8g2ref->setFont(u8g2_font_ncenB08_tr);
  u8g2ref->drawStr( 0, 12, "Main Menue");

  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(u8g2ref->getDisplayWidth()-15, 25, 6, 26);
  u8g2ref->setFont(u8g2_font_unifont_t_symbols);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 25, 9652);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 60, 9662);
  
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr( 10, 30, "Entry 1");
  u8g2ref->drawStr( 10, 40, "Entry 2");
  u8g2ref->drawStr( 10, 50, "Entry 3");
  u8g2ref->drawStr( 10, 60, "Entry 4");
  
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_unifont_t_symbols);
  u8g2ref->drawGlyph(0, 40+2, 9658);
}

void MenueScreen::display_submenue(){
  u8g2ref->setFontMode(1);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(0, 0, u8g2ref->getDisplayWidth(), 13);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawHLine(0, 15, u8g2ref->getDisplayWidth());

  u8g2ref->setDrawColor(0);
  u8g2ref->setFont(u8g2_font_ncenB08_tr);
  u8g2ref->drawStr( 0, 12, "Main Menue");

  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(u8g2ref->getDisplayWidth()-15, 25, 6, 26);
  u8g2ref->setFont(u8g2_font_unifont_t_symbols);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 25, 9652);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 60, 9662);
  
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr( 10, 30, "Entry 1");
  u8g2ref->drawStr( 10, 40, "Entry 2");
  u8g2ref->drawStr( 10, 50, "Entry 3");
  u8g2ref->drawStr( 10, 60, "Entry 4");
  
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_unifont_t_symbols);
  u8g2ref->drawGlyph(0, 40+2, 9658);
}