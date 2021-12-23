/* =============================================================================
** SimmeredEggsEngine, file: g_window.h Created 12/6/2021
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
#ifndef __G_WINDOW_H__
#define __G_WINDOW_H__

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "u_utility.h"
#include "g_options.h"

struct windowstate_t {
	char title[75];
	int posx;
	int posy;
	int sizex;
	int sizey;
	boolean maximized;
	boolean minimized;
	boolean fullscreen;
	boolean visible;
	boolean mouseover; // is mouse in window
	boolean focused;
	boolean cursorvisible;
};
typedef struct windowstate_t WindowState;

void G_SetWindowPtr(SDL_Window **window);
boolean G_WindowInit(Options *const options);
boolean G_WindowAttribs(const int glmajor, const int glminor,
						boolean doublebuffer);
int G_WindowGetAttrib(SDL_GLattr attrib);
void G_WindowHandleEvent(const SDL_Event *event);
const WindowState *G_WindowGetState(void);
void G_WindowViewport(GLint posx, GLint posy, GLint width, GLint height);
void G_WindowSetFullscreen(boolean fullscreen);
void G_WindowSetTitle(const char *title);
void G_WindowSetSize(int width, int height);
void G_WindowShowCursor(boolean cursor);
void G_WindowSwap(void);
boolean G_WindowClose(void);

#endif
