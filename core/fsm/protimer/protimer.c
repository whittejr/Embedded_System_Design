// /**
// * @file    protimer.c
// * @brief   none
// * @version 0.1.0
// * @author  Alessandro Davi
// * @date    2026-05-31
// */

// #include "protimer.h"
// #include "stm32wbxx_hal.h"
// #include "uart.h"
// #include <stdio.h>
// #include <string.h>

// extern UART_HandleTypeDef uart1;
// extern uint8_t dispatcher_flag;

// static void display_time(uint32_t time);
// static void display_message (char *msg);
// static void display_clear(void);
// static void do_beep(void);

// /* prototypes of state handlers */
// static event_status_t protimer_state_machine(protimer_t *mobj, event_t *e);

// static event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t *const e);
// static event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t *const e);
// static event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t *const e);
// static event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t *const e);
// static event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t *const e);

// void protimer_init(protimer_t *mobj) {
//     event_t e;
//     e.sig = ENTRY;
//     mobj->active_state = IDLE;
//     mobj->curr_time = 0;
//     mobj->pro_time = 0;

//     protimer_state_machine(mobj, &e);
// }

// void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e) {
//     event_status_t status;
//     protimer_state_t source, target;

//     source = mobj->active_state;
//     status = protimer_state_machine(mobj, e);
//     if (status == EVENT_TRANSITION) {
//         target = mobj->active_state;
//         event_t ee;
//         // 1. run exit action for the source state
//         ee.sig = EXIT;
//         mobj->active_state = source;
//         protimer_state_machine(mobj, &ee);

//         // 2. run the entry action for the target state
//         ee.sig = ENTRY;
//         mobj->active_state = target;
//         protimer_state_machine(mobj, &ee);
//     }
// }

// static event_status_t protimer_state_machine(protimer_t *mobj, event_t *e) {
//     switch(mobj->active_state) {
//         case IDLE: {
//             return protimer_state_handler_IDLE(mobj, e);
//         }

//         case TIME_SET: {
//             return protimer_state_handler_TIME_SET(mobj, e);
//         }

//         case COUNTDOWN: {
//             return protimer_state_handler_COUNTDOWN(mobj, e);
//         }

//         case PAUSE: {
//             return protimer_state_handler_PAUSE(mobj, e);
//         }

//         case STAT: {
//             return protimer_state_handler_STAT(mobj, e);
//         }
//     } // END OF SWITCH
//     return EVENT_IGNORED;
// }


// static event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t *const e) {
//     switch(e->sig) {
//         case ENTRY: {
//             mobj->curr_time = 0;
//             mobj->elapsed_time = 0;
//             display_time(0);
//             display_message("Set time");
//             return EVENT_HANDLED;
//         }
//         case EXIT: {
//             display_clear();
//             return EVENT_HANDLED;
//         }

//         case INC_TIME: {
//             mobj->curr_time += 60;
//             mobj->active_state = TIME_SET;
//             return EVENT_TRANSITION;
//         }

//         case START_PAUSE: {
//             mobj->active_state = STAT;
//             return EVENT_TRANSITION;
//         }

//         case TIME_TICK: {
//              if (((protimer_tick_event_t *)(e))->ss == 5) {
//                 do_beep();
//                 return EVENT_HANDLED;
//              }
//              return EVENT_IGNORED;
//         }
//     }
//     return EVENT_IGNORED;
// }
// static event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t *const e) {
//     switch (e->sig) {

//         case ENTRY:{
//             display_time(mobj->curr_time);
//             return EVENT_HANDLED;
//         }

//         case EXIT:{
//             display_clear();
//             return EVENT_HANDLED;
//         }

//         case START_PAUSE: {
//             if (mobj->curr_time < 60)
//                 return EVENT_IGNORED;
//             mobj->active_state = COUNTDOWN;
//             return EVENT_TRANSITION;
//         }

//         case ABRT: {
//             mobj->active_state = IDLE;
//             return EVENT_TRANSITION;
//         }

//         case INC_TIME: {
//             mobj->curr_time += 60;
//             display_time(mobj->curr_time);
//             return EVENT_HANDLED;
//         }

//         case DEC_TIME: {
//             if (mobj->curr_time < 60)
//                 return EVENT_IGNORED;
//             mobj->curr_time -= 60;
//             return EVENT_HANDLED;
//         }
//     }

//     return EVENT_IGNORED;
// }
// static event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t *const e) {
//     switch(e->sig) {
//         case EXIT: {
//             mobj->pro_time += mobj->elapsed_time;
//             mobj->elapsed_time = 0;
//             return EVENT_HANDLED;
//         }

//         case TIME_TICK: {
//             if( ( (protimer_tick_event_t*) (e))->ss == 10) {
//                 --mobj->curr_time;
//                 ++mobj->elapsed_time;
//                 display_time(mobj->curr_time);
//                 if(!mobj->curr_time) {
//                     mobj->active_state = IDLE;
//                     return EVENT_TRANSITION;
//                 }
//                 return EVENT_HANDLED;
//             }
//             return EVENT_IGNORED;
//         }

//         case START_PAUSE: {
//             mobj->active_state = PAUSE;
//             return EVENT_TRANSITION;
            
//         }

//         case ABRT: {
//             mobj->active_state = IDLE;
//             return EVENT_TRANSITION;
//         }        
//     }
//     return EVENT_IGNORED;
// }
// static event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t *const e) {
//     switch(e->sig) {
//         case ENTRY: {
//             display_message("paused");
//             return EVENT_HANDLED;
//         }

//         case START_PAUSE: {
//             mobj->active_state = COUNTDOWN;
//             return EVENT_TRANSITION;
//         }

//         case DEC_TIME: {
//             if (mobj->curr_time >= 60) {
//                 mobj->curr_time -= 60;
//                 mobj->active_state = TIME_SET;
//                 return EVENT_TRANSITION;
//             }
//             return EVENT_IGNORED;
//         }

//         case INC_TIME: {
//             mobj->curr_time += 60;
//             mobj->active_state = TIME_SET;
//             return EVENT_TRANSITION;
//         }

//         case ABRT: {
//             mobj->active_state = IDLE;
//             return EVENT_TRANSITION;
//         }
//     }
//     return EVENT_IGNORED;
// }
// static event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t *const e) {
//     switch(e->sig) {
//         case ENTRY: {
//             display_time(mobj->pro_time);
//             display_message("Productive time");
//             return EVENT_HANDLED;
//         }
//         case EXIT: {
//             display_clear();
//             return EVENT_HANDLED;
//         }

//         case TIME_TICK: {
//             if ( ((protimer_tick_event_t*) (e))->ss == 10) {
//                 mobj->active_state = IDLE;
//                 return EVENT_HANDLED;
//             }
//             return EVENT_IGNORED;
//         }
//     }
//     return EVENT_IGNORED;
// }

// static void display_message (char *msg) {
//         display_clear();
//         uart_write((uint8_t*) msg, strlen(msg));
        
// }

// static void display_clear(void) {
//     char *clear = "\x1B[2J\x1B[H";
//     uart_write((uint8_t*) clear, strlen(clear));
// }

// static void do_beep(void) {

// }

// static void display_time(uint32_t time) {
//     display_clear();
//     char buf[12];   

//     uint16_t m = time / 60;
//     uint8_t s = time % 60;
//     uint16_t len = snprintf(buf, sizeof(buf), "%03d:%02d\r\n", m, s);

//     uart_write((uint8_t*) buf, len);
// }
