#ifndef LED_H_
#define LED_H_
#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 5

#define NUM_LEDS 1

#define MAX_TEMP 450
#define MIN_TEMP 30

class StatusLed{ 
  private: 
    CRGBPalette16 heatPal;
    CRGB leds[NUM_LEDS];
    
  public:  
    StatusLed();
    void begin();
    void update(double temp);
};

#endif
