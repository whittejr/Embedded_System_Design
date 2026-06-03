/**
* @file    main.c
* @brief   Protimer
* @version 0.1.0
* @a* @author  Alessandro Davi
* @date    2026-03-31
*/

#include <stdint.h>
#include "qp.h"
#include "stm32wbxx_hal.h"
#include "bsp.h"
#include "qpc.h"
#include "QHSM_Test.h"

//  Peripherals
extern UART_HandleTypeDef uart1;
// extern TIM_HandleTypeDef tim16;

// Error handler
void Error_Handler(void);

// Application global variables

int main(void) {
    // Peripheral init
    hw_init();  
    
    while(1)
    {
    
    }
    return 0;
}

// Error handler
void Error_Handler(void) {
    __disable_irq();
    while(1);
}


// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    
//     if (data == 'w')
//         ue.super.sig = INC_TIME;
//     else if (data == 's')
//         ue.super.sig = DEC_TIME;
//     else if (data == 'c')
//         ue.super.sig = ABRT;
//     else if (data == 'p')
//         ue.super.sig = START_PAUSE;
//     else {
//         HAL_UART_Receive_IT(&uart1, (uint8_t*) &data, 1);
//         return;
//     }
       
//     HAL_UART_Receive_IT(&uart1, (uint8_t*) &data, 1);
//     dispatcher_flag = 1; 
// }

/*
    letra = interrupçao
    switch case Letra
        p - START_PAUSE
        w - INC
        s - DEC
        c - ABRT
*/
