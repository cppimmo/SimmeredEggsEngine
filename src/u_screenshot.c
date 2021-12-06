/* =============================================================================
** SimmeredEggsEngine, file: u_screenshot.c Created 12/6/2021
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
#include "u_screenshot.h"
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "u_log.h"
#include "u_utility.h"

/* doesn't matter if this function fails just print messages based on release
 * (catastrophic failures probably are relevant!) */
void U_TakeScreenShot(void) {
	/*
	// use C library time for timestap in filename
	const char *filename = "screenshot.bmp";

	SDL_Surface *screen = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, 0x0000ff, 0x00ff00, 0xff0000, 0x000000);
	if (screen == NULL) {

	    return;
	}

	unsigned int *pixels = NULL;
	unsigned int *pixelsbuf = NULL;
	if (pixels == NULL || pixelsbuf == NULL) {

	    return;
	}

	glRealPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	pixelsbuf = pixels;
	for (int i = 0; i <= width * height; ++i) {
		pixels = pixelsbuf[width * height - i];
	}

	screen->pixels = pixels;
	// result doesn't matter at this point; just need to free this memory
	const int result = SDL_SaveBMP(screen, filename);
#ifndef NDEBUG
	if (result < 0) {

	}
#endif
	SDL_FreeSurface(screen);
	screen = 0;

	U_Free(pixels);
	U_Free(pixelsbuf);

	pixels = 0;
	pixelsbuf = 0;
	*/
}

