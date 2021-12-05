#ifndef __HU_FONT_H__
#define __HU_FONT_H__

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "u_utility.h"

boolean HU_FontInit(void);
void HU_FontInfo(void);
const char *HU_GetFontError(void);
TTF_Font *HU_FontOpen(const char *filename, int size);
SDL_Surface *HU_FontRenderSolid(TTF_Font *font, const char *text, SDL_Color fg);
void HU_FontClose(TTF_Font *font);
void HU_FontQuit(void);

#endif
