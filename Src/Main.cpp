/* =============================================================================
** SimmeredEggsEngine, file: Main.cpp Created 12/6/2021
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
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cstring>

#include "SDL2/SDL.h"
#include "Utility.h"
#include "Log.h"
#include "Options.h"
#include "RenderDebug.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Shader.h"
#include "Sound.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Scene.h"

#define GAME_EXIT_SUCCESS 0
#define GAME_EXIT_FAILURE 1
#define GAME_EXIT(X) \
	exitCode = X; \
	std::exit(exitCode)	\

static void ProcessArguments(int argc, char **argv);
static void ShowUsage(void);
static void HandleSignal(int signalNum);
static void SDL_LogOutput(void *userData, int category,
                          SDL_LogPriority priority, const char *message);
static void Shutdown(void);
static int exitCode = GAME_EXIT_SUCCESS;
static boolean verbose = true;

struct GameState
{
	boolean configLoaded;
	boolean logOpened;
	boolean logClosed;
	boolean configClosed;
	boolean windowCreated;
};
GameState gameState = {false,false,false,false,false,};

int main(int argc, char *argv[]) {
	using namespace SEE;

	ProcessArguments(argc, argv);
	if (!SEE::LogOpen(SEE::LOG_FILE, verbose)) {
		std::fprintf(stderr, "Failed to open log file for writing, %s", SEE::LOG_FILE);
	}
	SEE::LogWrite(SEE::LogType::LOG_MSG, "Initializing %s v%d.%d.%d...\n", ENGINE_NAME,
			   ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR,
			   ENGINE_VERSION_PATCH);
	SEE::LogWrite(SEE::LogType::LOG_MSG, "Loading options file...\n");

	Options options = {
        "Program",
		800,
		600,
		false,
		60,
		true,
		6,
	};
	if (!G_OptionsLoad(OPTIONS_SCRIPT, &options)) {
		SEE::LogWrite(SEE::LogType::LOG_MSG, "Options parsing error. Using reasonable set of defaults.\n");
	}
	G_OptionsClose();
	SEE::LogWrite(SEE::LogType::LOG_MSG, "Options parsed successfully.\n");
	SEE::LogWrite(SEE::LogType::LOG_MSG, "Initialization complete. Elapsed time: %ds\n", 0);

	SDL_Window *window;
    G_SetWindowPtr(&window);
	if (!G_WindowInit(&options)) {
		SEE::LogWrite(SEE::LogType::LOG_ERR, "Window initilization failure.\n");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}
	{
		SDL_version compiled;
		SDL_VERSION(&compiled);
		SEE::LogWrite(SEE::LogType::LOG_LOG, "Compiled with SDL version: %d.%d.%d\n",
				   compiled.major, compiled.minor, compiled.patch);
		SDL_version linked;
		SDL_GetVersion(&linked);
		SEE::LogWrite(SEE::LogType::LOG_LOG, "Linked against SDL version: %d.%d.%d\n",
				   linked.major, linked.minor, linked.patch);
	}
	atexit(Shutdown);
#ifndef NDEBUG
    { // short scope for debug context checking
		// need to check if the current context is version 4.3 or greater
		int contextflags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &contextflags);
		if (contextflags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			SEE::LogWrite(SEE::LogType::LOG_MSG, "OpenGL Debug Context Enabled Successfully.\n");
		}
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(D_GLDebugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
							  GL_TRUE);
	}
#endif
	if (!S_SoundInit()) {
		SEE::LogWrite(SEE::LogType::LOG_ERR, "Failed to init sound system!");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}
	P_SceneSetup(); // configure scenes
	if (!P_SceneInit(SCENE_GAME)) { // load up the initial scene
		SEE::LogWrite(SEE::LogType::LOG_ERR, "Failed to init scene!\n");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}

	uint64_t startTime, endTime, deltaTime = 0;
	const uint64_t frameDelay = 1000 / options.refreshrate;
	boolean running = true;
	while (running) {
		startTime = SDL_GetTicks();

		SDL_Event event;
        while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				} else if (event.key.keysym.sym == SDLK_F11) {
					G_WindowSetFullscreen(true);
				}
				OnKeyDown(&event.key.keysym);
				break;
			case SDL_KEYUP:
				OnKeyUp(&event.key.keysym);
				break;
			case SDL_TEXTEDITING:
				OnTextEdit(&event.edit);
				break;
			case SDL_TEXTINPUT:
				OnTextInput(&event.text);
				break;
			case SDL_MOUSEMOTION:
				OnMouseMotion(&event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				OnMouseButtonDown(&event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				OnMouseButtonUp(&event.button);
				break;
			case SDL_MOUSEWHEEL:
				OnMouseWheel(&event.wheel);
				break;
			case SDL_CONTROLLERAXISMOTION:
				OnControllerAxisMotion(&event.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				OnControllerButtonDown(&event.cbutton);
				break;
			case SDL_CONTROLLERBUTTONUP:
				OnControllerButtonUp(&event.cbutton);
				break;
			case SDL_AUDIODEVICEADDED:

				break;
			case SDL_AUDIODEVICEREMOVED:

				break;
			case SDL_CONTROLLERDEVICEADDED:
				OnControllerDeviceAdded(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				OnControllerDeviceRemoved(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				OnControllerDeviceRemapped(&event.cdevice);
				break;
			case SDL_USEREVENT:
				break;
			case SDL_WINDOWEVENT:
				G_WindowHandleEvent(&event);
				break;
			}
        }
		P_SceneUpdate(P_GetActiveScene(), (GLfloat)deltaTime);
		P_SceneRender(P_GetActiveScene(), (GLfloat)deltaTime);
		G_WindowSwap();

		endTime = SDL_GetTicks();
		deltaTime = endTime - startTime;
		if (frameDelay > deltaTime) {
		    SDL_Delay(frameDelay - deltaTime);
		}
	}
	SEE::LogWrite(SEE::LogType::LOG_MSG, "Exiting application...\n");
	// destroy the last active scene
	P_SceneDestroy(P_GetActiveScene());
	S_SoundDestroy();
	G_WindowClose();
	SDL_Quit();
	U_LogClose();
	return exitcode;
}

#define ARGUMENT_QUIET "--quiet"
#define ARGUMENT_NOLOG "--nolog"
#define ARGUMENT_WIDTH "--window-width"
#define ARGUMENT_HEIGHT "--window-height"

void ProcessArguments(int argc, char **argv) {
	// use continue; to shift arguments for option values
	for (int i = 1; i <= argc - 1; ++i) {
	    printf("Testing argument[%d]: %s\n", i, argv[i]);
		if (strcmp(argv[i], ARGUMENT_QUIET) == 0) {
			verbose = false;
		} else if (strcmp(argv[i], ARGUMENT_NOLOG) == 0) {
			// disable log file output
		} else if (strcmp(argv[i], ARGUMENT_WIDTH) == 0) {
			// set window width
	    } else if (strcmp(argv[i], ARGUMENT_HEIGHT) == 0) {
			// set window height
		} else {
			if (argc > 1)
				ShowUsage();
		}
	}
}

inline void ShowUsage(void) {
	/* printf("SimmeredEggsEngine v"GAME_VERSION"\n"
		   "blah blah blah.\n\n"
		   "usage:\n\tSimmeredEggsEngine [FLAGS] [OPTIONS]\n\n"
           "FLAGS:\n"
	       "    -q, --quiet Suppress IO to stdout and stderr\n\n"
           "OPTIONS:\n"); */
	exit(1); // okay to exit no initialization done
}

inline void HandleSignal(int signum) {
	switch (signum) {

	}
}

void SDL_LogOutput(void *userdata, int category, SDL_LogPriority priority,
				   const char *message) {
	const char *categorybuf;
	const char *prioritybuf;

	switch (category) {
	case SDL_LOG_CATEGORY_APPLICATION:
		categorybuf = "APPLICATION";
		break;
    case SDL_LOG_CATEGORY_ERROR:
		categorybuf = "ERROR";
		break;
    case SDL_LOG_CATEGORY_ASSERT:
		categorybuf = "ASSERT";
		break;
    case SDL_LOG_CATEGORY_SYSTEM:
	    categorybuf = "SYSTEM";
		break;
    case SDL_LOG_CATEGORY_AUDIO:
		categorybuf = "AUDIO";
		break;
    case SDL_LOG_CATEGORY_VIDEO:
		categorybuf = "VIDEO";
		break;
    case SDL_LOG_CATEGORY_RENDER:
		categorybuf = "RENDER";
		break;
    case SDL_LOG_CATEGORY_INPUT:
		categorybuf = "INPUT";
		break;
    case SDL_LOG_CATEGORY_TEST:
		categorybuf = "TEST";
		break;
	default:
		categorybuf = "UNKNOWN";
	}

	switch (priority) {
	case SDL_LOG_PRIORITY_VERBOSE:
		prioritybuf = "VERBOSE";
		break;
    case SDL_LOG_PRIORITY_DEBUG:
		prioritybuf = "DEBUG";
		break;
	case SDL_LOG_PRIORITY_INFO:
		prioritybuf = "INFO";
		break;
    case SDL_LOG_PRIORITY_WARN:
		prioritybuf = "WARN";
		break;
    case SDL_LOG_PRIORITY_ERROR:
		prioritybuf = "ERROR";
		break;
    case SDL_LOG_PRIORITY_CRITICAL:
		prioritybuf = "CRITICAL";
		break;
	default:
		prioritybuf = "UNKNOWN";
	}
	SEE::LogWrite(SEE::LogType::LOG_LOG, "SDL:%s:%s:%s\n", categorybuf, prioritybuf, message);
}

// do any necessary resource management here
void Shutdown(void) {
	SDL_Quit();
}

