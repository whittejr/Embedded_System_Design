/**
 * @file tim.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-05-26
 */

#ifndef TIM_H
#define TIM_H

#include "stm32wb55xx.h"
#include <stdint.h>

uint8_t tim16_init(void);
void bsp_pwm_intensity(uint16_t GPIO_Pin, GPIO_TypeDef *GPIOx, uint8_t intensity);

#endif // TIM_H
