#include "r_render.h"
#include "d_glerror.h"

void R_ClearColor(const GLfloat *value) {

}

void R_Viewport(GLint x, GLint y, GLint width, GLint height) {
	glViewport(x, y, width, height);
}

inline GLboolean R_IsEnabled(GLenum capability) {
	return glIsEnabled(capability);
}

inline void R_Enable(GLenum capability) {
	glEnable(capability);
}

inline void R_Disable(GLenum capability) {
	glDisable(capability);
}

inline void R_Wireframe(const boolean value) {
	if (value)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void R_MessageCallback(GLDEBUGPROC callback, void *userparam) {
	glDebugMessageCallback(D_glDebugCallback, userparam);
}

void R_MessageControl(GLenum source, GLenum type, GLenum severity,
					   GLsizei count, const GLuint *ids, GLboolean enabled) {
	glDebugMessageControl(source, type, severity, count, ids, enabled);
}

