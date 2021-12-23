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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#ifdef __linux__
#include <linux/limits.h>
#elif defined(__unix__) && !defined(__linux__)

#elif defined(_WIN32)

#endif

/*
 * The following code was implemented simarly to the resources listed below:
 * https://www.gamedev.net/forums/topic/385949-taking-sdlopengl-screenshot/
 * https://github.com/rcarmo/homeworld/blob/master/src/SDL/screenshot.c
 * https://www.gamedev.net/forums/topic/303295-sdl-opengl-screenshot-problems/
 */

static void ScreenshotFilename(char *filename);

static void ScreenshotFilename(char *filename)
{
#ifdef __linux__
	char imagepath[PATH_MAX + 1], imagename[256];
#elif defined(__unix__) && !defined(__linux__)
	char imagepath[_POSIX_PATH_MAX + 1], imagename[256];
#elif defined(_WIN32)
	char imagepath[MAX_PATH + 1], imagename[256];
#endif
	time_t now;
	struct tm timedata;
	time(&now);
	timedata = *localtime(&now);
	if (now == NULL)
		return;

	strcpy(filename, ""); // make sure the is given a value
	strftime(imagename, sizeof(imagename), "shot_%Y%m%d_%H%M%S_%Z.bmp", &timedata);
    strcpy(imagepath, filename);
	strcat(imagepath, imagename);
	strcat(filename, imagename);
}

/* doesn't matter if this function fails just print messages based on release
 * (catastrophic failures probably are relevant!) check for NULL pointer! */
void SEE::TakeScreenshot(void)
{
	const WindowState *windowstate = G_WindowGetState();
		if (windowstate == NULL) {
#ifdef SCREENSHOT_VERBOSE
		SEE::LogWrite(SEE::LogType::LOG_ERR,
				   "U_TakeScreenshot(): couldn't retrieve windowstat!\n");
#endif
		return;
	}
	const int width = windowstate->sizex;
	const int height = windowstate->sizey;

	// use C library time for timestamp in filename
#ifdef __linux__
	char filename[PATH_MAX + 1 + 256];
#elif defined(__unix__) && !defined(__linux__)
	char filename[_POSIX_PATH_MAX + 1 + 256];
#elif defined(_WIN32)
	char filename[MAX_PATH + 1 + 256];
#endif
    ScreenshotFilename(filename);
	if (filename == NULL) {
#ifdef SCREENSHOT_VERBOSE
		SEE::LogWrite(SEE::LogType::LOG_ERR, "U_TakeScreenshot(): no filename!\n");
#endif
		return;
	}

	Uint32 rmask, gmask, bmask, amask = 0x000000;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff0000;
	gmask = 0x00ff00;
	bmask = 0x0000ff;
#else
	rmask = 0x0000ff;
	gmask = 0x00ff00;
	bmask = 0xff0000;
#endif
	const unsigned int colorbytes = 4;
	const unsigned int bitsperpixel = 32;
	SDL_Surface *temp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
											 bitsperpixel, rmask, gmask, bmask, amask);
	SDL_Surface *image = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
											  bitsperpixel, rmask, gmask, bmask, amask);
	if (temp == NULL || image == NULL) {
#ifdef SCREENSHOT_VERBOSE
		SEE::LogWrite(SEE::LogType::LOG_ERR, "U_TakeScreenshot(): temp/image is NULL!\n");
#endif
		return;
	}
	// glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	for (int i = 0; i < height; ++i) {
		memcpy((char *)temp->pixels + colorbytes * width * i, (char *)image->pixels
			   + colorbytes * width * (height - i), colorbytes * width);
	}
	memcpy(image->pixels, temp->pixels, width * height * 4);
	const int result = SDL_SaveBMP(temp, filename);
#ifdef SCREENSHOT_VERBOSE
	if (result < 0) {
		SEE::LogWrite(SEE::LogType::LOG_ERR, "U_TakeScreenshot(): screenshot failed!\n");
    }
	else {
		SEE::LogWrite(SEE::LogType::LOG_MSG, "U_TakeScreenshot(): screenshot succeeded!\n");
    }
#endif
	SDL_FreeSurface(image);
	SDL_FreeSurface(temp);
}

