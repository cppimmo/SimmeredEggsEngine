#include "r_render.h"
#include "d_glerror.h"

inline void R_Clear(const GLbitfield mask) {
	glClear(mask);
}

inline void R_ClearColor(const GLfloat *value) {
	glClearColor(value[0], value[1], value[2], value[3]);
}

inline void R_Viewport(GLint x, GLint y, GLint width, GLint height) {
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

inline void R_LineWidth(GLfloat width) {
	glLineWidth(width);
}

inline void R_DrawArrays(GLenum mode, GLint first, GLsizei count) {
	glDrawArrays(mode, first, count);
}

inline void R_DrawIndexed(GLenum mode, GLsizei count, GLenum type,
						  const GLvoid *indices) {
	glDrawElements(mode, count, type, indices);
}

void R_MessageCallback(GLDEBUGPROC callback, void *userparam) {
	glDebugMessageCallback(D_glDebugCallback, userparam);
}

void R_MessageControl(GLenum source, GLenum type, GLenum severity,
					   GLsizei count, const GLuint *ids, GLboolean enabled) {
	glDebugMessageControl(source, type, severity, count, ids, enabled);
}

