/**
* @file    moore_fsm.c
* @brief   none
* @version 0.1.0
* @author  Your name here
* @date    2026-05-27
*/

#include "moore_fsm.h"

void moore_run_entry_action(light_state_t state) {
  switch(state)
  {
    case LIGHT_OFF:{
      light_change_intensity(LIGHT_BRIGHT_OFF);
      break; 
    }
    case LIGHT_DIM:{
      light_change_intensity(LIGHT_BRIGHT_DIM);
      break; 
    }
    case LIGHT_MEDIUM:{
      light_change_intensity(LIGHT_BRIGHT_MED);
      break; 
    }
    case LIGHT_FULL:{
      light_change_intensity(LIGHT_BRIGHT_FULL);
      break; 
    }
  }
}

void moore_state_machine(light_state_t *curr_state, uint8_t event) {
  light_state_t prev_state;

  prev_state = *curr_state;
  switch(*curr_state)
  {
    case LIGHT_OFF:{
      switch(event){
        case ON:{
          *curr_state = LIGHT_DIM;
          break;
        }
      }
      break;
    }
    case LIGHT_DIM:{
      switch(event){
        case ON:{
          *curr_state = LIGHT_MEDIUM;
          break;
        }
        case OFF:{
          *curr_state = LIGHT_OFF;
          break;
        }
      }
      break;
    }
    case LIGHT_MEDIUM:{
      switch(event){
        case ON:{
          *curr_state = LIGHT_FULL;
          break;
        }
        case OFF:{
          *curr_state = LIGHT_OFF;         
          break;
        }
      }
      break;
    }
    case LIGHT_FULL:{
      switch(event){
        case ON:{
          *curr_state = LIGHT_DIM;         
          break;
        }
        case OFF:{
          *curr_state = LIGHT_OFF;          
          break;
        }
      }
      break;
    }
  }

  if(prev_state != *curr_state)
    moore_run_entry_action(*curr_state);
}
