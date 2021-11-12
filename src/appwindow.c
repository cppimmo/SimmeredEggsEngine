#include "appwindow.h"
#include "log.h"

bool window_init(SDL_Window *p_window, SDL_GLContext *p_context,
				 const Options *const p_options)
{
	p_window = SDL_CreateWindow("Starship Fleet", SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (p_window == NULL) {
		log_write(LOG_ERR, "SDL_CreateWindow() failure: %s\n", SDL_GetError());
		return false;
	}
	
	//window_attribs(4, 5, true);
	//SDL_GLContext context = SDL_GL_CreateContext(p_window);
	// if (context == NULL) {
		//log_write(LOG_ERR, "SDL_GL_CreateContext() failure: %s\n", SDL_GetError());
		//	return false;
		//}
	/* if (SDL_GL_MakeCurrent(p_window, *p_context) < 0) {
		log_write(LOG_ERR, "SDL_GL_MakeCurrent() failure: %s\n", SDL_GetError());
		return false;
	} */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GLContext context = SDL_GL_CreateContext(p_window);
	SDL_GL_SetSwapInterval(1);


	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK) {
		log_write(LOG_ERR, "glewInit() error: %s\n", glewGetErrorString(glew_error));
		return false;
	}

    if (glGetString(GL_VENDOR) != 0)
        log_write(LOG_LOG, "GL_VENDOR=%s\n", glGetString(GL_VENDOR));
    if (glGetString(GL_RENDERER) != 0)
        log_write(LOG_LOG, "GL_RENDERER=%s\n", glGetString(GL_RENDERER));

    if (glGetString(GL_VERSION) != 0)
        log_write(LOG_LOG, "GL_VERSION=%s\n", glGetString(GL_VERSION));

    if (glGetString(GL_SHADING_LANGUAGE_VERSION) != 0)
        log_write(LOG_LOG, "GL_SHADING_LANGUAGE_VERSION=%s\n",
              glGetString(GL_SHADING_LANGUAGE_VERSION));
	log_write(LOG_MSG, "gl3w loaded successfully; version: %s\n",
               glewGetString(GLEW_VERSION));
	return true;
}

bool window_attribs(int glv_major, int glv_minor, bool double_buffer)
{ // relevant documentation: https://wiki.libsdl.org/SDL_GLattr
	// SDL_GL_LoadLibrary(NULL);
	// SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glv_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glv_minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	return true;
}

int window_get_attrib(SDL_GLattr attr)
{
	int temp;
    SDL_GL_GetAttribute(attr, &temp);
	return temp;
}

void window_event_handle(const SDL_Event *p_event)
{
	if (p_event->type == SDL_WINDOWEVENT) {
		switch (p_event->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
	        window_state.is_visible = true;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
			window_state.is_visible = false;
            break;
        case SDL_WINDOWEVENT_EXPOSED:		   
            break;
        case SDL_WINDOWEVENT_MOVED:
			window_viewport(p_event->window.data1, p_event->window.data2,
				window_state.window_pos_x, window_state.window_pos_y);
            break;
        case SDL_WINDOWEVENT_RESIZED:
			window_viewport(window_state.window_pos_x,
							window_state.window_pos_y,
							p_event->window.data1, p_event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
			window_viewport(window_state.window_pos_x,
							window_state.window_pos_y,
							p_event->window.data1, p_event->window.data2);
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

void window_viewport(GLint posx, GLint posy, GLint width, GLint height)
{
	window_state.window_pos_x = posx;
	window_state.window_pos_y = posy;
	window_state.window_size_x = width;
	window_state.window_size_y = height;
	glViewport(posx, posy, width, height);
}

inline bool window_close(SDL_Window* p_window, SDL_GLContext *p_context)
{
	SDL_GL_DeleteContext(*p_context);
	SDL_DestroyWindow(p_window);
	return true;
}
