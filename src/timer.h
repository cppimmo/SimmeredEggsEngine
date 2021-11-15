#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct timer_t {
    uint64_t elapsed;
    uint64_t start;
    uint64_t end;
    bool paused;
};
typedef struct timer_t Timer;

void timer_init(Timer *p_timer);
void timer_start(Timer *p_timer);
void timer_stop(Timer *p_timer);
bool timer_paused(Timer *p_timer);
void timer_update(Timer *p_timer);
uint64_t timer_peek_ms(Timer *p_timer);

#endif // TIMER_H
