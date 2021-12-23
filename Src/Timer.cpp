/* =============================================================================
** SimmeredEggsEngine, file: g_timer.c Created 12/6/2021
**
** Copyright 2021 Brian Hoffpauir TX, USA
** All rights reserved.
**
** Redistribution and use of this source file, with or without modification, is
** permitted provided that the following conditions are met:
**
** 1. Redistributions of this source file must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
** EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** =============================================================================
**/
#include "g_timer.h"
#include "SDL2/SDL.h"

inline void G_TimerInit(Timer *timer) {
    timer->elapsed = 0;
    timer->start = 0;
    timer->end = 0;
    timer->paused = true;
}

inline void G_TimerStart(Timer *timer) {
    if (timer->paused)
		return;
    timer->start = SDL_GetTicks();
}

inline void G_TimerEnd(Timer *timer) {
    if (timer->paused)
		return;
    timer->end = SDL_GetTicks();
}

inline boolean G_TimerIsPaused(Timer *timer) {
	return timer->paused;
}

inline void G_TimerPause(Timer *timer, boolean pause) {
    timer->paused = pause;
}

inline void G_TimerUpdate(Timer *timer) {
    if (timer->paused)
		return;
    timer->elapsed = timer->end - timer->start;
}

inline uint64_t G_TimerPeekMS(Timer *timer) {
    return timer->elapsed;
}
