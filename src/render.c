#include "render.h"
#include "glerror.h"

void r_clearcolor(const GLfloat *value)
{
	
}

void r_viewport(GLint x, GLint y, GLint width, GLint height)
{
	glViewport(x, y, width, height);
}

inline GLboolean r_is_enabled(GLenum capability)
{
	return glIsEnabled(capability);
}

inline void r_enable(GLenum capability)
{
	glEnable(capability);
}

inline void r_disable(GLenum capability)
{
	glDisable(capability);
}

void r_set_gl_callback(GLDEBUGPROC callback, void *userParam)
{
	glDebugMessageCallback(callback, NULL);
}

