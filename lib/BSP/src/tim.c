/**
* @file    tim.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-05-26
*/

#include <stdint.h>
#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_tim.h"

uint8_t tim16_init() {
    TIM_HandleTypeDef TIM16_Init = {0};








    
    TIM16_Init.Instance = TIM16;
    TIM16_Init.Init.Prescaler = 99;
    TIM16_Init.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM16_Init.Init.Period = 665;
    TIM16_Init.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
}
