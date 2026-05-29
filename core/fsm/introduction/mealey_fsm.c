/**
* @file    mealey_fsm.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-05-27
*/

#include "fsm.h"

void mealey_light_state_machine(light_state_t *curr_state, uint8_t event) {
  
  switch(*curr_state)
  {
    case LIGHT_OFF:{
      switch(event){
        case ON:{
          light_change_intensity(LIGHT_BRIGHT_DIM);
          *curr_state = LIGHT_DIM;
          break;
        }
      }
      break;
    }
    case LIGHT_DIM:{
      switch(event){
        case ON:{
          light_change_intensity(LIGHT_BRIGHT_MED);
          *curr_state = LIGHT_MEDIUM;
          break;
        }
        case OFF:{
          light_change_intensity(LIGHT_BRIGHT_OFF);
          *curr_state = LIGHT_OFF;
          break;
        }
      }
      break;
    }
    case LIGHT_MEDIUM:{
      switch(event){
        case ON:{
          light_change_intensity(LIGHT_BRIGHT_FULL);
          *curr_state = LIGHT_FULL;
          break;
        }
        case OFF:{
          light_change_intensity(LIGHT_BRIGHT_OFF);
          *curr_state = LIGHT_OFF;         
          break;
        }
      }
      break;
    }
    case LIGHT_FULL:{
      switch(event){
        case ON:{
          light_change_intensity(LIGHT_BRIGHT_DIM);
          *curr_state = LIGHT_DIM;         
          break;
        }
        case OFF:{
          light_change_intensity(LIGHT_BRIGHT_OFF);
          *curr_state = LIGHT_OFF;          
          break;
        }
      }
      break;
    }
  }
}
