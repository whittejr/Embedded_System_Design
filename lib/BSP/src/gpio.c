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

/* static functions */
static void btn_init(void);

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


    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pin : PE4 */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    btn_init();

    return 0;
}

static void btn_init(void) {
    GPIO_InitTypeDef btn_pins;
    btn_pins.Mode = GPIO_MODE_INPUT;
    btn_pins.Pull = GPIO_PULLUP;
    btn_pins.Pin = BTN_SET_PIN;
    HAL_GPIO_Init(BTN_SET_PORT, &btn_pins);

    btn_pins.Pin = BTN_OK_PIN;
    HAL_GPIO_Init(BTN_OK_PORT, &btn_pins);
}


