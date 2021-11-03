#ifndef GLERROR_H
#define GLERROR_H

#include "GL/glew.h"

void gl_debug_callback(GLenum source,
					   GLenum type,
					   GLuint id,
					   GLenum severity,
					   GLsizei length,
					   const GLchar *message,
					   const void *user_param);

#endif // GLERROR_H
