/**
* @file    bsp.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-06-03
*/

#include "bsp.h"
#include "clock.h"
#include "gpio.h"
#include "stm32wbxx_hal.h"
#include "uart.h"


uint8_t hw_init(void) {
    HAL_Init();
    clock_config();
    // tim16_init();
    gpio_init();
    uart_init();
}

void BSP_display(char *c) {

}

void BSP_exit(void) {

}