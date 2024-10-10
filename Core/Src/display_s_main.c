
#include "display.h"

extern u8g2_t u8g2;

extern enum { MAIN_SCREEN, MENU_SCREEN, PLOT_SCREEN } main_screen;

void Display_Render_Screen_Main(void){

    if (GPIO_Button_Encoder__GetState())   { main_screen = MENU_SCREEN;
                                                Encoder_SetCounter(0); }
    else if (GPIO_Button_Blue__GetState()) { main_screen = PLOT_SCREEN; }
    else if (GPIO_Button_Red__GetState())  { } // TODO: Set Temperature to 0

    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);

        // Is and Set Temperature
        u8g2_SetFont(&u8g2, u8g2_font_profont12_tr);
        u8g2_DrawStr(&u8g2, 3, 53, "Is:");
        u8g2_DrawStr(&u8g2, 2, 29, "Set:");
        u8g2_SetFont(&u8g2, u8g2_font_profont29_tr);
        u8g2_DrawStr(&u8g2, 28, 29, "400°C");
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, 28, 53, "400°C");

        // Hibernation Supend Time
        u8g2_DrawFrame(&u8g2, 92, 37, 17, 10);
        u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
        u8g2_DrawStr(&u8g2, 93, 45, "10s");
        
        // PWR Meter
        u8g2_DrawFrame(&u8g2, 112, 9, 13, 46);
        u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
        u8g2_DrawStr(&u8g2, 111, 8, "100");
        u8g2_DrawStr(&u8g2, 112, 62, "OFF");
        u8g2_DrawBox(&u8g2, 113, 26, 11, 28);

    } while (u8g2_NextPage(&u8g2));
}




// 

// u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
// u8g2_DrawStr(&u8g2, 28, 53, "Hibernation");


// u8g2_SendBuffer(&u8g2); 