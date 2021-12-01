#ifndef __G_WINDOW_H__
#define __G_WINDOW_H__

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "u_utility.h"
#include "g_config.h"

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
};

void G_SetWindowPtr(SDL_Window **window);
boolean G_WindowInit(struct config_t *const config);
boolean G_WindowAttribs(const int glmajor, const int glminor,
						boolean doublebuffer);
int G_WindowGetAttrib(SDL_GLattr attrib);
void G_WindowHandleEvent(const SDL_Event *event);
struct windowstate_t *G_WindowGetState(void);
void G_WindowViewport(GLint posx, GLint posy, GLint width, GLint height);
void G_WindowSetFullscreen(boolean fullscreen);
void G_WindowSetTitle(const char *title);
void G_WindowSetSize(int width, int height);
void G_WindowShowCursor(boolean cursor);
void G_WindowSwap(void);
boolean G_WindowClose(void);

#endif
