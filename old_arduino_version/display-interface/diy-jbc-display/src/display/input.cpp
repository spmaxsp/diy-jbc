#include "input.h"

Input::Input(int button_red, int button_blue, int rotary_sw, int rotary_clk, int rotary_dt) {
    this->button_red = button_red;
    this->button_blue = button_blue;
    this->rotary_sw = rotary_sw;
    this->rotary_clk = rotary_clk;
    this->rotary_dt = rotary_dt;

    pinMode(button_red, INPUT_PULLUP);
    pinMode(button_blue, INPUT_PULLUP);

    pinMode(rotary_sw, INPUT_PULLUP);
    pinMode(rotary_clk, INPUT);
    pinMode(rotary_dt, INPUT);

    attachInterrupt(digitalPinToInterrupt(rotary_clk), Interrupt, RISING);
    this_instance = this;
}

void Input::update() {
    if (millis() - last_button_red >= BUTTON_DEBOUNCE) {
        this->button_red_pressed = !digitalRead(this->button_red);
        last_button_red = millis();
    }
    else {
        this->button_red_pressed = false;
    }

    if (millis() - last_button_blue >= BUTTON_DEBOUNCE) {
        this->button_blue_pressed = !digitalRead(this->button_blue);
        last_button_blue = millis();
    }
    else {
        this->button_blue_pressed = false;
    }

    if (millis() - last_rotary_sw >= BUTTON_DEBOUNCE) {
        this->button_rotary_pressed = !digitalRead(this->rotary_sw);
        last_rotary_sw = millis();
    }
    else {
        this->button_rotary_pressed = false;
    }
}

void Input::Interrupt() {
    this_instance->rotaryInterrupt();
}

void Input::rotaryInterrupt(){
  if (millis() - last_rotary_clk >= ROT_DEBOUNCE) {
    if (digitalRead(rotary_dt)){
      if (encoder_pos < rotary_max){
        encoder_pos++;
      }
    }
    else{
      if (encoder_pos > rotary_min){
        encoder_pos--;
      }
    }
    last_rotary_clk = millis();
  }
}

void Input::change_rotary_value(int value) {
    this->encoder_pos = value;
}

void Input::change_rotary_min_max(int min, int max) {
    this->rotary_min = min;
    this->rotary_max = max;
}

Input* Input::this_instance;