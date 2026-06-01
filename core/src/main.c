/**
* @file    main.c
* @brief   Mealey Machine
* @version 0.1.0
* @a* @author  Alessandro Davi
* @date    2026-03-31
*/

#include <stdint.h>
#include "protimer/protimer.h"
#include "stm32wbxx_hal.h"
#include "clock.h"
#include "tim.h"
#include "gpio.h"
#include "uart.h"
// #include "fsm.h"
#include "protimer.h"

//  Peripherals
extern UART_HandleTypeDef uart1;
// extern TIM_HandleTypeDef tim16;
void hw_init(void);

// Error handler
void Error_Handler(void);

// Application global variables
protimer_t protimer;


int main(void) {
    // Peripheral init
    hw_init();

    // application code
    protimer_init(&protimer);

    return 0;
}

void fsm_init(void) {
    
}


// Error handler
void Error_Handler(void) {
    __disable_irq();
    while(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    // if (rcv_data == '\r') {
    //     if (count < 0) return;

    //     event = rx_buffer[count-1];
    //     if (event == 'o')
    //         mealey_light_state_machine(&curr_state, ON); 
    //     else if (event == 'x')
    //         mealey_light_state_machine(&curr_state, OFF);
    //     count = 0;        
    // } else {
    //     rx_buffer[count++] = rcv_data;
    // }
    
   HAL_UART_Receive_IT(&uart1, &rcv_data, 1);
}

void hw_init(void) {
    HAL_Init();
    clock_config();
    // tim16_init();
    gpio_init();
    uart_init();

}


