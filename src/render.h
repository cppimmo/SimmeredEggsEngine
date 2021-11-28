#ifndef RENDER_H
#define RENDER_H

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "u_utility.h"

#include "vaobject.h"
#include "vbuffer.h"

// offset, and type
#define BUFFER_OFFSET(X, Y) ((void*)(X* sizeof(Y)))

void r_clearcolor(const GLfloat *value);
void r_viewport(GLint x, GLint y, GLint width, GLint height);
GLboolean r_is_enabled(GLenum capability);
void r_enable(GLenum capability);
void r_disable(GLenum capability);
void r_wireframe(const boolean value);
void r_draw(GLenum mode, GLint first, GLsizei count);
void r_draw_indexed(GLenum mode, GLsizei count, GLenum type,
					const GLvoid *indices);
void r_message_callback(GLDEBUGPROC callback, void *userparam);
void r_message_control(GLenum source, GLenum type, GLenum severity,
					   GLsizei count, const GLuint *ids, GLboolean enabled);

#endif // RENDER_H
