/**
  ******************************************************************************
  * @file    settings.h
  * @brief   This file contains the function prototypes for the settings.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "eeprom.h"

/* Exported types ------------------------------------------------------------*/

typedef struct settings_t 
{
    float KP;
    float KI;
    float KD;

    float TC_A;
    float TC_B;
    float TC_C;  

    int SLEEP_DELAY;
    int SLEEP_TEMP;
    int HIBERNATE_DELAY;
    int HIBERNATE_TEMP; 
} settings_t;

/* Exported functions --------------------------------------------------------*/

void Recover_from_EEPROM(void);
void Commit_to_EEPROM(void);

#ifdef __cplusplus
}
#endif

#endif /* __SETTINGS_H__ */