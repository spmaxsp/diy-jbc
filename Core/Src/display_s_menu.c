
#include "display.h"   
#include "settings.h"

#include <stdio.h>

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

void Display_Render_Screen_Menu_Main(void);
void Display_Render_Screen_Menu_PID(void);
void Display_Render_Screen_Menu_Temp_Cal(void);
void Display_Render_Screen_Menu_Susp_Hibr(void);

extern enum { MAIN_SCREEN, MENU_SCREEN, PLOT_SCREEN } main_screen;
extern enum { MENU_MAIN, MENU_PID, MENU_TEMP_CAL, MENU_SUSP_HIBR } settings_screen;

extern settings_t settings;


void Display_Handle_Screen_Menu(void){

    // render menu
    switch(settings_screen){
        case MENU_MAIN:
            Display_Render_Screen_Menu_Main();
            break;
        case MENU_PID:
            Display_Render_Screen_Menu_PID();
            break;
        case MENU_TEMP_CAL:
            Display_Render_Screen_Menu_Temp_Cal();
            break;
        case MENU_SUSP_HIBR:
            Display_Render_Screen_Menu_Susp_Hibr();
            break;
    }
}

void Display_Render_Screen_Menu_Main(){

    // Handle Encoder
    Encoder_SetMinMax(0, 2);
    int selection = Encoder_GetCounter();

    // Handle Buttons
    if (GPIO_Button_Encoder__GetState())   { settings_screen = selection+1; }
    else if (GPIO_Button_Blue__GetState()) { settings_screen = selection+1; }
    else if (GPIO_Button_Red__GetState())  { main_screen = MAIN_SCREEN; }

    // Render
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
        //u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_4_PX_Y, "Other");
        //u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +110, DISPLAY_FORMAT_LINE_4_PX_Y, ">");

        // Selection
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X - 2, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +3, 120, 10);
    } while (u8g2_NextPage(&u8g2));
}

void Display_Render_Screen_Menu_PID(void){

    static int edit_selection = 0;

    // Handle Encoder
    Encoder_SetMinMax(0, 2);
    int selection = Encoder_GetCounter();

    if (GPIO_Button_Encoder__GetState())   { edit_selection = !edit_selection; }
    else if (GPIO_Button_Blue__GetState()) { }
    else if (GPIO_Button_Red__GetState())  { Encoder_SetCounter(settings_screen-1);
                                                settings_screen = MENU_MAIN; }
    
    // Render
    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);

        // Title
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_HEADER_PX_X, DISPLAY_FORMAT_HEADER_PX_Y, "PID");

        char str[6];
        sprintf(str, "%.3f", settings.KP);

        // Menu items
        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_1_PX_Y, "PID P");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_1_PX_Y, str);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_2_PX_Y, "PID I");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_2_PX_Y, str);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_3_PX_Y, "PID D");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_3_PX_Y, str);

        // Selection
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X - 2, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +3, 82, 10);
        if (edit_selection) {
            u8g2_DrawFrame(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +82, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +2, 35, 12);
        }
    } while (u8g2_NextPage(&u8g2));
}

void Display_Render_Screen_Menu_Temp_Cal(void){

    static int edit_selection = 0;
    static int  selection = 0;
    
    static float temp_TC_A = 0;
    static float temp_TC_B = 0;
    static float temp_TC_C = 0;

    // Handle Encoder

    if (!edit_selection) { 
        Encoder_SetMinMax(0, 2);
        selection = Encoder_GetCounter();

        if (GPIO_Button_Encoder__GetState())   { edit_selection = 1; 
                                                    Encoder_ResetAndGetDelta_Acel(); }
        else if (GPIO_Button_Blue__GetState()) { }
        else if (GPIO_Button_Red__GetState())  { Encoder_SetCounter(settings_screen-1);
                                                    settings_screen = MENU_MAIN; }

        temp_TC_A = settings.TC_A;
        temp_TC_B = settings.TC_B;
        temp_TC_C = settings.TC_C;
    } else {

        switch (selection){
            case 0:
                temp_TC_A += (Encoder_ResetAndGetDelta_Acel() * 0.001);
                if (temp_TC_A < 0) { temp_TC_A = 0; }
                if (temp_TC_A > 9) { temp_TC_A = 9; }
                break;
            case 1:
                temp_TC_B += (Encoder_ResetAndGetDelta_Acel() * 0.001);
                if (temp_TC_B < 0) { temp_TC_B = 0; }
                if (temp_TC_B > 9) { temp_TC_B = 9; }
                break;
            case 2:
                temp_TC_C += (Encoder_ResetAndGetDelta_Acel() * 0.001);
                if (temp_TC_C < 0) { temp_TC_C = 0; }
                if (temp_TC_C > 9) { temp_TC_C = 9; }
                break;
        }

        if (GPIO_Button_Encoder__GetState())   { edit_selection = 0; 
                                                    settings.TC_A = temp_TC_A;
                                                    settings.TC_B = temp_TC_B;
                                                    settings.TC_C = temp_TC_C; 
                                                    Encoder_SetCounter(selection); }
        else if (GPIO_Button_Blue__GetState()) { }
        else if (GPIO_Button_Red__GetState())  { edit_selection = 0; 
                                                    Encoder_SetCounter(selection); }
    }

    
    // Render    
    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);

        // Title
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_HEADER_PX_X, DISPLAY_FORMAT_HEADER_PX_Y, "Temp. Cal.");

        // Menu items
        char str_TC_A[6];
        sprintf(str_TC_A, "%.3f", temp_TC_A);
        char str_TC_B[6];
        sprintf(str_TC_B, "%.3f", temp_TC_B);
        char str_TC_C[6];
        sprintf(str_TC_C, "%.3f", temp_TC_C);

        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_1_PX_Y, "Cal. A");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_1_PX_Y, str_TC_A);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_2_PX_Y, "Cal. B");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_2_PX_Y, str_TC_B);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_3_PX_Y, "Cal. C");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_3_PX_Y, str_TC_C);
        
        // Selection
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X - 2, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +3, 82, 10);
        if (edit_selection) {
            u8g2_DrawFrame(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +82, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +2, 35, 12);
        }    
    } while (u8g2_NextPage(&u8g2));
}

void Display_Render_Screen_Menu_Susp_Hibr(){

    static int edit_selection = 0;

    // Handle Encoder
    Encoder_SetMinMax(0, 3);
    int selection = Encoder_GetCounter();

    if (GPIO_Button_Encoder__GetState())   { edit_selection = !edit_selection; }
    else if (GPIO_Button_Blue__GetState()) { }
    else if (GPIO_Button_Red__GetState())  { Encoder_SetCounter(settings_screen-1);
                                                settings_screen = MENU_MAIN; }
    
    // Render        
    u8g2_FirstPage(&u8g2);
    do
    {
        u8g2_SetBitmapMode(&u8g2, 1);
        u8g2_SetFontMode(&u8g2, 1);

        // Title
        u8g2_SetFont(&u8g2, u8g2_font_profont22_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_HEADER_PX_X, DISPLAY_FORMAT_HEADER_PX_Y, "Susp./Hib.");

        // Menu items
        u8g2_SetFont(&u8g2, u8g2_font_profont11_tr);
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_1_PX_Y, "Time Susp.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_1_PX_Y, "20s");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_2_PX_Y, "Temp. Susp.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_2_PX_Y, "150°C");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_3_PX_Y, "Time Hib.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_3_PX_Y, "10s");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X     , DISPLAY_FORMAT_LINE_4_PX_Y, "Temp Hib.");
        u8g2_DrawStr(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +86 , DISPLAY_FORMAT_LINE_4_PX_Y, "100°C");
        
        // Selection
        u8g2_SetDrawColor(&u8g2, 2);
        u8g2_DrawBox(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X - 2, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +3, 82, 10);
        if (edit_selection) {
            u8g2_DrawFrame(&u8g2, DISPLAY_FORMAT_FIRST_LINE_PX_X +82, DISPLAY_FORMAT_FIRST_LINE_PX_Y + (selection-1)*DISPLAY_FORMAT_LINE_HEIGHT_PX +2, 35, 12);
        }
    } while (u8g2_NextPage(&u8g2));
}