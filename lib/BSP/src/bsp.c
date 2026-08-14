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
#include "stm32wbxx_hal_gpio.h"
#include "uart.h"

uint8_t hw_init(void) {
    HAL_Init();
    clock_config();
    // tim16_init();
    gpio_init();
    uart_init();

    bsp_display_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
    // bsp_display_write_string(0, 0,"teste");
    bsp_display_clear();
}

void BSP_display(char *c) {
    uart_write((uint8_t*) c, strlen(c));
}

uint8_t bsp_display_init(ssd1306_interface_t interface, ssd1306_address_t addr) {
    ssd1306_basic_init(interface, addr);
    ssd1306_basic_display_on();
    
    return 0;
}

void bsp_display_clear(void) {
    ssd1306_basic_clear();
}

void bsp_display_write_string(uint8_t x, uint8_t y, char *texto) {
    ssd1306_basic_string(x, y, texto, (uint16_t)strlen(texto), 1, SSD1306_FONT_16);
}

void bsp_write_rect(void) {
    ssd1306_basic_rect(0, 18, 5, 21, 1);
}