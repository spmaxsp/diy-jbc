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

void MenueScreen::display(){
  if (menue_structure.active){
    display_menue(&menue_structure);
  }
  else{
    submenue* submenue = &menue_structure.menue_items[menue_structure.selected];
    if (submenue->active){
      display_submenue(submenue);
    }
    else{
      menueitem* menueitem = &submenue->menue_items[submenue->selected];
      display_menueitem(menueitem);
    }
  }
}

void MenueScreen::setup_encoder(Input* input){
  if (menue_structure.active){
    input->change_rotary_value(menue_structure.selected);
    input->change_rotary_min_max(0,len(menue_structure.menue_items)-1);
  }
  else{
    submenue* submenue = &menue_structure.menue_items[menue_structure.selected];
    if (submenue->active){
      input->change_rotary_value(submenue->selected);
      input->change_rotary_min_max(0,len(submenue->menue_items)-1);
    }
    else{
      menueitem* menueitem = &submenue->menue_items[submenue->selected];
      input->change_rotary_value(menueitem->value);
      input->change_rotary_min_max(menueitem->min_value,menueitem->max_value);
    }
  }
}

void MenueScreen::handle_input(Input* input){
  if (menue_structure.active){
    if(input->button_red_pressed){
      return false;
    }
    else if (input->button_blue_pressed or input->button_rotary_pressed){
      menue_structure.active = false;
      menue_structure.menue_items[menue_structure.selected].active = true;
      this->setup_encoder(input);
    } 
    menue_structure.selected = input->rotary_value;
  }
  else{
    submenue* submenue = &menue_structure.menue_items[menue_structure.selected];
    if (submenue->active){
      if(input->button_red_pressed){
        submenue->active = false;
        menue_structure.active = true;
        this->setup_encoder(input);
      }
      else if (input->button_blue_pressed or input->button_rotary_pressed){
        submenue->active = false;
        this->setup_encoder(input);
      } 
      submenue->selected = input->rotary_value;
    }
    else{
    
    }
  }
  return true;
}

void MenueScreen::display_menue(mainmenue* menue){
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

void MenueScreen::display_submenue(submenue* menue){
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

void MenueScreen::display_menueitem(menueitem* item){

}