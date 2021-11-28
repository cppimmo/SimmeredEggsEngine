#ifndef FONT_H
#define FONT_H

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "u_utility.h"

boolean font_init();
void font_info();
char *font_get_error();
TTF_Font *font_open(const char *filename, int size);
SDL_Surface *font_render_solid(TTF_Font *font, const char *text, SDL_Color fg);
void font_close(TTF_Font *font);
void font_quit();

#endif // FONT_H
