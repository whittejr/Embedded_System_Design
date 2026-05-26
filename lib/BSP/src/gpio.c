/**
 * @file    gpio.c
 * @brief   none
 * @version 0.1.0
 * @author  
 * @date    
 */

#include "gpio.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_gpio.h"
#include "stm32wbxx_hal_gpio_ex.h"

uint8_t gpio_init(void) {
    
    // led
    GPIO_InitTypeDef gpio_led = {0};
    gpio_led.Pin = led_pin;
    gpio_led.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_led.Pull = GPIO_PULLDOWN;
    gpio_led.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(led_port, &gpio_led);

    // USART1 pin muxing configurations
    GPIO_InitTypeDef gpio_uart = {0};
    gpio_uart.Pin = GPIO_PIN_6|GPIO_PIN_7;
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Alternate = GPIO_AF7_USART1;
    gpio_uart.Pull = GPIO_PULLUP;
    gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio_uart);

    // Enabling IRQ and set up the priority (NVIC)
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);

    return 0;
}
