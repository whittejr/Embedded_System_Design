#/**
 * @file board_config.h
 * @brief  none
 * @version 0.1
 * @author Your name here
 * @date 2026-05-27
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "stm32wbxx_hal.h"

#define led_pin     GPIO_PIN_6
#define led_port    GPIOA
#define uart_pin    GPIO_PIN_6|GPIO_PIN_7
#define uart_port   GPIOB

#endif // BOARD_CONFIG_H
