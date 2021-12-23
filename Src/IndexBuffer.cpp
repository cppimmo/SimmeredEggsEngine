/* =============================================================================
** SimmeredEggsEngine, file: IndexBuffer.cpp Created 12/6/2021
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
#include "IndexBuffer.h"

boolean R_CreateIndexBuffer(struct indexbuffer_t *ibo, GLboolean dynamic) {
	ibo->target = GL_ELEMENT_ARRAY_BUFFER;
	ibo->dynamic = dynamic;
	glCreateBuffers(1, &ibo->id);
	if (!glIsBuffer(ibo->id))
		return false;
	return true;
}

void R_DeleteIndexBuffer(struct indexbuffer_t *ibo) {
	glDeleteBuffers(1, &ibo->id);
}

boolean R_CreateIndexBufferArray(struct indexbuffer_t **ibo, size_t count,
								 GLboolean dynamic) {
	for (size_t i = 0; i < count; ++i) {
		ibo[i]->target = GL_ELEMENT_ARRAY_BUFFER;
		ibo[i]->dynamic = dynamic;
		glCreateBuffers(1, &ibo[i]->id);
		if (!glIsBuffer(ibo[i]->id))
			return false;
	}
	return true;
}

void R_DeleteIndexBufferArray(struct indexbuffer_t **ibo, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		glDeleteBuffers(1, &ibo[i]->id);
	}
}

inline void R_BindIndexBuffer(struct indexbuffer_t *ibo) {
	glBindBuffer(ibo->target, ibo->id);
}

inline void R_UnbindIndexBuffer(struct indexbuffer_t *ibo) {
	glBindBuffer(ibo->target, 0);
}

void R_IndexBufferStorage(struct indexbuffer_t *ibo, GLsizeiptr size,
						  const void *data) {
	GLbitfield flags = (ibo->dynamic == GL_TRUE)? GL_DYNAMIC_STORAGE_BIT : 0;
	glNamedBufferStorage(ibo->id, size, data, flags);
}

void R_IndexBufferData(struct indexbuffer_t *ibo, GLsizeiptr size,
					   const void *data) {
	// possibly offset and count parameters instead of size
	R_BindIndexBuffer(ibo);
	glBufferData(ibo->target, size, data,
				 (ibo->dynamic)? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	//R_UnbindVertexBuffer(vbo);
}

