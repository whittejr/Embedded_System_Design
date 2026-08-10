/**
 * @file bsp.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-06-03
 */

#ifndef BSP_H
#define BSP_H
#include "driver_ssd1306_basic.h"
#include <stdint.h>

uint8_t hw_init(void);
void BSP_display(char *c);

uint8_t bsp_display_init(ssd1306_interface_t interface, ssd1306_address_t addr);
void bsp_display_clear(void);
void bsp_display_write_string(uint8_t x, uint8_t y, char *texto);

#endif // BSP_H
