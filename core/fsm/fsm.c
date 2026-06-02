/**
* @file    fsm.c
* @brief   none
* @version 0.1.0
* @author  Your name here
* @date    2026-05-27
*/

#include "fsm.h"
#include "board_config.h"

void light_change_intensity(uint8_t intensity) {
    bsp_pwm_intensity(led_pin, led_port, intensity);
}

