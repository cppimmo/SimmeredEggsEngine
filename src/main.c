#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "log.h"
#include "config.h"
#include "appwindow.h"
#include "render.h"
#include "glerror.h"
#include "SDL2/SDL.h"

#include "shader.h"

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
	/* SIGABRT, SIGFPE,	SIGILL,
	SIGINT,	SIGSEGV, SIGTERM */
	if (!log_open(LOG_FILE, verbose)) {
		fprintf(stderr, "Failed to open log file for writing, %s", LOG_FILE);
	}
	log_write(LOG_MSG, "Initializing Starship Fleet...\n");
	log_write(LOG_MSG, "Loading configuration file...\n");

	Options options = {
        .window_title = "Starship Fleet",
		.window_size_x = 800,
		.window_size_y = 600,
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

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		log_write(LOG_ERR, "SDL_Init failure: %s\n", SDL_GetError());
		return false;
	}
	atexit(shutdown);
	
	SDL_Window *p_window = SDL_CreateWindow("Starship Fleet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	/*if (!window_init(p_window, &p_context, &options)) {
		log_write(LOG_ERR, "Window initilization failure.\n");
		exit_code = 1;
		return exit_code;
	} */
	// SDL_LogSetOutputFunction(&sdl_log_output, NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GLContext context = SDL_GL_CreateContext(p_window);

	SDL_GL_SetSwapInterval(1);
  
	glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	// opengl test code
	static const float vertices[6][2] = {
		{-0.90f,-0.90f},
		{ 0.85f,-0.90f},
		{-0.90f, 0.85f},
		{ 0.90f,-0.85f},
		{ 0.90f, 0.90f},
		{-0.85f, 0.90f},
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
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	uint64_t start_time, end_time, delta_time;
	const uint64_t frame_delay = 1000 / options.refresh_rate;
	bool running = true;
	while (running) {
		start_time = SDL_GetTicks();
		
		SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type = SDL_KEYDOWN) {
			    switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				default:
					break;
				}
			}
        }		
	    static const float clear_color[] = { 1.0f, 1.0f, 0.0f, 0.0f, };
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		SDL_GL_SwapWindow(p_window);
		
		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;
		if (frame_delay > delta_time) {
		    SDL_Delay(frame_delay - delta_time);   
		}
	}
	
	// window_close(p_window, &p_context);
	SDL_Quit();
	log_close();
	return exit_code;
}

void cmdargs(int argc, char **argv)
{
	// use continue; to shift arguments for option values
	for (int i = 1; i <= argc - 1; ++i) {
	    printf("Testing argument[%d]: %s\n", i, argv[i]);
		if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0) {
			verbose = false;
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

