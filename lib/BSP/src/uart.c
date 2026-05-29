/**
* @file    uart.c
* @brief   none
* @version 0.1.0
*/

#include "uart.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_uart.h"

UART_HandleTypeDef uart1;

uint8_t uart_init(void) {
    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;

    // Enabling USART1 IRQ and set up the priority (NVIC)
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);

    if (HAL_UART_Init(&uart1) != 0) return 1;
    
    return 0;
}

// uint8_t uart_receive(uint8_t *data, uint16_t size) {
//     if (HAL_UART_Receive(&uart1, data, size, HAL_MAX_DELAY) != 0) {
//         return 1;
//     }
//     return 0;
// }


void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart) {

}

void HAL_UARTEx_TxFifoEmptyCallback(UART_HandleTypeDef *huart) {

}

void HAL_UARTEx_RxFifoFullCallback(UART_HandleTypeDef *huart) {

}
