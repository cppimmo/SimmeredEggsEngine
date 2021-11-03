#include "render.h"
#include "glerror.h"

void r_clearcolor(const GLfloat *value)
{

}

void r_viewport(GLint x, GLint y, GLint width, GLint height)
{
	glViewport(x, y, width, height);
}

void r_set_gl_callback(GLDEBUGPROC callback, void *userParam)
{
	glDebugMessageCallback(callback, NULL);
}

