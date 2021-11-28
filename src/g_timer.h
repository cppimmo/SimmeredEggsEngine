#ifndef __G_TIMER_H__
#define __G_TIMER_H__

#include <stdlib.h>
#include <stdint.h>
#include "u_utility.h"

struct timer_t {
    uint64_t elapsed;
    uint64_t start;
    uint64_t end;
    boolean paused;
};

void G_TimerInit(struct timer_t *timer);
void G_TimerStart(struct timer_t *timer);
void G_TimerStop(struct timer_t *timer);
boolean G_TimerPaused(struct timer_t *timer);
void G_TimerUdpate(struct timer_t *timer);
uint64_t G_TimerPeekMS(struct timer_t *timer);

#endif
