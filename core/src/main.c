/**
* @file    main.c
* @brief   Mealey Machine
* @version 0.1.0
* @a* @author  Alessandro Davi
* @date    2026-03-31
*/

#include <stdint.h>
#include "stm32wbxx_hal.h"
#include "clock.h"
#include "tim.h"
#include "gpio.h"
#include "uart.h"
#include "fsm.h"
#include "mealey_fsm.h"
#include "moore_fsm.h"


//  Peripherals
extern UART_HandleTypeDef uart1;
extern TIM_HandleTypeDef tim16;
void hw_init(void);

// Error handler
void Error_Handler(void);

// Application variables    
uint8_t event;
uint8_t rcv_data;
uint8_t rx_buffer[50];
uint8_t count = 0;
uint8_t message[100] = "Light Control Application\r\n-------------------------\r\nSend 'x' or 'o'\r\n";
light_state_t curr_state;

int main(void) {
    // Peripheral init
    hw_init();

    // application code

    return 0;
}

void fsm_init(void) {
    curr_state = LIGHT_OFF;
    moore_run_entry_action(LIGHT_OFF);
}


// Error handler
void Error_Handler(void) {
    __disable_irq();
    while(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (rcv_data == '\r') {
        if (count < 0) return;

        event = rx_buffer[count-1];
        if (event == 'o')
            mealey_light_state_machine(&curr_state, ON); 
        else if (event == 'x')
            mealey_light_state_machine(&curr_state, OFF);
        count = 0;        
    } else {
        rx_buffer[count++] = rcv_data;
    }
    
   HAL_UART_Receive_IT(&uart1, &rcv_data, 1);
}

void hw_init(void) {
    HAL_Init();
    clock_config();
    tim16_init();
    gpio_init();
    uart_init();
    if (HAL_TIM_PWM_Start(&tim16, TIM_CHANNEL_1) != 0) Error_Handler();
    HAL_UART_Receive_IT(&uart1, &rcv_data, 1);
    HAL_UART_Transmit(&uart1, message, 100, HAL_MAX_DELAY);
}


