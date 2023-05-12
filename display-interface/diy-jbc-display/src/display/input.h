#ifndef INPUT_H_
#define INPUT_H_
#include <Arduino.h>

class Input {
private:
    int button_red;
    int button_blue;

    int rotary_sw;
    int rotary_clk;
    int rotary_dt;

    int rotary_min;
    int rotary_max;

    unsigned long last_rotary_clk = 0;
    unsigned long last_rotary_sw = 0;
    unsigned long last_button_red = 0;
    unsigned long last_button_blue = 0;

    const unsigned int ROT_DEBOUNCE = 50;
    const unsigned int BUTTON_DEBOUNCE = 500;

    static Input* this_instance;  // stores a reference to the instance the interrupt is bound to

    static void Interrupt();      // a static function which can be called by attachInterrupt, which then calls rotaryInterrupt
    void rotaryInterrupt(); 

public:
    bool button_red_pressed;
    bool button_blue_pressed;
    bool button_rotary_pressed;

    int encoder_pos = 0;

    Input(int button_red, int button_blue, int rotary_sw, int rotary_clk, int rotary_dt);
    void update();
    void change_rotary_value(int value);
    void change_rotary_min_max(int min, int max);
};

#endif // INPUT_H_
