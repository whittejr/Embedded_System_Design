/**
* @file    it.c
* @brief   none
* @version 0.1.0
* @author  Your name here
* @date    2026-04-01
*/

#include "it.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_uart.h"
#include "uart.h"

extern UART_HandleTypeDef uart1;

void SysTick_Handler(void) {
    HAL_IncTick();
}

void USART1_IRQHandler(void) {
    HAL_UART_IRQHandler(&uart1);
}

