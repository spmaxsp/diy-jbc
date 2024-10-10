#include "display.h"

#include <stdio.h>

// Private variables
u8g2_t u8g2;

// Public functions
void Display_Init(void)
{
    //u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);
    u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);      // send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0);  // wake up display

    u8g2_ClearBuffer(&u8g2);
    u8g2_SendBuffer(&u8g2);
}

enum { MAIN_SCREEN, MENU_SCREEN, PLOT_SCREEN } main_screen;
enum { MENU_MAIN, MENU_PID, MENU_TEMP_CAL, MENU_SUSP_HIBR } settings_screen;

void Display_Render_Main(void)
{
    // render screens
    switch (main_screen)
    {
    case MAIN_SCREEN:
        Display_Render_Screen_Main();
        break;
    case MENU_SCREEN:
        Display_Handle_Screen_Menu();
        break;
    case PLOT_SCREEN:
        Display_Render_Screen_Plot();
        break;
    }
}