/**
* @file    protimer.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-05-31
*/

#include "protimer.h"

void protimer_init(protimer_t *mobj) {
    mobj->active_state = IDLE;
    mobj->pro_time = 0;
    
}