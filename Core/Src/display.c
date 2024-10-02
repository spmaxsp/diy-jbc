#include "display.h"

#include <stdio.h>

// Private variables
u8g2_t u8g2;

// Public functions
void Display_Init(void)
{
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);      // send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0);  // wake up display
}


void Display_Render_Main(void)
{
    static enum { MAIN_SCREEN, MENU_SCREEN, PLOT_SCREEN } screen = PLOT_SCREEN;

    // setup encoder


    // handle input
    if (Button_Blue_GetState()){
        screen = MENU_SCREEN;
    }
    else if (Button_Red_GetState()){
        screen = MAIN_SCREEN;
    }
    else if (Button_Encoder_GetState()){
        screen = PLOT_SCREEN;
    }


    // render screens
    switch (screen)
    {
    case MAIN_SCREEN:
        Display_Render_Screen_Main();
        break;
    case MENU_SCREEN:
        Display_Render_Screen_Menu();
        break;
    case PLOT_SCREEN:
        Display_Render_Screen_Plot();
        break;
    }
}