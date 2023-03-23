#ifndef MENUE_H_
#define MENUE_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "../../screenmanager.h"
#include "../../input.h"
#include "../../screen.h"

class MenueElement {
  public:
    void virtual display(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref)=0;
    bool virtual handle_input(Input* input)=0;
    void virtual display_as_entry(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int y)=0;
    void virtual add_menueelement(MenueElement* menueelement);
    void virtual setup_encoder(Input* input)=0;
};

class MenueItem: public MenueElement {
  private:
    char title[20];
    double value;
    char type;
    double max_value;
    double min_value;
    void setup_encoder(Input* input);
  public:
    MenueItem(const char title[], double value, char type, double max_value, double min_value);
    void display_as_entry(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int y);
    void display(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    bool handle_input(Input* input);
};

class SubMenue: public MenueElement {
  private:
    char title[20];
    int enty_selected;
    bool selected_entry_active;
    int scroll_offset;
    int menueelement_count;
    int menueelement_max;
    MenueElement** menueelements;
    void diplay_title(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void display_scrollbar(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void display_entries(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void setup_encoder(Input* input);
  public:
    SubMenue(const char title[], int size);
    void add_menueelement(MenueElement* menueelement);
    void display_as_entry(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref, int y);
    void display(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    bool handle_input(Input* input);
};

class MenueScreen: public Screen {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
    MenueElement* menue_structure;
  public:
    MenueScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void display();
    bool handle_input(Input* input);
};

#endif