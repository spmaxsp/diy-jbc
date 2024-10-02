
#include "display.h"   

extern u8g2_t u8g2;

#define DISPLAY_FORMAT_HEADER_PX_X  6
#define DISPLAY_FORMAT_HEADER_PX_Y  16

#define DISPLAY_FORMAT_FIRST_LINE_PX_X  6
#define DISPLAY_FORMAT_FIRST_LINE_PX_Y  27
#define DISPLAY_FORMAT_LINE_HEIGHT_PX   11

#define DISPLAY_FORMAT_LINE_1_PX_Y    DISPLAY_FORMAT_FIRST_LINE_PX_Y + DISPLAY_FORMAT_LINE_HEIGHT_PX*0
#define DISPLAY_FORMAT_LINE_2_PX_Y    DISPLAY_FORMAT_FIRST_LINE_PX_Y + DISPLAY_FORMAT_LINE_HEIGHT_PX*1
#define DISPLAY_FORMAT_LINE_3_PX_Y    DISPLAY_FORMAT_FIRST_LINE_PX_Y + DISPLAY_FORMAT_LINE_HEIGHT_PX*2
#define DISPLAY_FORMAT_LINE_4_PX_Y    DISPLAY_FORMAT_FIRST_LINE_PX_Y + DISPLAY_FORMAT_LINE_HEIGHT_PX*3


void Display_Render_Screen_Menu(void){
    static enum {MENU_MAIN, PID_MENU, MENU_SUB2} menu = MENU_MAIN;

    // setup encoder

    
    // handle input


    // render menu
    switch(menu){
        case MENU_MAIN:
            Display_Render_Screen_Menu_Main();
            break;
        case PID_MENU:
            Display_Render_Screen_Menu_PID();
            break;
        case MENU_SUB2:
            //display_sub2_menu();
            break;
    }
}

void Display_Render_Screen_Menu_Main(void){
    int selection = 2;
    
    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);

        // Title
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_HEADER_PX_X, DISPLAY_FORMAT_HEADER_PX_Y, "Menu:");

        // Menu items
        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_1_PX_Y, "PID Settings");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +110, DISPLAY_FORMAT_LINE_1_PX_Y, ">");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_2_PX_Y, "Temperature Cal.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +110, DISPLAY_FORMAT_LINE_2_PX_Y, ">");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_3_PX_Y, "Suspend/Hibernatn.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +110, DISPLAY_FORMAT_LINE_3_PX_Y, ">");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_4_PX_Y, "Other");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +110, DISPLAY_FORMAT_LINE_4_PX_Y, ">");

        // Selection
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X - 2, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +3, 120, 10);
    } while (u8g2_NextPage(&u8g2));
}

void Display_Render_Screen_Menu_PID(void){
    
    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);
        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, 6, 27, "Time Susp.");
        u8g2_DrawStr(&u8g2, 6, 38, "Temp. Susp.");
        u8g2_DrawStr(&u8g2, 6, 49, "Time Hib.");
        u8g2_DrawStr(&u8g2, 6, 60, "Temp Hib.");
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, 6, 16, "Susp./Hib.");
        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, 103, 27, "20s");
        u8g2_DrawStr(&u8g2, 91, 39, "150°C");
        u8g2_DrawStr(&u8g2, 103, 49, "10s");
        u8g2_DrawStr(&u8g2, 91, 60, "100°C");
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, 4, 30, 84, 10);
        u8g2_DrawFrame(&u8g2, 89, 29, 35, 12);
    } while (u8g2_NextPage(&u8g2));
}