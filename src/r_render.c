/* =============================================================================
** SimmeredEggsEngine, r_render.c Created 12/6/2021
**
** Copyright 2021 Brian Hoffpauir TX, USA
** All rights reserved.
**
** Redistribution and use of this source file, with or without modification, is
** permitted provided that the following conditions are met:
**
** 1. Redistributions of this source file must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
** EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** =============================================================================
**/
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

