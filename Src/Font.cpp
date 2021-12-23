/* =============================================================================
** SimmeredEggsEngine, file: Font.cpp Created 12/6/2021
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
#include "Font.h"
#include "Log.h"

boolean HU_FontInit(void) {
	return (TTF_Init() == -1) ? false : true;
}

void HU_FontInfo(void) {
	/* SDL_version compile_version;
	const SDL_version *link_version = TFF_Linked_Version();
	SDL_TFF_VERSION(&compile_version); */
	SEE::LogWrite(SEE::LogType::LOG_LOG, "SDL_ttf compiled version: %d.%d.%d\n",
			  SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL);
	/* SEE::LogWrite(SEE::LogType::LOG_LOG, "SDL_ttf running version: ", link_version->major,
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

