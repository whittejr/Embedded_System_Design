/**
 * @file uart.h
 * @brief  none
 * @version 0.1
 */

#ifndef UART_H
#define UART_H

#include "stm32wbxx_hal.h"
#include <stdint.h>

extern UART_HandleTypeDef uart1;

/*
* @brief       
* @param[in]   
* @return      
*            - 
*            - 
* @note       
*/
uint8_t uart_init(void);

/*
* @brief       
* @param[in]   
* @return      
*            - 
*            - 
* @note       
*/
uint8_t uart_deinit(void);

/*
* @brief       
* @param[in]   
* @return      
*            - 
*            - 
* @note       
*/
void uart_write(uint8_t *buf, uint16_t len);

/*
* @brief       
* @param[in]   
* @return      
*            - 
*            - 
* @note       
*/
uint8_t uart_receive(uint8_t *data, uint16_t size);

#endif // UART_H
