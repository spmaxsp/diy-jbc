/**
  ******************************************************************************
  * @file    eeprom.h
  * @brief   This file contains the function prototypes for the eeprom.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H__
#define __EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "i2c.h"

/* Exported types ------------------------------------------------------------*/

void EEPROM_Write(uint16_t address, uint8_t length, uint8_t *data);
void EEPROM_Read(uint16_t address, uint8_t length, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H__ */