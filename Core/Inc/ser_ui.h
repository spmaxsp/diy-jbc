/**
  ******************************************************************************
  * @file    ser_ui.h
  * @brief   This file contains the function prototypes for the ser_ui.c, ser_ui_dma.c, and ser_ui_usart.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SER_UI_H__
#define __SER_UI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "usart_ser_ui.h"
#include "dma_ser_ui.h"

/* Exported types ------------------------------------------------------------*/

void Ser_Ui_Print(char *str);
void Ser_Ui_PrintLn(char *str);

#ifdef __cplusplus
}
#endif

#endif /* __SER_UI_H__ */