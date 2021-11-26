#ifndef VBUFFER_H
#define VBUFFER_H

#include "GL/glew.h"
#include <stdbool.h>
#include <stdlib.h>

struct vertex_buffer_t {
	GLuint id;
	GLenum target;
	GLboolean dynamic;
};
typedef struct vertex_buffer_t VertexBuffer;

bool vbo_create(struct vertex_buffer_t *p_vbo, GLenum target, GLboolean dynamic);
void vbo_delete(struct vertex_buffer_t *p_vbo);
bool vbo_create_arr(struct vertex_buffer_t **p_vbo, size_t count, GLenum target,
				    GLboolean dynamic);
void vbo_delete_arr(struct vertex_buffer_t **p_vbo, size_t count);
void vbo_bind(struct vertex_buffer_t *p_vbo);
void vbo_unbind(struct vertex_buffer_t *p_vbo);
void vbo_buffer_storage(struct vertex_buffer_t *p_vbo, GLsizeiptr size,
						const void *data);
void vbo_buffer_data(struct vertex_buffer_t *p_vbo, GLsizeiptr size, const void *data);
	
#endif // VBUFFER_H
