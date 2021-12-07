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
#include "g_window.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

/*
 * The following code was implemented simarly to the resources listed below:
 * https://www.gamedev.net/forums/topic/385949-taking-sdlopengl-screenshot/
 * https://github.com/rcarmo/homeworld/blob/master/src/SDL/screenshot.c
 * https://www.gamedev.net/forums/topic/303295-sdl-opengl-screenshot-problems/
 */

static void AppendScreenshotFilename(char *path);

static void AppendScreenshotFilename(char *path) {
	FILE *image;
	char imagepath[256 + 1], imagename[256];

	time_t now;
	struct tm timedata;

	unsigned int attempts = 0,
		sleeptime_s = 1,
		maxattempts_s = 10;
	while (1) {
		time(&now);
		timedata = *localtime(&now);

		strftime(imagename, sizeof(imagename), "shot_%Y%m%d_%H%M%S_%Z.bmp", &timedata);

		strcpy(imagepath, path);
		strcat(imagepath, imagename);

		// presumed good if unable to open
		if ((image = fopen(imagepath, "r")) == NULL)
			break;

		fclose(image);
		++attempts;
		sleep(sleeptime_s);

		if (attempts > maxattempts_s / sleeptime_s) {
			strcpy(imagename, "most_recent_screenshot.bmp");
			break;
		}
	}

	strcat(path, imagename);
}

/* doesn't matter if this function fails just print messages based on release
 * (catastrophic failures probably are relevant!) check for NULL pointer! */
void U_TakeScreenshot(void) {
	struct windowstate_t *windowstate = G_WindowGetState();
	if (windowstate == NULL) {
#ifdef SCREENSHOT_VERBOSE
		U_LogWrite(LOG_ERR,
				   "U_TakeScreenshot(): couldn't retrieve windowstat!\n");
#endif
		return;
	}
	const int width = windowstate->sizex;
	const int height = windowstate->sizey;

	// use C library time for timestamp in filename
	const char *filename = "screenshot.bmp";
	// AppendScreenshotFilename(filename);
	if (filename == NULL) {
#ifdef SCREENSHOT_VERBOSE
		U_LogWrite(LOG_ERR, "U_TakeScreenshot(): no filename!\n");
#endif
		return;
	}

	SDL_Surface *screen = SDL_CreateRGBSurface(SDL_SWSURFACE, width,
											   height, 32, 0x0000ff,
											   0x00ff00, 0xff0000, 0x000000);
	if (screen == NULL) {
#ifdef SCREENSHOT_VERBOSE
		U_LogWrite(LOG_ERR, "U_TakeScreenshot(): screen is NULL!\n");
#endif
	    return;
	}

	unsigned char *pixels = (unsigned char*)U_Malloc(width
													 * height * 4);
	unsigned char *pixelsbuf = (unsigned char*)U_Malloc(width
														* height * 4);
    if (pixels == NULL || pixelsbuf == NULL) {
#ifdef SCREENSHOT_VERBOSE
		U_LogWrite(LOG_ERR,
					"U_TakeScreenshot(): pixels or pixelsbuf are NULL!\n");
#endif
	    return;
	}
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	memcpy(pixelsbuf, pixels, width * height * 4);
	pixelsbuf = pixels;
	// flip image
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j)
			pixels[width * (height - i) + j] =
				pixelsbuf[width * i + j];
	}
	screen->pixels = pixels;
	// result doesn't matter at this point; just need to free this memory
	const int result = SDL_SaveBMP(screen, filename);
#ifdef SCREENSHOT_VERBOSE
	if (result < 0)
		U_LogWrite(LOG_ERR, "U_TakeScreenshot(): screenshot failed!\n");
	else
		U_LogWrite(LOG_MSG, "U_TakeScreenshot(): screenshot succeeded!\n");
#endif
    // this function below is causing segfaults
	SDL_FreeSurface(screen);
	screen = 0;

    free(pixels);
	free(pixelsbuf);
	pixels = 0;
	pixelsbuf = 0;
}

