/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @a* @author  Your name here
* @date    2026-03-31
*/

#include "Legacy/stm32_hal_legacy.h"
#include "main.h"
#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_def.h"
#include "stm32wbxx_hal_gpio.h"
#include "stm32wbxx_hal_rcc.h"
#include "stm32wbxx_hal_uart.h"
#include "stm32wbxx_hal_uart_ex.h"
#include "stm32wbxx_hal_usart.h"
#include "uart.h"

// chip specific
#define led_pin GPIO_PIN_4
#define led_port GPIOE

UART_HandleTypeDef uart1;

void clk_enable(void);
void gpio_init(void);
void uart_init(void);

// FSM logic
enum event {
    ON,
    OFF
};

typedef enum {
    LIGHT_OFF,
    LIGHT_DIM,
    LIGHT_MEDIUM,
    LIGHT_FULL
} light_state_t;

light_state_t curr_state;

#define LIGHT_BRIGHT_DIM 25
#define LIGHT_BRIGHT_MED 85
#define LIGHT_BRIGHT_FULL 255
#define LIGHT_BRIGHT_OFF 0

void light_state_machine(uint8_t event);
void light_change_intensity(uint8_t pin, GPIO_TypeDef *port, uint8_t intensity);
void run_entry_action(light_state_t state);
void light_init(void);

// error handler
void Error_Handler(void);

//
uint8_t data;


int main(void)
{
    HAL_Init();
    clk_enable();
    gpio_init();
    uart_init();

    light_init();
    
    while (1) {
        if (HAL_UART_Receive(&uart1, &data, 1, HAL_MAX_DELAY))
    }
    return 0;
}

// chip specific
void clk_enable(void) {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
}
void gpio_init(void) {

    // led
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = led_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(led_port, &GPIO_InitStruct);

    // usart1 pins
    GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
}

void uart_init(void) {
    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;
    uart1.Init.OverSampling = UART_OVERSAMPLING_16;
    uart1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    uart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;

    if (HAL_UART_Init(&uart1) != 0) {
        Error_Handler();
    }
}


// FSM logic
void light_init(void) {
    curr_state = LIGHT_OFF;
    run_entry_action(LIGHT_OFF);
}

void run_entry_action(light_state_t state) {
    switch(state) {

        case LIGHT_OFF: {
            light_change_intensity(led_pin, led_port, LIGHT_BRIGHT_OFF);
            break;
        }
        case LIGHT_DIM: {
            light_change_intensity(led_pin, led_port, LIGHT_BRIGHT_DIM);
            break;
        }
        case LIGHT_MEDIUM: {
            light_change_intensity(led_pin, led_port, LIGHT_BRIGHT_MED);
            break;
        }
        case LIGHT_FULL: {
            light_change_intensity(led_pin, led_port, LIGHT_BRIGHT_FULL);
            break;
        }
    }
}


// error handler
void Error_Handler(void) {
    __disable_irq();
    while(1);
}
