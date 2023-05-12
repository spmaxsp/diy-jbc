#include <Arduino.h>
#include "src/display/display.h"
#include "src/i2c-interface-main/i2c-interface.h"

#define ENCODER_CLK 2 // INT0
#define ENCODER_DT  10
#define ENCODER_BUTTON 9

#define BUTTON_RED A1
#define BUTTON_BLUE A2

I2CInterface i2c_interface;
Display display(BUTTON_RED, BUTTON_BLUE, ENCODER_BUTTON, ENCODER_CLK, ENCODER_DT);

void setup() {
    display.begin();
}

void loop() {
    display.update();
}