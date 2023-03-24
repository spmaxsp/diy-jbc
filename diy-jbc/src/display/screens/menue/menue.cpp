#include "menue.h"

MenueScreen::MenueScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  this->u8g2ref = u8g2ref;

  this->menue_structure = new SubMenue("Main Menue", 3);

  SubMenue* functions_menue = new SubMenue("Functions", 4);
  functions_menue->add_menueelement(new MenueItem("Sleep D. (s)", 0, 'i', 3600, 1));
  functions_menue->add_menueelement(new MenueItem("Sleep T. (C)", 0, 'f', 500, 0));
  functions_menue->add_menueelement(new MenueItem("Hib. D. (s)", 0, 'i', 3600, 1));
  functions_menue->add_menueelement(new MenueItem("Hib T. (C)", 0, 'f', 500, 0));

  SubMenue* pid_menue = new SubMenue("PID", 3); 
  pid_menue->add_menueelement(new MenueItem("KP", 0, 'f', 100, 0));
  pid_menue->add_menueelement(new MenueItem("KI", 0, 'f', 100, 0));
  pid_menue->add_menueelement(new MenueItem("KD", 0, 'f', 100, 0));

  SubMenue* temp_calib_menue = new SubMenue("Temp. Calibration", 3);
  temp_calib_menue->add_menueelement(new MenueItem("A", 0, 'f', 100, -100));
  temp_calib_menue->add_menueelement(new MenueItem("B", 0, 'f', 100, -100));
  temp_calib_menue->add_menueelement(new MenueItem("C", 0, 'f', 100, -100));

  this->menue_structure->add_menueelement(functions_menue);
  this->menue_structure->add_menueelement(pid_menue);
  this->menue_structure->add_menueelement(temp_calib_menue);
}

void MenueScreen::display(){

}

SubMenue::SubMenue(const char title[], int size){
  strcpy(this->title, title);
  this->enty_selected = 0;
  this->selected_entry_active = false;
  this->scroll_offset = 0;
  this->menueelement_count = 0;
  this->menueelement_max = size;
  this->menueelements = new MenueElement*[size];
}

void SubMenue::add_menueelement(MenueElement* menueelement){
  if (this->menueelement_count >= this->menueelement_max){
    return;
  }
  this->menueelements[this->menueelement_count] = menueelement;
  this->menueelement_count++;
}



void SubMenue::diplay_title(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  u8g2ref->setFontMode(1);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(0, 0, u8g2ref->getDisplayWidth(), 13);

  u8g2ref->setDrawColor(1);
  u8g2ref->drawHLine(0, 15, u8g2ref->getDisplayWidth());

  u8g2ref->setDrawColor(0);
  u8g2ref->setFont(u8g2_font_ncenB08_tr);
  u8g2ref->drawStr( 0, 12, this->title);
}

void SubMenue::display_scrollbar(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  u8g2ref->setDrawColor(1);
  u8g2ref->drawBox(u8g2ref->getDisplayWidth()-15, 25, 6, 26);
  u8g2ref->setFont(u8g2_font_unifont_t_symbols);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 25, 9652);
  u8g2ref->drawGlyph(u8g2ref->getDisplayWidth()-16, 60, 9662);
}

void SubMenue::display_entries(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
}

void SubMenue::display_as_entry(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int y){
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr( 10, y, this->title);
}

void SubMenue::display(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){

}

void SubMenue::setup_encoder(Input* input){
  input->change_rotary_min_max(0, this->menueelement_count-1);
  input->change_rotary_value(this->enty_selected);
}

bool SubMenue::handle_input(Input* input){
  if (this->selected_entry_active){
    if (this->menueelements[this->enty_selected]->handle_input(input) == false){
      this->selected_entry_active = false;
      this->setup_encoder(input);
    }
  }
  else{
    if (input->button_blue_pressed or input->button_rotary_pressed){
      this->selected_entry_active = true;
      this->menueelements[this->enty_selected]->setup_encoder(input);
    }
    else if (input->button_red_pressed){
      return false;
    }
    else {
      this->enty_selected = input->encoder_pos;
    }
  }
  return true;
}


MenueItem::MenueItem(const char title[], double value, char type, double max_value, double min_value){
  strcpy(this->title, title);
  this->value = value;
  this->type = type;
  this->max_value = max_value;
  this->min_value = min_value;
}

void MenueItem::display_as_entry(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int y){
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr( 10, y, this->title);
}

void MenueItem::display(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref){
  char buf[5];
  snprintf (buf, 5, "%f", this->value);
  u8g2ref->setDrawColor(1);
  u8g2ref->setFont(u8g2_font_profont12_mr);
  u8g2ref->drawStr( 10, 25, this->title);
  u8g2ref->drawStr( 10, 40, buf);
}

void MenueItem::setup_encoder(Input* input){
  input->change_rotary_min_max(this->min_value, this->max_value);
  input->change_rotary_value(this->value);
}

bool MenueItem::handle_input(Input* input){
  if (input->button_blue_pressed or input->button_red_pressed or input->button_rotary_pressed){
    return false;
  }
  else{
    this->value = input->encoder_pos;
  }
  return true;
}

void MenueElement::add_menueelement(MenueElement* menueelement){
  return;  // empty function so add menueelement can be called on menueitem and wont give an error
}




