
#include "main.h"

#include "hw_define.h"

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSE configuration and activation */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(64000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);
}

void MainLoopTimer_Config(uint32_t period_Hz)
{

  /* interrupt Init */
  NVIC_SetPriority(TIM_MAIN_LOOP_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(TIM_MAIN_LOOP_IRQn);

  /* Timer Init */
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  TIM_InitStruct.Prescaler = __LL_TIM_CALC_PSC(64000000, 100);
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = __LL_TIM_CALC_ARR(64000000, TIM_InitStruct.Prescaler, period_Hz);
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM_MAIN_LOOP, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM_MAIN_LOOP);

  /* Timer interrupt enable */
  LL_TIM_EnableIT_UPDATE(TIM_MAIN_LOOP);

  /* Timer Enable */
  LL_TIM_EnableCounter(TIM_MAIN_LOOP);

  /* Generate an update event to update the prescaler immediately */
  LL_TIM_GenerateEvent_UPDATE(TIM_MAIN_LOOP);
  
}