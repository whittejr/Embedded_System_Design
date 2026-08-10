/**
* @file    main.c
* @brief   Protimer
* @version 0.1.0
* @a* @author  Alessandro Davi
* @date    2026-03-31
*/

#include <stdint.h>
// #include "qp.h"
#include "stm32wbxx_hal.h"
#include "bsp.h"
// #include "qpc.h"

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
