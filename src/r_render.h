#ifndef __R_RENDER_H__
#define __R_RENDER_H__

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "u_utility.h"

#include "r_vertexarray.h"
#include "r_vertexbuffer.h"

// offset, and type
#define BUFFER_OFFSET(X, Y) ((void*)(X* sizeof(Y)))

void R_Clear(const GLbitfield mask);
void R_ClearColor(const GLfloat *value);
void R_Viewport(GLint x, GLint y, GLint width, GLint height);
GLboolean R_IsEnabled(GLenum capability);
void R_Enable(GLenum capability);
void R_Disable(GLenum capability);
void R_Wireframe(const boolean value);
void R_LineWidth(GLfloat width);
void R_DrawArrays(GLenum mode, GLint first, GLsizei count);
void R_DrawIndexed(GLenum mode, GLsizei count, GLenum type,
					const GLvoid *indices);
void R_MessageCallback(GLDEBUGPROC callback, void *userparam);
void R_MessageControl(GLenum source, GLenum type, GLenum severity,
					   GLsizei count, const GLuint *ids, GLboolean enabled);

#endif
