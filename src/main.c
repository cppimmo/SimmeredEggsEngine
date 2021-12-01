#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "d_glerror.h"
#include "u_log.h"
#include "g_config.h"
#include "g_window.h"
#include "i_input.h"
#include "r_render.h"
#include "r_shader.h"
#include "s_sound.h"
#include "r_vertexarray.h"
#include "r_vertexbuffer.h"
#include "p_scene.h"

#define GAME_VERSION "1.0.0"
#define GAME_EXIT_SUCCESS 0
#define GAME_EXIT_FAILURE 1
#define GAME_EXIT(X) \
	exitcode = X; \
	return exitcode \

static void ProcessArguments(int argc, char **argv);
static void ShowUsage(void);
static void HandleSignal(int signum);
static void SDL_LogOutput(void *userdata, int category,
                          SDL_LogPriority priority, const char *message);
static void Shutdown(void);
static int exitcode = GAME_EXIT_SUCCESS;
static boolean verbose = true;

struct gamestate_t {
	boolean configloaded;
	boolean logopened;
	boolean logclosed;
	boolean configclosed;
	boolean windowcreated;
};
struct gamestate_t gamestate = {false,false,false,false,false,};

int main(int argc, char **argv) {
	ProcessArguments(argc, argv);
	if (!U_LogOpen(LOG_FILE, verbose)) {
		fprintf(stderr, "Failed to open log file for writing, %s", LOG_FILE);
	}
	U_LogWrite(LOG_MSG, "Initializing Starship Fleet...\n");
	U_LogWrite(LOG_MSG, "Loading configuration file...\n");

	struct config_t config = {
        .title = "Starship Fleet",
		.sizex = 800,
		.sizey = 600,
		.fullscreen = false,
		.refreshrate = 60,
		.vsync = true,
		.quality = 6,
	};
	if (!G_ConfigLoad(CONFIG_FILE, &config)) {
		U_LogWrite(LOG_MSG, "Configuration parsing error. Using reasonable set of defaults.\n");
	}
	G_ConfigClose();
	U_LogWrite(LOG_MSG, "Configuration parsed successfully.\n");
	U_LogWrite(LOG_MSG, "Initialization complete. Elapsed time: %ds\n", 0);

	SDL_Window *window;
    G_SetWindowPtr(&window);
	if (!G_WindowInit(&config)) {
		U_LogWrite(LOG_ERR, "Window initilization failure.\n");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}
	atexit(Shutdown);
    { // short scope for debug context checking
		// need to check if the current context is version 4.3 or greater
		int contextflags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &contextflags);
		if (contextflags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			U_LogWrite(LOG_MSG, "OpenGL Debug Context Enabled Successfully.\n");
		}
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(D_glDebugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
							  GL_TRUE);
	}
	if (!S_SoundInit()) {
		U_LogWrite(LOG_ERR, "Failed to init sound system!");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}
	P_SceneSetup(); // configure scenes
	if (!P_SceneInit(SCENE_GAME)) { // load up the initial scene
		U_LogWrite(LOG_ERR, "Failed to init scene!\n");
		GAME_EXIT(GAME_EXIT_FAILURE);
	}

	uint64_t starttime, endtime, deltatime = 0;
	const uint64_t framedelay = 1000 / config.refreshrate;
	boolean running = true;
	while (running) {
		starttime = SDL_GetTicks();

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
				I_OnKeyDown(&event.key.keysym);
				break;
			case SDL_KEYUP:
				I_OnKeyUp(&event.key.keysym);
				break;
			case SDL_TEXTEDITING:
				I_OnTextEdit(&event.edit);
				break;
			case SDL_TEXTINPUT:
				I_OnTextInput(&event.text);
				break;
			case SDL_MOUSEMOTION:
				I_OnMouseMotion(&event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				I_OnMouseButtonDown(&event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				I_OnMouseButtonUp(&event.button);
				break;
			case SDL_MOUSEWHEEL:
				I_OnMouseWheel(&event.wheel);
				break;
			case SDL_CONTROLLERAXISMOTION:
				I_OnControllerAxisMotion(&event.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				I_OnControllerButtonDown(&event.cbutton);
				break;
			case SDL_CONTROLLERBUTTONUP:
				I_OnControllerButtonUp(&event.cbutton);
				break;
			case SDL_AUDIODEVICEADDED:

				break;
			case SDL_AUDIODEVICEREMOVED:

				break;
			case SDL_CONTROLLERDEVICEADDED:
				I_OnControllerDeviceAdded(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				I_OnControllerDeviceRemoved(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				I_OnControllerDeviceRemapped(&event.cdevice);
				break;
			case SDL_USEREVENT:
				break;
			case SDL_WINDOWEVENT:
				G_WindowHandleEvent(&event);
				break;
			}
        }
		P_SceneUpdate(P_GetActiveScene(), (GLfloat)deltatime);
		P_SceneRender(P_GetActiveScene(), (GLfloat)deltatime);
		G_WindowSwap();

		endtime = SDL_GetTicks();
		deltatime = endtime - starttime;
		if (framedelay > deltatime) {
		    SDL_Delay(framedelay - deltatime);
		}
	}
	U_LogWrite(LOG_MSG, "Exiting application...\n");
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
	printf("Starship Fleet v"GAME_VERSION"\n"
		   "Starship Fleet is a spaceship fleet battle game.\n\n"
		   "usage:\n\tstarshipfleet [FLAGS] [OPTIONS]\n\n"
           "FLAGS:\n"
	       "    -q, --quiet Suppress IO to stdout and stderr\n\n"
           "OPTIONS:\n");
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
	U_LogWrite(LOG_LOG, "SDL:%s:%s:%s\n", categorybuf, prioritybuf, message);
}

// do any necessary resource management here
void Shutdown(void) {
	SDL_Quit();
}

