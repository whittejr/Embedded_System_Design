/**
* @file    main.c
* @brief   none
* @version 0.1.0
* @a* @author  Your name here
* @date    2026-03-31
*/

#include "main.h"
#include "stm32wbxx_hal.h"
#include "gpio.h"
#include "clock.h"
#include "stm32wbxx_hal_def.h"
#include "stm32wbxx_hal_uart.h"
#include "uart.h"
#include <string.h>

extern UART_HandleTypeDef uart1;

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

// global variables
uint8_t event;
uint8_t buffer;

// test
char *user_data = "The application is running\r\n";
uint8_t received_data;
uint8_t data_buffer[100];
uint8_t count;


int main(void) {
  /* CHIP LOGIC */

  // peripheral init
  HAL_Init();
  clock_config();
  gpio_init();
  uart_init();
  // IT Init
  // HAL_UART_Receive_IT(&uart1, &buffer, 1);

  // uint32_t data_len = strlen(user_data);
  // if (HAL_UART_Transmit(&uart1, (uint8_t*) user_data, (uint16_t) data_len, HAL_MAX_DELAY) != 0)
  //     return 1;

  while (1) {
  HAL_UART_Receive(&uart1, &received_data, 1, HAL_MAX_DELAY);
  if (received_data == '\r') {
    data_buffer[count++] = '\r';
    HAL_UART_Transmit(&uart1, data_buffer, count, HAL_MAX_DELAY);
    memset(data_buffer, 0, count);  
  } else {
    data_buffer[count++] = received_data;
  }
  
  }
  

  /* CHIP LOGIC */


    
  // FSM logic
  light_init();
  
  while (1) {
  }

  return 0;
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

void light_state_machine(uint8_t event) {
  
  switch(curr_state)
  {
    case LIGHT_OFF:{
      switch(event){
        case ON:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_DIM);
          curr_state = LIGHT_DIM;
          break;
        }
      }
      break;
    }
    case LIGHT_DIM:{
      switch(event){
        case ON:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_MED);
          curr_state = LIGHT_MEDIUM;
          break;
        }
        case OFF:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;
          break;
        }
      }
      break;
    }
    case LIGHT_MEDIUM:{
      switch(event){
        case ON:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_FULL);
          curr_state = LIGHT_FULL;
          break;
        }
        case OFF:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;         
          break;
        }
      }
      break;
    }
    case LIGHT_FULL:{
      switch(event){
        case ON:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_DIM);
          curr_state = LIGHT_DIM;         
          break;
        }
        case OFF:{
          light_change_intensity(led_pin, led_port,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;          
          break;
        }
      }
      break;
    }
  }
}


// error handler
void Error_Handler(void) {
    __disable_irq();
    while(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    event = buffer;

    if (event == 'o') {
        light_state_machine(ON);
    }
    else if (event == 'x') {
        light_state_machine(OFF);
    }

	HAL_UART_Receive_IT(&uart1, &buffer, 1);
}

void light_change_intensity(uint8_t pin, GPIO_TypeDef *port, uint8_t intensity) {

}

void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UARTEx_TxFifoEmptyCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UARTEx_RxFifoFullCallback(UART_HandleTypeDef *huart)
{

}
