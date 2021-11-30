#include "r_indexbuffer.h"

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

