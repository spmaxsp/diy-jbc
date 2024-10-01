#include "usart_ser_ui.h"

// Public functions

void UART_Ser_Ui__IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_CM(UART_SER_UI))
    {
        LL_USART_ClearFlag_CM(UART_SER_UI);
    }
}

void USART_Ser_Ui__Init(void)
{
    /* GPIO Configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_SER_UI_RX;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init( PIN_SER_UI_RX_TX_PORT, &GPIO_InitStruct );

    GPIO_InitStruct.Pin = PIN_SER_UI_TX;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init( PIN_SER_UI_RX_TX_PORT, &GPIO_InitStruct );
    
    /* USART RX Interrupt Configuration */
    LL_USART_EnableIT_CM(       UART_SER_UI );      // Enable Character Match Interrupt for "\n"    
    LL_USART_ConfigNodeAddress( UART_SER_UI, LL_USART_ADDRESS_DETECT_7B, '\n' );

    /* USART Initialization */
    LL_USART_InitTypeDef USART_InitStruct = {0};
    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = UART_SER_UI_BAUDRATE;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init( UART_SER_UI, &USART_InitStruct );

    /* USART Disable FIFO mode */
    LL_USART_SetTXFIFOThreshold( UART_SER_UI, LL_USART_FIFOTHRESHOLD_1_8 );
    LL_USART_SetRXFIFOThreshold( UART_SER_UI, LL_USART_FIFOTHRESHOLD_1_8 );
    LL_USART_DisableFIFO(        UART_SER_UI );

    /* USART Async Mode */
    LL_USART_ConfigAsyncMode(UART_SER_UI);

    /* USART DMA Enable */
    LL_USART_EnableDMAReq_RX(UART_SER_UI);

    /* USART Enable */
    LL_USART_Enable(UART_SER_UI);

    /* Polling USART initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(UART_SER_UI))) || (!(LL_USART_IsActiveFlag_REACK(UART_SER_UI))))
    {
    }


    /* USART interrupt priority and enable */
    NVIC_SetPriority(UART_SER_UI_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(UART_SER_UI_IRQn);
}

void USART_Ser_Ui__Tx_Blocking(uint8_t *data, uint16_t size)
{
    uint16_t i = 0;
    for (i = 0; i < size; i++)
    {
        while (!LL_USART_IsActiveFlag_TXE(UART_SER_UI));
        LL_USART_TransmitData8(UART_SER_UI, data[i]);
    }
    while (!LL_USART_IsActiveFlag_TC(UART_SER_UI));
}