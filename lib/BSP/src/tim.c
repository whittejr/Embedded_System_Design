/**
* @file    tim.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-05-26
*/


#include <stdint.h>
#include "stm32wbxx_hal.h"
#include "tim.h"

TIM_HandleTypeDef tim16 = {0};

uint8_t tim16_init(void) {

    TIM_OC_InitTypeDef tim16PWM_Config = {0};
    // TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    // Timer Cfg
    tim16.Instance = TIM16;
    tim16.Init.Prescaler = 1;
    tim16.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim16.Init.Period = 33332;
    tim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim16.Init.RepetitionCounter = 0;
    tim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&tim16) != HAL_OK) return 1;

    tim16PWM_Config.OCMode = TIM_OCMODE_PWM1;
    tim16PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;
    tim16PWM_Config.Pulse = 33332;
    if (HAL_TIM_PWM_ConfigChannel(&tim16, &tim16PWM_Config, TIM_CHANNEL_1) != 0) return 1;
    
    // Enabling TIM16 IRQ and set up the priority (NVIC)
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

    // PWM Start
    // if (HAL_TIM_PWM_Start(&tim16, TIM_CHANNEL_1) != 0) return 1;

    return 0;
}

void bsp_pwm_intensity(uint16_t GPIO_Pin, GPIO_TypeDef *GPIOx, uint8_t intensity) {
    uint32_t period = 33332;
    
    // Converte a intensidade de 0-255 para o limite de 0-33332
    uint32_t new_pulse = (period * intensity) / 255;
    
    __HAL_TIM_SET_COMPARE(&tim16, TIM_CHANNEL_1, new_pulse);
}
