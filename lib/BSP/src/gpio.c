/**
 * @file    gpio.c
 * @brief   none
 * @version 0.1.0
 * @author  
 * @date    
 */

#include "gpio.h"
#include "board_config.h"
#include "stm32wbxx_hal_gpio.h"
#include "stm32wbxx_hal_gpio_ex.h"

uint8_t gpio_init(void) {
    
    // Led
    GPIO_InitTypeDef gpio_led = {0};
    gpio_led.Pin = led_pin;
    gpio_led.Mode = GPIO_MODE_AF_PP;
    gpio_led.Alternate = GPIO_AF14_TIM16;
    gpio_led.Pull = GPIO_NOPULL;
    gpio_led.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(led_port, &gpio_led);

    // USART1 pin muxing configurations
    GPIO_InitTypeDef gpio_uart = {0};
    gpio_uart.Pin = uart_pin;
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Alternate = GPIO_AF7_USART1;
    gpio_uart.Pull = GPIO_PULLUP;
    gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(uart_port, &gpio_uart);

    return 0;
}


