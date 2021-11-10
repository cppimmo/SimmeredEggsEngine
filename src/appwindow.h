#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "SDL2/SDL.h"
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

bool window_init(SDL_Window *p_window, SDL_GLContext *p_context,
				 const Options *const p_options);
bool window_attribs(int glv_major, int glv_minor, bool double_buffer);
int window_get_attrib(SDL_GLattr attr);
void window_event_handle(const SDL_Event *p_event);
WindowState *window_get_state();
void window_viewport(GLint posx, GLint posy, GLint width, GLint height);
bool window_close(SDL_Window* p_window, SDL_GLContext *p_context);

#endif // APPWINDOW_H
