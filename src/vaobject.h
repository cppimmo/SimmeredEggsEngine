#ifndef VAOBJECT_H
#define VAOBJECT_H

#include "GL/glew.h"
#include "vbuffer.h"
#include <stdbool.h>

struct vertex_array_t {
	GLuint id;
};
typedef struct vertex_array_t VertexArray;

bool vao_create(struct vertex_buffer_t *p_vao);
void vao_destroy(struct vertex_array_t *p_vao);
void vao_bind(struct vertex_array_t *p_vao);
void vao_unbind(struct vertex_array_t *p_vao);
void vao_attrib(struct vertex_array_t *p_vao, struct vertex_buffer_t *p_vbo,
			  GLuint index, GLint size, GLenum type,
			  GLsizei stride, size_t offset);
// wrapper for enable vertex attrib func

#endif // VAOBJECT_H
