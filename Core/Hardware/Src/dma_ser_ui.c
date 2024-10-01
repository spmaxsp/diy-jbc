#include "dma_ser_ui.h"


uint8_t ser_ui_rx_buffer[DMA_SER_UI_RX_BUFFER_SIZE];

extern void Ser_Ui_Process_Command(uint8_t *command, uint8_t length);

// Public functions

void DMA_Ser_Ui__IRQHandler(void)
{
    LL_DMA_ClearFlag_TE1(   DMA_SER_UI );
    LL_DMA_ClearFlag_TC1(   DMA_SER_UI );
    Ser_Ui_Process_Command(ser_ui_rx_buffer, DMA_Ser_Ui__GetDataLength());
}

void DMA_Ser_Ui__Init(void)
{
    /* DMA Init */
	LL_DMA_SetDataTransferDirection(DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY );
	LL_DMA_SetChannelPriorityLevel( DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_PRIORITY_LOW );
	LL_DMA_SetMode(                 DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_MODE_NORMAL );
	LL_DMA_SetPeriphIncMode(        DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_PERIPH_NOINCREMENT );
	LL_DMA_SetMemoryIncMode(        DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_MEMORY_INCREMENT );
	LL_DMA_SetPeriphSize(           DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_PDATAALIGN_BYTE );
	LL_DMA_SetMemorySize(           DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, LL_DMA_MDATAALIGN_BYTE );
	LL_DMA_EnableIT_TE(             DMA_SER_UI, DMA_SER_UI_RX_CHANNEL );
    LL_DMA_EnableIT_TC(             DMA_SER_UI, DMA_SER_UI_RX_CHANNEL );

    /* DMA Request configuration */
    LL_DMA_SetPeriphRequest(        DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, DMA_SER_UI_RX_REQUEST);

    /* DMA Register and Memory address configuration */
	LL_DMA_ConfigAddresses(         DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, 
                                      LL_USART_DMA_GetRegAddr(UART_SER_UI, LL_USART_DMA_REG_DATA_RECEIVE), (uint32_t)ser_ui_rx_buffer, 
                                      LL_DMA_DIRECTION_PERIPH_TO_MEMORY); 
	LL_DMA_SetDataLength(           DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, DMA_SER_UI_RX_BUFFER_SIZE); 

    /* DMA interrupt priority and enable */
    NVIC_SetPriority(               DMA_SER_UI_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(                 DMA_SER_UI_IRQn);
}

void DMA_Ser_Ui__Enable(void)
{
    /* DMA Enable */
    LL_DMA_EnableChannel(   DMA_SER_UI, DMA_SER_UI_RX_CHANNEL );
}

void DMA_Ser_Ui__Reset(void)
{
    /* DMA Disable */
    LL_DMA_DisableChannel(  DMA_SER_UI, DMA_SER_UI_RX_CHANNEL );
    /* DMA Reset */
    LL_DMA_ClearFlag_TE1(   DMA_SER_UI );
    LL_DMA_ClearFlag_TC1(   DMA_SER_UI );
    LL_DMA_SetDataLength(   DMA_SER_UI, DMA_SER_UI_RX_CHANNEL, DMA_SER_UI_RX_BUFFER_SIZE );
    /* DMA Enable */
    LL_DMA_EnableChannel(   DMA_SER_UI, DMA_SER_UI_RX_CHANNEL );
}

uint32_t DMA_Ser_Ui__GetDataLength(void)
{
    return (DMA_SER_UI_RX_BUFFER_SIZE - LL_DMA_GetDataLength(DMA_SER_UI, DMA_SER_UI_RX_CHANNEL));
}