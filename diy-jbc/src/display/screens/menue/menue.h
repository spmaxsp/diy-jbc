#ifndef MENUE_H_
#define MENUE_H_
#include <Arduino.h>
#include <U8g2lib.h>

#include "../../screenmanager.h"

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
} mainmenue;

class MenueScreen: public Screen {
  private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref;
    void display_menue(mainmenue* menue);
    void display_submenue(submenue* menue);
    void display_menueitem(menueitem* item);
    void setup_encoder(Input* input);
    mainmenue menue_structure;
  public:
    MenueScreen(U8G2_SH1106_128X64_NONAME_1_HW_I2C* u8g2ref);
    void display();
    bool handle_input(Input* input);
};

#endif