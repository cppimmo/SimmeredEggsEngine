/* =============================================================================
** SimmeredEggsEngine, file: r_vertexarray.c Created 12/6/2021
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
#include "r_vertexarray.h"

boolean R_CreateVertexArray(struct vertexarray_t *vao) {
	glCreateVertexArrays(1, &vao->id);
	if (!glIsVertexArray(vao->id))
		return false;
	return true;
}

// creating vertex arrays from arrays. needs work
boolean R_CreateVertexArrayArray(struct vertexarray_t **vao, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		glCreateVertexArrays(count, &vao[i]->id);
		if (!glIsVertexArray(vao[i]->id))
			return false;
	}
	return true;
}

void R_DeleteVertexArray(struct vertexarray_t *vao) {
	glDeleteVertexArrays(1, &vao->id);
}

void R_DeleteVertexArrayArray(struct vertexarray_t **vao, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		glDeleteVertexArrays(1, &vao[i]->id);
	}
}

inline void R_BindVertexArray(struct vertexarray_t *vao) {
	glBindVertexArray(vao->id);
}

inline void R_UnbindVertexArray(void) {
	glBindVertexArray(0);
}

/* normalized parameter can be given dummy values when using types: integer and
   long double */
void R_VertexAttribPtr(struct vertexarray_t *vao,
					   struct vertexbuffer_t *vbo,
					   GLuint index, GLint size, GLenum type,
					   GLboolean normalized, GLsizei stride,
					   size_t offset) {
	R_BindVertexArray(vao);
	R_BindVertexBuffer(vbo);

	switch (type) {
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_INT_2_10_10_10_REV:
	case GL_UNSIGNED_INT_2_10_10_10_REV:
 		// signed and unsigned integral version
		glVertexAttribIPointer(index, size, type, stride, offset);
		break;
	case GL_DOUBLE:
		// 64-bit floating point version
		glVertexAttribLPointer(index, size, type, stride, offset);
		break;
	default:
		// regular floating point version
		glVertexAttribPointer(index, size, type, normalized, stride,
							  offset);
		break;
	}
	// R_UnbindVertexArray(vao);
	// R_UnbindVertexBuffer(vbo);
}

inline void R_VertexAttribEnable(const GLuint index) {
	glEnableVertexAttribArray(index);
}

inline void R_VertexAttribDisable(const GLuint index) {
	glDisableVertexAttribArray(index);
}

