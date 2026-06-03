/**
 * @file bsp.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-06-03
 */

#ifndef BSP_H
#define BSP_H

#include <stdint.h>

uint8_t hw_init(void);

void BSP_display(char *c);

void BSP_exit(void);


#endif // BSP_H
