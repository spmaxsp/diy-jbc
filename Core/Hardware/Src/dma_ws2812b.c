
#include "dma_ws2812b.h"

uint32_t ws2812b_dma_buffer[WS2812B_LED_COUNT * 24 + 1] = {0};
int dma_running = 0;

extern void TIM_WS2812B__Enable(void);
extern void TIM_WS2812B__Zerro(void);

void DMA_WS2812B__IRQHandler(void)
{
    LL_DMA_ClearFlag_TE2(DMA_WS2812B);
    LL_DMA_ClearFlag_TC2(DMA_WS2812B);
    LL_DMA_DisableChannel(  DMA_WS2812B, DMA_WS2812B_CHANNEL );

    LL_TIM_DisableCounter(TIM_WS2812B);
    dma_running = 0;
}

void DMA_WS2812B__Init(void)
{
    /* DMA Init */
	LL_DMA_SetDataTransferDirection(DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH );
	LL_DMA_SetChannelPriorityLevel( DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_PRIORITY_LOW );
	LL_DMA_SetMode(                 DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_MODE_NORMAL );
	LL_DMA_SetPeriphIncMode(        DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_PERIPH_NOINCREMENT );
	LL_DMA_SetMemoryIncMode(        DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_MEMORY_INCREMENT );
	LL_DMA_SetPeriphSize(           DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_PDATAALIGN_WORD );
	LL_DMA_SetMemorySize(           DMA_WS2812B, DMA_WS2812B_CHANNEL, LL_DMA_MDATAALIGN_WORD );
	LL_DMA_EnableIT_TE(             DMA_WS2812B, DMA_WS2812B_CHANNEL );
    LL_DMA_EnableIT_TC(             DMA_WS2812B, DMA_WS2812B_CHANNEL );
    LL_DMA_DisableIT_HT(            DMA_WS2812B, DMA_WS2812B_CHANNEL );

    /* DMA Request configuration */
    LL_DMA_SetPeriphRequest(        DMA_WS2812B, DMA_WS2812B_CHANNEL, DMA_WS2812B_REQUEST);

    /* DMA Register and Memory address configuration */
	LL_DMA_ConfigAddresses(         DMA_WS2812B, DMA_WS2812B_CHANNEL, 
                                        (uint32_t)ws2812b_dma_buffer, (uint32_t)&TIM3->CCR1, 
                                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH); 
	LL_DMA_SetDataLength(           DMA_WS2812B, DMA_WS2812B_CHANNEL, WS2812B_LED_COUNT * 24 + 1); 

    /* DMA interrupt priority and enable */
    NVIC_SetPriority(               DMA_WS2812B_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(                 DMA_WS2812B_IRQn);

    /* DMA Disable */
    LL_DMA_DisableChannel(  DMA_WS2812B, DMA_WS2812B_CHANNEL );
}

void DMA_WS2812B__ReEnable(void)
{
    if (dma_running)
    {
        return;
    }

    /* DMA Disable */
    LL_DMA_DisableChannel(  DMA_WS2812B, DMA_WS2812B_CHANNEL );
    /* DMA Reset */
    LL_DMA_ClearFlag_TE2(   DMA_WS2812B );
    LL_DMA_ClearFlag_TC2(   DMA_WS2812B );
    LL_DMA_SetDataLength(   DMA_WS2812B, DMA_WS2812B_CHANNEL, WS2812B_LED_COUNT * 24 + 1 );
    /* DMA Enable */
    LL_DMA_EnableChannel(   DMA_WS2812B, DMA_WS2812B_CHANNEL );

    LL_TIM_EnableCounter(TIM_WS2812B);
    dma_running = 1;
}