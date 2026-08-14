/**
* @file    button.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-04-07
*/

#include "button.h"

void button_init(button_t *btn) {
    btn->is_pressed = 0;
    btn->last_raw_state = 0;
    btn->last_debounce_time = 0;
    btn->press_start_time = 0;
    btn->long_press_handled = 0;
    btn->very_long_press_handled = 0;
    btn->click_count = 0;
    btn->last_release_time = 0;
    btn->waiting_double_click = 0;
}

button_event_t button_process_interrupt_driven(button_t *btn, bool raw_pin_state, bool *exti_flag) {
    button_event_t event = BUTTON_EVENT_NONE;
    uint32_t current_tick_ms = HAL_GetTick();

    // 1. Se a interrupção avisou que houve mudança de estado físico
    if (*exti_flag) {
        *exti_flag = 0; // "Limpa/Consome" a flag para não processar de novo
        btn->last_debounce_time = current_tick_ms; // Inicia o timer do debounce
    }

    if ((current_tick_ms - btn->last_debounce_time) >= BUTTON_DEBOUNCE_MS) {
        if (raw_pin_state != btn->is_pressed) {
            btn->is_pressed = raw_pin_state;

            // O botão acabou de ser PRESSIONADO
            if (btn->is_pressed) {
                btn->press_start_time = current_tick_ms; 
                btn->long_press_handled = 0;         
                btn->very_long_press_handled = 0;
            } 
            // O botão acabou de ser SOLTO
            else {
                if (!btn->long_press_handled && !btn->very_long_press_handled) {
                    btn->click_count++;
                    btn->last_release_time = current_tick_ms;
                    btn->waiting_double_click = 1;
                } else {
                    btn->click_count = 0;
                    btn->waiting_double_click = 0;
                }
            }
        }
    }

    // Tratamento de clique longo e super longo
    if (btn->is_pressed) {
        uint32_t press_duration = current_tick_ms - btn->press_start_time;
        if (!btn->very_long_press_handled && press_duration >= BUTTON_VERY_LONG_PRESS_MS) {
            event = BUTTON_EVENT_VERY_LONG_CLICK;
            btn->very_long_press_handled = 1;
            btn->long_press_handled = 1; // previne multiplos cliques
        } else if (!btn->long_press_handled && press_duration >= BUTTON_LONG_PRESS_MS) {
            event = BUTTON_EVENT_LONG_CLICK;
            btn->long_press_handled = 1;
        }
    }

    // Tratamento de double click/triple click (esperando timeout)
    if (!btn->is_pressed && btn->waiting_double_click) {
        if ((current_tick_ms - btn->last_release_time) >= BUTTON_DOUBLE_CLICK_MS) {
            if (btn->click_count == 1) {
                event = BUTTON_EVENT_SHORT_CLICK;
            } else if (btn->click_count == 2) {
                event = BUTTON_EVENT_DOUBLE_CLICK;
            } else if (btn->click_count >= 3) {
                event = BUTTON_EVENT_TRIPLE_CLICK;
            }
            btn->click_count = 0;
            btn->waiting_double_click = 0;
        } else if (btn->click_count >= 3) {
            event = BUTTON_EVENT_TRIPLE_CLICK;
            btn->click_count = 0;
            btn->waiting_double_click = 0;
        }
    }

    return event;
}