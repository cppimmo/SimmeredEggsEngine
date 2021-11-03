#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "SDL.h"
#include "GL/glew.h"
#include <stdbool.h>
#include "config.h"

typedef struct {
	char title[75];
	int window_pos_x;
	int window_pos_y;
	int window_size_x;
	int window_size_y;
	bool window_maximized;
	bool window_minimized;
	bool is_visible;
	bool is_mouse_in_window;
	bool is_window_focus;
} WindowState;
static WindowState window_state;

bool window_init(SDL_Window *pWindow, SDL_GLContext *pContext,
				 const Options *const pOptions);
bool window_attribs(int glVersionMajor, int glVersionMinor, bool doubleBuffer);
void window_event_handle(const SDL_Event *pEvent);
WindowState *window_get_state();
bool window_close(SDL_Window* pWindow, SDL_GLContext *pContext);

#endif // APPWINDOW_H
