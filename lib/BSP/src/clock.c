/**
 * @file    clock.c
 * @brief   none
 * @version 0.1.0
 * @author  
 * @date    
 */

#include "clock.h"
#include "stdint.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_rcc.h"

uint8_t clock_config(void) {
  
  /*
  * clock configuration can be generated using CubeMX Software
  */
  
  // Peripherals clock initialization
  __HAL_RCC_USART1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_TIM16_CLK_ENABLE();

  return 0;
}
