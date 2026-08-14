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

#define I2C_INSTANCE      I2C1
#define I2C_SDA_PORT      GPIOA
#define I2C_SDA_PIN       GPIO_PIN_10
#define I2C_SCL_PORT      GPIOA
#define I2C_SCL_PIN       GPIO_PIN_9


#define BTN_SET_PIN   GPIO_PIN_5 
#define BTN_SET_PORT  GPIOA
#define BTN_OK_PIN    GPIO_PIN_6
#define BTN_OK_PORT   GPIOA

#endif // BOARD_CONFIG_H
