/**
 * @file moore_fsm.h
 * @brief  none
 * @version 0.1
 * @author Your name here
 * @date 2026-05-27
 */

#ifndef MOORE_FSM_H
#define MOORE_FSM_H

#include "fsm.h"

void moore_run_entry_action(light_state_t state);
void moore_state_machine(light_state_t *curr_state, uint8_t event);

#endif // MOORE_FSM_H
