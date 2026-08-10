// /**
// * @file    main.c
// * @brief   Protimer
// * @version 0.1.0
// * @a* @author  Alessandro Davi
// * @date    2026-03-31
// */

// #include <stdint.h>
// #include "protimer_state_handler.h"
// #include "stm32wbxx_hal.h"
// #include "clock.h"
// #include "gpio.h"
// #include "uart.h"

// //  Peripherals
// extern UART_HandleTypeDef uart1;
// // extern TIM_HandleTypeDef tim16;
// void hw_init(void);

// // Error handler
// void Error_Handler(void);
// /* static functions*/
// static void timer_tick(void);

// // Application global variables
// uint32_t current_time = 0;
// protimer_t protimer;
// protimer_user_event_t ue;
// protimer_tick_event_t te; // tick event
// uint8_t dispatcher_flag = 0; // flag from UART callback
// char data; // UART RX data

// int main(void) {
//     // Peripheral init
//     hw_init();  
//     timer_tick();

//     // application code
//     protimer_init(&protimer);
//     current_time = HAL_GetTick(); // temporary (use timer instead)
    
//     while(1) {
//         timer_tick();
//    }
//     return 0;
// }

// // Error handler
// void Error_Handler(void) {
//     __disable_irq();
//     while(1);
// }


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

// void hw_init(void) {
//     HAL_Init();
//     clock_config();
//     // tim16_init();
//     gpio_init();
//     uart_init();

//     HAL_UART_Receive_IT(&uart1, (uint8_t*) &data, 1);
// }

// static void timer_tick(void) {
//     if (dispatcher_flag) {
//         protimer_event_dispatcher(&protimer, &ue.super);
//         dispatcher_flag = 0;
//     }

//     if ((HAL_GetTick() - current_time) >= 100) { // if 100ms has passed
//         current_time = HAL_GetTick();
//         te.super.sig = TIME_TICK;

//         if (++te.ss > 10) {
//             te.ss = 1;
//         }
//         protimer_event_dispatcher(&protimer, &te.super);
//     }
// }


// /*
//     letra = interrupçao
//     switch case Letra
//         p - START_PAUSE
//         w - INC
//         s - DEC
//         c - ABRT
// */
