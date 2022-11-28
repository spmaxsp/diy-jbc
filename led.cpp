#include <Arduino.h>
#include "led.h"

DEFINE_GRADIENT_PALETTE(heatmap) {
    0,     0,  0,  0,
  128,   255,  0,  0,
  224,   255,255,  0,
  255,   255,255,255 
  };

StatusLed::StatusLed():heatPal(heatmap){
}

void StatusLed::begin() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(this->leds, NUM_LEDS);
}

void StatusLed::update(double temp) {
  int heatindex = map(temp, MIN_TEMP, MAX_TEMP, 0, 255);
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = ColorFromPalette(heatPal, heatindex);   
  }
  FastLED.show();
}
