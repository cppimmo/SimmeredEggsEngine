#include "timer.h"
#include "SDL2/SDL.h"

inline void timer_init(Timer *p_timer)
{
    p_timer->elapsed = 0;
    p_timer->start = 0;
    p_timer->end = 0;
    p_timer->paused = true;
}

inline void timer_start(Timer *p_timer)
{
    if (p_timer->paused)
	return;
    p_timer->start = SDL_GetTicks();
}
    
inline void timer_stop(Timer *p_timer)
{
    if (p_timer->paused)
	return;
    p_timer->end = SDL_GetTicks();
}
    
inline bool timer_paused(Timer *p_timer)
{
    p_timer->paused = !p_timer->paused;
}

inline void timer_update(Timer *p_timer)
{
    if (p_timer->paused)
	return;
    p_timer->elapsed = p_timer->end - p_timer->start;
}

inline uint64_t timer_peek_ms(Timer *p_timer)
{
    return p_timer->elapsed;
}
