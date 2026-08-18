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

uint8_t alarm_counter;

button_t btn_set;
button_t btn_ok;
bool flag_exti_set = false;
bool flag_exti_ok = false;

int main(void) {
    hw_init();

    Clock_Alarm_ctor();
    QASM_INIT(super_ClockAlarm, (void *)0, 0U);

    button_init(&btn_set);
    button_init(&btn_ok);

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

        alarm_counter++;
        if (alarm_counter >= 5) {
            alarm_counter = 0;

            QEvt e_alarm;
            e_alarm.sig = ALARM_SIG;
            QASM_DISPATCH(super_ClockAlarm, &e_alarm, 0U);
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
        case BTN_SET_PIN: {
            flag_exti_set = true;
            break;
        }

        case BTN_OK_PIN: {
            flag_exti_ok = true;
            break;
        }
    }
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


// bool state_set = (HAL_GPIO_ReadPin(BTN_SET_PORT, BTN_SET_PIN) == GPIO_PIN_RESET);
        // bool state_ok  = (HAL_GPIO_ReadPin(BTN_OK_PORT, BTN_OK_PIN) == GPIO_PIN_RESET);

        // /* processamento btn SET */
        // button_event_t evt_set = button_process_interrupt_driven(&btn_set, state_set, &flag_exti_set);
        // if (evt_set != BUTTON_EVENT_NONE) {
                
        //     if (evt_set == BUTTON_EVENT_SHORT_CLICK) {
        //         QEvt e;
        //         e.sig = SET_SIG; // Substitua pelo sinal correto na sua UML
        //         QASM_DISPATCH(super_ClockAlarm, &e, 0U);
        //     }
        //     // (Você também pode tratar BUTTON_EVENT_LONG_CLICK aqui se quiser)
        // }

        // /* processamento btn OK */
        // button_event_t evt_ok = button_process_interrupt_driven(&btn_ok, state_ok, &flag_exti_ok);
        // if (evt_ok != BUTTON_EVENT_NONE) {
            
        //     if (evt_ok == BUTTON_EVENT_SHORT_CLICK) {
        //         QEvt e;
        //         e.sig = OK_SIG; // Substitua pelo sinal correto na sua UML
        //         QASM_DISPATCH(super_ClockAlarm, &e, 0U);
        //     }
        // }