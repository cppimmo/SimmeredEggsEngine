#include "g_window.h"
#include "u_log.h"

#define WINDOW_ICON "assets/icon.bmp"

static struct windowstate_t windowstate;
static SDL_GLContext context;

boolean G_WindowInit(SDL_Window **window, struct config_t *const config) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		U_LogWrite(LOG_ERR, "SDL_Init failure: %s\n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow(config->title, SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED, config->sizex,
							   config->sizey,
							   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (*window == NULL) {
		U_LogWrite(LOG_ERR, "SDL_CreateWindow() failure: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *icon = SDL_LoadBMP(WINDOW_ICON);
	if (icon != NULL)
		SDL_SetWindowIcon(*window, icon);
	SDL_FreeSurface(icon);

	G_WindowAttribs(4, 2, true);
    context = SDL_GL_CreateContext(*window);
	if (context == NULL) {
		U_LogWrite(LOG_ERR, "SDL_GL_CreateContext() failure: %s\n", SDL_GetError());
		return false;
	}
	if (SDL_GL_MakeCurrent(*window, context) < 0) {
		U_LogWrite(LOG_ERR, "SDL_GL_MakeCurrent() failure: %s\n", SDL_GetError());
		return false;
	}
	SDL_GL_SetSwapInterval(((config->vsync) ? 1 : 0));

	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK) {
		U_LogWrite(LOG_ERR, "glewInit() error: %s\n", glewGetErrorString(glew_error));
		return false;
	}
	G_WindowViewport(0, 0, config->sizex, config->sizey);

	if (glGetString(GL_VENDOR) != 0)
        U_LogWrite(LOG_LOG, "GL_VENDOR=%s\n", glGetString(GL_VENDOR));
    if (glGetString(GL_RENDERER) != 0)
        U_LogWrite(LOG_LOG, "GL_RENDERER=%s\n", glGetString(GL_RENDERER));
    if (glGetString(GL_VERSION) != 0)
        U_LogWrite(LOG_LOG, "GL_VERSION=%s\n", glGetString(GL_VERSION));
    if (glGetString(GL_SHADING_LANGUAGE_VERSION) != 0) {
        U_LogWrite(LOG_LOG, "GL_SHADING_LANGUAGE_VERSION=%s\n",
				   glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	U_LogWrite(LOG_MSG, "gl3w loaded successfully; version: %s\n",
               glewGetString(GLEW_VERSION));
	return true;
}

inline boolean G_WindowAttribs(const int glmajor, const int glminor,
							   boolean doublebuffer) {
	// relevant documentation: https://wiki.libsdl.org/SDL_GLattr
	SDL_GL_LoadLibrary(NULL);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glmajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glminor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doublebuffer);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	return true;
}

int G_WindowGetAttrib(SDL_GLattr attrib) {
	int temp;
    SDL_GL_GetAttribute(attrib, &temp);
	return temp;
}

void G_WindowHandleEvent(const SDL_Event *event) {
	switch (event->window.event) {
	case SDL_WINDOWEVENT_SHOWN:
	    windowstate.visible = true;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
		windowstate.visible = false;
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        break;
    case SDL_WINDOWEVENT_MOVED:
		// G_WindowViewport(event->window.data1, event->window.data2,
		//	windowstate.posx, windowstate.posy);
        break;
    case SDL_WINDOWEVENT_RESIZED:
		G_WindowViewport(windowstate.posx,
						windowstate.posy,
						event->window.data1, event->window.data2);
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
		G_WindowViewport(windowstate.posx,
						windowstate.posy,
						event->window.data1, event->window.data2);
        break;
    case SDL_WINDOWEVENT_MINIMIZED:
		windowstate.maximized = false;
		windowstate.minimized = true;
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
		windowstate.minimized = false;
		windowstate.maximized = true;
        break;
    case SDL_WINDOWEVENT_RESTORED:
        break;
    case SDL_WINDOWEVENT_ENTER:
		windowstate.mouseover = true;
        break;
    case SDL_WINDOWEVENT_LEAVE:
		windowstate.mouseover = false;
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
		windowstate.focused = true;
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
		windowstate.focused = false;
		break;
    case SDL_WINDOWEVENT_CLOSE:
        break;
	}
}

struct windowstate_t *G_WindowGetState() {
	return &windowstate;
}

void G_WindowViewport(GLint posx, GLint posy, GLint width, GLint height) {
	windowstate.posx = posx;
	windowstate.posy = posy;
	windowstate.sizex = width;
	windowstate.sizey = height;
	glViewport(posx, posy, width, height);
}

void G_WindowSwap(SDL_Window **window) {
	SDL_GL_SwapWindow(*window);
}

inline boolean G_WindowClose(SDL_Window** window) {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(*window);
	return true;
}

