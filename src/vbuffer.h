#ifndef VBUFFER_H
#define VBUFFER_H

#include "GL/glew.h"
#include <stdbool.h>

struct vertex_buffer_t {
	GLuint id;
	GLuint type;
	bool dynamic;
};
typedef struct vertex_buffer_t VertexBuffer;

// should be able to pass array
bool vbo_create(struct vertex_buffer_t *p_vbo, GLint type, bool dynamic);
// should be able to pass array
void vbo_destroy(struct vertex_buffer_t *p_vbo);
void vbo_bind(struct vertex_buffer_t *p_vbo);
void vbo_unbind(struct vertex_buffer_t *p_vbo);
void vbo_buffer(struct vertex_buffer_t *p_vbo, void *p_data, size_t offset, size_t count);

#endif // VBUFFER_H
