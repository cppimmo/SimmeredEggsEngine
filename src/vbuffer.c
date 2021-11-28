#include "vbuffer.h"

boolean vbo_create(struct vertex_buffer_t *p_vbo, GLenum target, GLboolean dynamic)
{
	p_vbo->target = target;
	p_vbo->dynamic = dynamic;
	glCreateBuffers(1, &p_vbo->id);
	if (!glIsBuffer(p_vbo->id))
		return false;
	return true;
}

void vbo_delete(struct vertex_buffer_t *p_vbo)
{
	glDeleteBuffers(1, &p_vbo->id);
}

boolean vbo_create_arr(struct vertex_buffer_t **p_vbo, size_t count, GLenum target,
					GLboolean dynamic)
{
	for (size_t i = 0; i < count; ++i) {
		p_vbo[i]->target = target;
		p_vbo[i]->dynamic = dynamic;
		glCreateBuffers(1, &p_vbo[i]->id);
		if (!glIsBuffer(p_vbo[i]->id))
			return false;
	}
	return true;
}

void vbo_delete_arr(struct vertex_buffer_t **p_vbo, size_t count)
{
	for (size_t i = 0; i < count; ++i) {
		glDeleteBuffers(1, &p_vbo[i]->id);
	}
}

inline void vbo_bind(struct vertex_buffer_t *p_vbo)
{
	glBindBuffer(p_vbo->target, p_vbo->id);
}

inline void vbo_unbind(struct vertex_buffer_t *p_vbo)
{
	glBindBuffer(p_vbo->target, 0);
}

void vbo_buffer_storage(struct vertex_buffer_t *p_vbo, GLsizeiptr size,
						const void *data)
{
	GLbitfield flags = (p_vbo->dynamic == GL_TRUE)? GL_DYNAMIC_STORAGE_BIT : 0;
	glNamedBufferStorage(p_vbo->id, size, data, 0);
}

void vbo_buffer_data(struct vertex_buffer_t *p_vbo, GLsizeiptr size,
					 const void *data)
{ // possibly offset and count parameters instead of size
	//
	vbo_bind(p_vbo);
	glBufferData(p_vbo->target, size, data,
				 (p_vbo->dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	vbo_bind(p_vbo);
}

