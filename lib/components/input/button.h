/**
 * @file button.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-04-07
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

/* Tempos de configuração (em milissegundos) */
#define BUTTON_DEBOUNCE_MS     5
#define BUTTON_LONG_PRESS_MS   500
#define BUTTON_DOUBLE_CLICK_MS 300
#define BUTTON_VERY_LONG_PRESS_MS 3000

typedef enum {
    BUTTON_EVENT_NONE = 0,
    BUTTON_EVENT_SHORT_CLICK,
    BUTTON_EVENT_LONG_CLICK,
    BUTTON_EVENT_DOUBLE_CLICK,
    BUTTON_EVENT_TRIPLE_CLICK,
    BUTTON_EVENT_VERY_LONG_CLICK
} button_event_t;

/* Estrutura para gerenciar o estado do botão */
typedef struct {
    bool is_pressed;            
    bool last_raw_state;        
    uint32_t last_debounce_time;
    uint32_t press_start_time;  
    bool long_press_handled;    
    bool very_long_press_handled;
    uint8_t click_count;
    uint32_t last_release_time;
    bool waiting_double_click;
} button_t;

/* Protótipos das funções */

/**
 * @brief
 * @param btn
 */
void button_init(button_t *btn);

/*
* @brief       
* @param[in]   
* @return      
*            - 
*            - 
* @note       
*/
button_event_t button_process_interrupt_driven(button_t *btn, bool raw_pin_state, bool *exti_flag);

#endif // BUTTON_H
