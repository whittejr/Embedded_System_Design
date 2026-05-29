/**
 * @file fsm.h
 * @brief  none
 * @version 0.1
 * @author Your name here
 * @date 2026-05-27
 */

#ifndef FSM_H
#define FSM_H

#include <stdint.h>

enum event {
    ON,
    OFF
};

typedef enum {
    LIGHT_OFF,
    LIGHT_DIM,
    LIGHT_MEDIUM,
    LIGHT_FULL
} light_state_t;


#define LIGHT_BRIGHT_DIM 25
#define LIGHT_BRIGHT_MED 85
#define LIGHT_BRIGHT_FULL 255
#define LIGHT_BRIGHT_OFF 0

void light_change_intensity(uint8_t intensity);

#endif // FSM_H
