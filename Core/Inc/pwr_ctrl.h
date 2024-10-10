/**
  ******************************************************************************
  * @file    pwr_ctl.h
  * @brief   This file contains the function prototypes for the pwr_ctl.c
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWR_CTL_H__
#define __PWR_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

// Hardware
#include "gpio_pwr.h"

/* Exported types ------------------------------------------------------------*/

void Request_Heating(int power);
uint8_t Get_Heating(void);

#ifdef __cplusplus
}
#endif

#endif /* __PWR_CTL_H__ */