/**
 * @file protimer.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-05-31
 */

#ifndef PROTIMER_H
#define PROTIMER_H

/* Signals of the application */
#include <stdint.h>
typedef enum {
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    START_PAUSE,
    ABRT,
/* Internal activity signals */
    ENTRY,
    EXIT
} protimer_signal_t;

/* Various states of the application */
typedef enum {
    IDLE,
    TIME_SET,
    COUNTDOWN,
    PAUSE,
    STAT
} protimer_state_t;

/* Main application structure */

typedef struct {
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
} protimer_t;

/* Generic(Super) event structure */
typedef struct {
    uint8_t sig;
} event_t;

typedef struct {
    event_t super;
} protimer_user_event_t;

typedef struct {
    event_t super;
    uint8_t ss;
} protimer_tick_event_t;

typedef enum {
    EVENT_HANDLED,
    EVENT_IGNORED,
    EVENT_TRANSITION
} event_status_t;


/* Functions */
void protimer_init(protimer_t *mobj);
void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e);

#endif // PROTIMER_H
