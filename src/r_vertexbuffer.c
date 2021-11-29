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
	glNamedBufferStorage(vbo->id, size, data, 0);
}

void R_VertexBufferData(struct vertexbuffer_t *vbo, GLsizeiptr size,
						const void *data) {
	// possibly offset and count parameters instead of size
	R_BindVertexBuffer(vbo);
	glBufferData(vbo->target, size, data,
				 (vbo->dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	//R_UnbindVertexBuffer(vbo);
}

