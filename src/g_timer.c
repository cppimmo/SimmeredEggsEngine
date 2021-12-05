#include "g_timer.h"
#include "SDL2/SDL.h"

inline void G_TimerInit(struct timer_t *timer) {
    timer->elapsed = 0;
    timer->start = 0;
    timer->end = 0;
    timer->paused = true;
}

inline void G_TimerStart(struct timer_t *timer) {
    if (timer->paused)
		return;
    timer->start = SDL_GetTicks();
}

inline void G_TimerStop(struct timer_t *timer) {
    if (timer->paused)
		return;
    timer->end = SDL_GetTicks();
}

inline boolean G_TimerPaused(struct timer_t *timer) {
    timer->paused = !timer->paused;
}

inline void G_TimerUpdate(struct timer_t *timer) {
    if (timer->paused)
		return;
    timer->elapsed = timer->end - timer->start;
}

inline uint64_t G_TimerPeekMS(struct timer_t *timer) {
    return timer->elapsed;
}

