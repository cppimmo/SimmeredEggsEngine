#include "appwindow.h"
#include "log.h"

bool window_init(SDL_Window *pWindow, SDL_GLContext *pContext,
				 const Options *const pOptions)
{
	window_attribs(3, 3, true);
	pWindow = SDL_CreateWindow("Starship Fleet", SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	if (pWindow == NULL) {
		log_write(LOG_ERR, "SDL_CreateWindow() failure: %s\n", SDL_GetError());
		return false;
	}
	pContext = SDL_GL_CreateContext(pWindow);
	if (pContext == NULL) {
		log_write(LOG_ERR, "SDL_GL_CreateContext() failure: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_GL_MakeCurrent(pWindow, pContext) < 0) {
		log_write(LOG_ERR, "SDL_GL_MakeCurrent() failure: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK) {
		log_write(LOG_ERR, "glewInit() error: %s\n", glewGetErrorString(glew_error));
		return false;
	}
	// log_write(LOG_MSG, "gl3w loaded successfully; version: %s\n", glewGetString(GLEW_VERSION));
	return true;
}

bool window_attribs(int glVersionMajor, int glVersionMinor, bool doubleBuffer)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// set opengl version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glVersionMajor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glVersionMinor);
	// use double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doubleBuffer);
	return true;
}

void window_event_handle(const SDL_Event *pEvent)
{
	if (pEvent->type == SDL_WINDOWEVENT) {
		switch (pEvent->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
	        window_state.is_visible = true;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
			window_state.is_visible = false;
            break;
        case SDL_WINDOWEVENT_EXPOSED:		   
            break;
        case SDL_WINDOWEVENT_MOVED:
			window_state.window_pos_x = pEvent->window.data1;
			window_state.window_pos_y = pEvent->window.data2;
            break;
        case SDL_WINDOWEVENT_RESIZED:
			window_state.window_size_x = pEvent->window.data1;
			window_state.window_size_y = pEvent->window.data2;
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
			window_state.window_size_x = pEvent->window.data1;
			window_state.window_size_y = pEvent->window.data2;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
			window_state.window_maximized = false;
			window_state.window_minimized = true;
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
			window_state.window_minimized = false;
			window_state.window_maximized = true;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            break;
        case SDL_WINDOWEVENT_ENTER:
			window_state.is_mouse_in_window = true;
            break;
        case SDL_WINDOWEVENT_LEAVE:
			window_state.is_mouse_in_window = false;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
			window_state.is_window_focus = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
			window_state.is_window_focus = false;
			break;
        case SDL_WINDOWEVENT_CLOSE:
            break;
		}
	}
}

WindowState *window_get_state()
{
	return &window_state;
}

inline bool window_close(SDL_Window* pWindow, SDL_GLContext *pContext)
{
	SDL_GL_DeleteContext(pContext);
	SDL_DestroyWindow(pWindow);
	return true;
}
