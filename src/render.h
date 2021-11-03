#ifndef RENDER_H
#define RENDER_H

#include "SDL.h"
#include "GL/glew.h"
#include <stdbool.h>

void r_clearcolor(const GLfloat *value);
void r_viewport(GLint x, GLint y, GLint width, GLint height);
void r_set_gl_callback(GLDEBUGPROC callback, void *userParam);

#endif // RENDER_H
