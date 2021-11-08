#ifndef GLERROR_H
#define GLERROR_H

#include "GL/glew.h"

GLenum gl_check_error(const char *filename, int line);
# define glCheckError() gl_check_error(__FILE__, __LINE__)

void gl_debug_callback(GLenum source,
					   GLenum type,
					   GLuint id,
					   GLenum severity,
					   GLsizei length,
					   const GLchar *message,
					   const void *user_param);

#endif // GLERROR_H
