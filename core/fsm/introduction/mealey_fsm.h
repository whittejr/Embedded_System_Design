/**
 * @file mealey_fsm.h
 * @brief  none
 * @version 0.1
 * @author Your name here
 * @date 2026-05-27
 */

#ifndef MEALEY_FSM_H
#define MEALEY_FSM_H

#include "fsm.h"
#include <stdint.h>

void mealey_light_state_machine(light_state_t *curr_state, uint8_t event);

#endif // MEALEY_FSM_H
