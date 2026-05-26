/**
 * @file gpio.h
 * @brief  none
 * @version 0.1
 * @author 
 * @date 
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// chip specific
#define led_pin GPIO_PIN_4
#define led_port GPIOE

uint8_t gpio_init(void);


#endif // GPIO_H
