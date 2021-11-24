#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "glerror.h"
#include "log.h"
#include "config.h"
#include "appwindow.h"
#include "input.h"
#include "render.h"
#include "shader.h"
#include "audio.h"

#define APP_VERSION "1.0.0"

static void cmdargs(int argc, char **argv);
static void usage();
static void signal_handler(int signum);
static void sdl_log_output(void *userdata, int category, SDL_LogPriority priority, const char *message);
static void shutdown();
static int exit_code = 0;
static bool verbose = true;

typedef struct {
	bool config_loaded;
	bool log_opened;
	bool log_closed;
	bool config_closed;
	bool window_created;
} AppState;
AppState app_state = {false,false,false,false,false,};

int main(int argc, char **argv)
{
	cmdargs(argc, argv);
	if (!log_open(LOG_FILE, verbose)) {
		fprintf(stderr, "Failed to open log file for writing, %s", LOG_FILE);
	}
	log_write(LOG_MSG, "Initializing Starship Fleet...\n");
	log_write(LOG_MSG, "Loading configuration file...\n");

	Options options = {
        .window_title = "Starship Fleet",
		.window_size_x = 800,
		.window_size_y = 600,
		.is_fullscreen = false,
		.refresh_rate = 60,
		.vsync_enabled = true,
		.graphics_quality = 6,
	};
	if (!config_load(CONFIG_FILE, &options)) {
		log_write(LOG_MSG, "Configuration parsing error. Using reasonable set of defaults.\n");
	}
	config_close();
	log_write(LOG_MSG, "Configuration parsed successfully.\n");
	log_write(LOG_MSG, "Initialization complete. Elapsed time: %ds\n", 0);

	SDL_Window *window;
	if (!window_init(&window, &options)) {
		log_write(LOG_ERR, "Window initilization failure.\n");
		exit_code = 1;
		return exit_code;
	}
	atexit(shutdown);
    { // short scope for debug context checking
		// need to check if the current context is version 4.3 or greater
		int context_flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
		if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			log_write(LOG_MSG, "OpenGL Debug Context Enabled Successfully.\n");
		}
		glEnable(GL_DEBUG_OUTPUT);
		// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(&gl_debug_callback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
							  GL_TRUE);
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

	GLuint vbo, vao;
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"assets/shaders/triangle_vs.glsl",0},
		{GL_FRAGMENT_SHADER,"assets/shaders/triangle_fs.glsl",0},
	};
	GLuint program;
	program_create(&program, shaders, 2);
	program_use(program);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(0, GLfloat));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(2, GLfloat));
	glEnableVertexAttribArray(1);

	uint64_t start_time, end_time, delta_time;
	const uint64_t frame_delay = 1000 / options.refresh_rate;
	bool running = true;
	while (running) {
		start_time = SDL_GetTicks();
		
		SDL_Event event;
        while (SDL_PollEvent(&event))
        {
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
				window_event_handle(&event);
				break;
			}         
        }
		
	    // static const float clear_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		// glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		r_wireframe(false);
		glLineWidth(1.0f);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		r_wireframe(true);
		glLineWidth(5.0f);
		
		glDrawArrays(GL_TRIANGLES, 3, 6);
		SDL_GL_SwapWindow(window);
		
		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;
		if (frame_delay > delta_time) {
		    SDL_Delay(frame_delay - delta_time);   
		}
	}
	log_write(LOG_MSG, "Exiting application...\n");
	window_close(&window);
	SDL_Quit();
	log_close();
	return exit_code;
}

#define ARGUMENT_QUIET "--quiet"
#define ARGUMENT_NOLOG "--nolog"
#define ARGUMENT_WIDTH "--window-width"
#define ARGUMENT_HEIGHT "--window-height"

void cmdargs(int argc, char **argv)
{
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
				usage();
		}
	}
}

void usage()
{
	printf("Starship Fleet v"APP_VERSION"\n"
		   "Starship Fleet is a spaceship fleet battle game.\n\n"
		   "USAGE:\n\tstarshipfleet [FLAGS] [OPTIONS]\n\n"
           "FLAGS:\n"
	       "    -q, --quiet Suppress IO to stdout and stderr\n\n"
           "OPTIONS:\n");
	exit(1); // okay to exit no initialization done
}

void signal_handler(int signum)
{
	switch (signum) {

	}
}

void sdl_log_output(void *userdata, int category, SDL_LogPriority priority,
					const char *message)
{
	const char *category_buf;
	const char *priority_buf;

	switch (category) {
	case SDL_LOG_CATEGORY_APPLICATION:
		category_buf = "APPLICATION";
		break;
    case SDL_LOG_CATEGORY_ERROR:
		category_buf = "ERROR";
		break;
    case SDL_LOG_CATEGORY_ASSERT:
		category_buf = "ASSERT";
		break;
    case SDL_LOG_CATEGORY_SYSTEM:
	    category_buf = "SYSTEM";
		break;
    case SDL_LOG_CATEGORY_AUDIO:
		category_buf = "AUDIO";
		break;
    case SDL_LOG_CATEGORY_VIDEO:
		category_buf = "VIDEO";
		break;
    case SDL_LOG_CATEGORY_RENDER:
		category_buf = "RENDER";
		break;
    case SDL_LOG_CATEGORY_INPUT:
		category_buf = "INPUT";
		break;
    case SDL_LOG_CATEGORY_TEST:
		category_buf = "TEST";
		break;
	default:
		category_buf = "UNKNOWN";
	}
	
	switch (priority) {
	case SDL_LOG_PRIORITY_VERBOSE:
		priority_buf = "VERBOSE";
		break;
    case SDL_LOG_PRIORITY_DEBUG:
		priority_buf = "DEBUG";
		break;
	case SDL_LOG_PRIORITY_INFO:
		priority_buf = "INFO";
		break;
    case SDL_LOG_PRIORITY_WARN:
		priority_buf = "WARN";
		break;
    case SDL_LOG_PRIORITY_ERROR:
		priority_buf = "ERROR";
		break;
    case SDL_LOG_PRIORITY_CRITICAL:
		priority_buf = "CRITICAL";
		break;
	default:
		priority_buf = "UNKNOWN";
	}
	log_write(LOG_LOG, "SDL:%s:%s:%s\n", category_buf, priority_buf, message);
}

// do any necessary resource management here
void shutdown()
{
	SDL_Quit();
}

