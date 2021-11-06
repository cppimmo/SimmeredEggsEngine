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
	
	SDL_Window *pWindow = NULL;
	SDL_GLContext *pContext = NULL;
	if (!window_init(pWindow, pContext, &options)) {
		log_write(LOG_ERR, "Window initilization failure.\n");
		exit_code = 1;
		return exit_code;
	}
	r_set_gl_callback(&gl_debug_callback, NULL);

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
	glBindVertexArray(&vao);
	glBindBuffer(GL_ARRAY_BUFFER, &vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	bool running = true;
	SDL_Event evt;
	while (running) {
		while (SDL_PollEvent(&evt) != 0) {
		    if (evt.type == SDL_QUIT) {
				running = false;
			}
		}
		static const float clear_color[] = { 0.0f, 1.0f, 0.0f, 1.0f,};
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		SDL_GL_SwapWindow(pWindow);
	}
	
	window_close(pWindow, pContext);
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

// do any necessary resource management here
void shutdown()
{
	SDL_Quit();
}

