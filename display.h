#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <Arduino.h>

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
  public:
    Menue();
};

#endif
