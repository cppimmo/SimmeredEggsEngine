#include "font.h"
#include "log.h"

bool font_init()
{
	return (TTF_Init() == -1) ? false : true;
}

void font_info()
{
	/* SDL_version compile_version;
	const SDL_version *link_version = TFF_Linked_Version();
	SDL_TFF_VERSION(&compile_version); */
	log_write(LOG_LOG, "SDL_ttf compiled version: %d.%d.%d\n", SDL_TTF_MAJOR_VERSION,
			  SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL);
	/* log_write(LOG_LOG, "SDL_ttf running version: ", link_version->major,
	   link_version->minor, link_version->patch); */
}

inline char *font_get_error()
{
	return TTF_GetError();
}

TTF_Font *font_open(const char *filename, int size)
{
	return TTF_OpenFont(filename, size);
}

// generated surfaces must be freed!
inline SDL_Surface *font_render_solid(TTF_Font *font, const char *text, SDL_Color fg)
{
	return TTF_RenderText_Solid(font, text, fg);
}

inline void font_close(TTF_Font *font)
{
	TTF_CloseFont(font);
}

inline void font_quit()
{
	TTF_Quit();
}
