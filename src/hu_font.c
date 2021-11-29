#include "hu_font.h"
#include "u_log.h"

boolean HU_FontInit(void) {
	return (TTF_Init() == -1) ? false : true;
}

void HU_FontInfo(void) {
	/* SDL_version compile_version;
	const SDL_version *link_version = TFF_Linked_Version();
	SDL_TFF_VERSION(&compile_version); */
	U_LogWrite(LOG_LOG, "SDL_ttf compiled version: %d.%d.%d\n",
			  SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL);
	/* U_LogWrite(LOG_LOG, "SDL_ttf running version: ", link_version->major,
	   link_version->minor, link_version->patch); */
}

inline const char *HU_GetFontError(void) {
	return TTF_GetError();
}

TTF_Font *HU_FontOpen(const char *filename, int size) {
	return TTF_OpenFont(filename, size);
}

// generated surfaces must be freed!
inline SDL_Surface *HU_FontRenderSolid(TTF_Font *font, const char *text,
									   SDL_Color fg) {
	return TTF_RenderText_Solid(font, text, fg);
}

inline void HU_FontClose(TTF_Font *font) {
	TTF_CloseFont(font);
}

inline void HU_FontQuit(void) {
	TTF_Quit();
}

