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

    uint32_t tick_time = HAL_GetTick();
    while(1) {
        bool state_set = (HAL_GPIO_ReadPin(BTN_SET_PORT, BTN_SET_PIN) == GPIO_PIN_RESET);
        bool state_ok  = (HAL_GPIO_ReadPin(BTN_OK_PORT, BTN_OK_PIN) == GPIO_PIN_RESET);

        /* processamento btn SET */
        button_event_t evt_set = button_process_interrupt_driven(&btn_set, state_set, &flag_exti_set);
        if (evt_set != BUTTON_EVENT_NONE) {
                
            if (evt_set == BUTTON_EVENT_SHORT_CLICK) {
                QEvt e;
                e.sig = SET_SIG; // Substitua pelo sinal correto na sua UML
                QASM_DISPATCH(super_ClockAlarm, &e, 0U);
            }
            // (Você também pode tratar BUTTON_EVENT_LONG_CLICK aqui se quiser)
        }

        /* processamento btn OK */
        button_event_t evt_ok = button_process_interrupt_driven(&btn_ok, state_ok, &flag_exti_ok);
        if (evt_ok != BUTTON_EVENT_NONE) {
            
            if (evt_ok == BUTTON_EVENT_SHORT_CLICK) {
                QEvt e;
                e.sig = OK_SIG; // Substitua pelo sinal correto na sua UML
                QASM_DISPATCH(super_ClockAlarm, &e, 0U);
            }
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
