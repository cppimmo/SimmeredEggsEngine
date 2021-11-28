#ifndef __D_GLERROR_H__
#define __D_GLERROR_H__

#include "GL/glew.h"

GLenum D_glCheckError(const char *filename, int line);
# define glCheckError() D_glCheckError(__FILE__, __LINE__)

void D_glDebugCallback(GLenum source,
					   GLenum type,
					   GLuint id,
					   GLenum severity,
					   GLsizei length,
					   const GLchar *message,
					   const void *userparam);

#endif
