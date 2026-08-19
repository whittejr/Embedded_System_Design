/**
* @file    main.c
* @brief   Protimer
* @version 0.1.0
* @a* @author  Alessandro Davi
* @date    2026-03-31
*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "qp.h"
#include "stm32wbxx_hal.h"
#include "bsp.h"
#include "qpc.h"
#include "ClockAlarm_SM.h"
#include "button.h"
#include "stm32wbxx_hal_gpio.h"
#include "board_config.h"

Q_DEFINE_THIS_FILE

void Error_Handler(void);

extern UART_HandleTypeDef uart1;
uint8_t rcv_data;
uint8_t rx_buffer[50];
uint8_t count = 0;
uint8_t event;
QEvt g_event;
uint8_t event_ready = 0;

/* 1. Create event queues (array of QEvt) for the AOs */
static QEvt ClockAlarmQueue[5];
static QEvt ButtonQueue[5];
// QActive const QF_active[] = {
//     { (QActive*)0, (QEvt*)0, 0 },
//     {}
// };
int main(void) {
    hw_init();

    Clock_Alarm_ctor();
    QASM_INIT(super_ClockAlarm, (void *)0, 0U);

    HAL_UART_Receive_IT(&uart1, &rcv_data, 1);

    uint32_t tick_time = HAL_GetTick();
    while(1) {
        
        if (event_ready) {
            event_ready = 0;
            QASM_DISPATCH(super_ClockAlarm, &g_event, 0U);
        }
        /* processamento TICK */
        if (HAL_GetTick() - tick_time >= 100) {
            tick_time += 100;
            QEvt e;
            e.sig = TICK_SIG;

            QASM_DISPATCH(super_ClockAlarm, &e, 0U);
        }
    }
    return 0;
}

void Error_Handler(void) {
    __disable_irq();
    while(1);
}

void Q_onError(char const *module, int loc) {
        __disable_irq(); 
            while (1) { }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (rcv_data == '\r') { // Se for ENTER pressionado
        event = rx_buffer[count-1];

        if (event == 's') { // EVENT SET
            g_event.sig = SET_SIG;
            event_ready = 1;
        } else if (event == 'o') { // EVENT OK
            g_event.sig = OK_SIG;
            event_ready = 1;
        } else if (event == 'a') { // EVENT ABORT
            g_event.sig = ABRT_SIG;
            event_ready = 1;
        }
        count = 0;
    } else { // Se for um dígito pressionado
        rx_buffer[count++] = rcv_data;
    }
   HAL_UART_Receive_IT(&uart1, &rcv_data, 1);
}
