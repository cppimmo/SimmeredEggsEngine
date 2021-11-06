#ifndef RENDER_H
#define RENDER_H

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include <stdbool.h>

#define BUFFER_OFFSET(X) ((void*)(X))

void r_clearcolor(const GLfloat *value);
void r_viewport(GLint x, GLint y, GLint width, GLint height);
GLboolean r_is_enabled(GLenum capability);
void r_enable(GLenum capability);
void r_disable(GLenum capability);
void r_set_gl_callback(GLDEBUGPROC callback, void *userParam);

#endif // RENDER_H
