#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "d_glerror.h"
#include "u_log.h"
#include "g_config.h"
#include "g_window.h"
#include "g_input.h"
#include "r_render.h"
#include "r_shader.h"
#include "s_sound.h"
#include "r_vertexarray.h"
#include "r_vertexbuffer.h"
#include "p_scene.h"

#define GAME_VERSION "1.0.0"

static void ProcessArguments(int argc, char **argv);
static void ShowUsage(void);
static void HandleSignal(int signum);
static void SDL_LogOutput(void *userdata, int category,
                          SDL_LogPriority priority, const char *message);
static void Shutdown(void);
static int exitcode = 0;
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
	if (!G_WindowInit(&window, &config)) {
		U_LogWrite(LOG_ERR, "Window initilization failure.\n");
		exitcode = 1;
		return exitcode;
	}
	atexit(Shutdown);
    { // short scope for debug context checking
		// need to check if the current context is version 4.3 or greater
		int context_flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
		if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			U_LogWrite(LOG_MSG, "OpenGL Debug Context Enabled Successfully.\n");
		}
		glEnable(GL_DEBUG_OUTPUT);
		// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(D_glDebugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
							  GL_TRUE);
	}

	// configure scenes
	P_SceneSetup();
	if (!P_SceneInit(SCENE_GAME)) {
		U_LogWrite(LOG_ERR, "Failed to init scene!\n");
	}

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	static const GLfloat vertices[6][5] = {
		{-0.90f,-0.90f, 1.0f, 0.0f, 0.0f},
		{ 0.85f,-0.90f, 0.0f, 1.0f, 0.0f},
		{-0.90f, 0.85f, 0.0f, 0.0f, 1.0f},
		{ 0.90f,-0.85f, 1.0f, 0.0f, 0.0f},
		{ 0.90f, 0.90f, 0.0f, 1.0f, 0.0f},
		{-0.85f, 0.90f, 0.0f, 0.0f, 1.0f},
	};

	struct vertexarray_t vao;
	if (!R_CreateVertexArray(&vao))
		U_LogWrite(LOG_LOG, "FAILED TO CREATE VAO");
	struct vertexbuffer_t vbo;
	if (!R_CreateVertexBuffer(&vbo, GL_ARRAY_BUFFER, GL_FALSE))
		U_LogWrite(LOG_LOG, "FAILED TO CREATE VBO");
    R_VertexBufferStorage(&vbo, sizeof(vertices), vertices);

	struct shader_info_t shaders[] = {
		{GL_VERTEX_SHADER,"assets/shaders/triangle_vs.glsl",0},
		{GL_FRAGMENT_SHADER,"assets/shaders/triangle_fs.glsl",0},
	};
	GLuint program;
	R_CreateProgram(&program, shaders, 2);
    R_UseProgram(program);

	R_BindVertexArray(&vao);
	R_BindVertexBuffer(&vbo);

	R_VertexAttribPtr(&vao, &vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(0, GLfloat));
	R_VertexAttribEnable(0);
	R_VertexAttribPtr(&vao, &vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(2, GLfloat));
	R_VertexAttribEnable(1);

	uint64_t start_time, end_time, delta_time;
	const uint64_t frame_delay = 1000 / config.refreshrate;
	boolean running = true;
	while (running) {
		start_time = SDL_GetTicks();

		SDL_Event event;
        while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				on_key_down(&event.key.keysym);
				break;
			case SDL_KEYUP:
				on_key_up(&event.key.keysym);
				break;
			case SDL_TEXTEDITING:
				on_text_edit(&event.edit);
				break;
			case SDL_TEXTINPUT:
				on_text_input(&event.text);
				break;
			case SDL_MOUSEMOTION:
				on_mouse_motion(&event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				on_mouse_button_down(&event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				on_mouse_button_up(&event.button);
				break;
			case SDL_MOUSEWHEEL:
				on_mouse_wheel(&event.wheel);
				break;
			case SDL_CONTROLLERAXISMOTION:
				on_controller_axis_motion(&event.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				on_controller_button_down(&event.cbutton);
				break;
			case SDL_CONTROLLERBUTTONUP:
				on_controller_button_up(&event.cbutton);
				break;
			case SDL_AUDIODEVICEADDED:

				break;
			case SDL_AUDIODEVICEREMOVED:

				break;
			case SDL_CONTROLLERDEVICEADDED:
				on_controller_device_added(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				on_controller_device_removed(&event.cdevice);
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				on_controller_device_remapped(&event.cdevice);
				break;
			case SDL_USEREVENT:
				break;
			case SDL_WINDOWEVENT:
				G_WindowHandleEvent(&event);
				break;
			}
        }
	    /* static const GLfloat clear_color[] = { 1.0f, 1.0f, 0.0f, 0.0f };
		GLint drawbuf_id = 0;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &drawbuf_id);
		glClearBufferfv(GL_COLOR, 0, clear_color); */
		P_SceneUpdate(P_GetActiveScene(), (GLfloat)delta_time);
		P_SceneRender(P_GetActiveScene(), (GLfloat)delta_time);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		R_Wireframe(false);
		glLineWidth(1.0f);

		R_BindVertexArray(&vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		R_Wireframe(true);
		glLineWidth(5.0f);

		glDrawArrays(GL_TRIANGLES, 3, 6);

		G_WindowSwap(&window);

		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;
		if (frame_delay > delta_time) {
		    SDL_Delay(frame_delay - delta_time);
		}
	}
	U_LogWrite(LOG_MSG, "Exiting application...\n");
	R_DeleteProgram(program);
	R_DeleteVertexArray(&vao);
	R_DeleteVertexBuffer(&vbo);
	P_SceneDestroy(P_GetActiveScene());
	G_WindowClose(&window);
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

void HandleSignal(int signum) {
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

