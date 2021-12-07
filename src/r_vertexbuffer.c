/* =============================================================================
** SimmeredEggsEngine, file: r_vertexbuffer.c Created 12/6/2021
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
#include "r_vertexbuffer.h"

boolean R_CreateVertexBuffer(struct vertexbuffer_t *vbo, GLenum target,
							 GLboolean dynamic) {
	vbo->target = target;
	vbo->dynamic = dynamic;
	glCreateBuffers(1, &vbo->id);
	if (!glIsBuffer(vbo->id))
		return false;
	return true;
}

void R_DeleteVertexBuffer(struct vertexbuffer_t *vbo) {
	glDeleteBuffers(1, &vbo->id);
}

boolean R_CreateVertexBufferArray(struct vertexbuffer_t **vbo, size_t count, GLenum target,
								  GLboolean dynamic) {
	for (size_t i = 0; i < count; ++i) {
		vbo[i]->target = target;
		vbo[i]->dynamic = dynamic;
		glCreateBuffers(1, &vbo[i]->id);
		if (!glIsBuffer(vbo[i]->id))
			return false;
	}
	return true;
}

void R_DeleteVertexBufferArray(struct vertexbuffer_t **vbo, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		glDeleteBuffers(1, &vbo[i]->id);
	}
}

inline void R_BindVertexBuffer(struct vertexbuffer_t *vbo) {
	glBindBuffer(vbo->target, vbo->id);
}

inline void R_UnbindVertexBuffer(struct vertexbuffer_t *vbo) {
	glBindBuffer(vbo->target, 0);
}

void R_VertexBufferStorage(struct vertexbuffer_t *vbo, GLsizeiptr size,
						   const void *data) {
	GLbitfield flags = (vbo->dynamic == GL_TRUE)? GL_DYNAMIC_STORAGE_BIT : 0;
	glNamedBufferStorage(vbo->id, size, data, flags);
}

void R_VertexBufferData(struct vertexbuffer_t *vbo, GLsizeiptr size,
						const void *data) {
	// possibly offset and count parameters instead of size
	R_BindVertexBuffer(vbo);
	glBufferData(vbo->target, size, data,
				 (vbo->dynamic)? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	//R_UnbindVertexBuffer(vbo);
}

