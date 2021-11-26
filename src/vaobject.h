#ifndef VAOBJECT_H
#define VAOBJECT_H

#include "GL/glew.h"
#include "vbuffer.h"
#include <stdbool.h>
#include <stdlib.h>

/* wraps interfacing for glVertexAttrib */

struct vertex_array_t {
	GLuint id;
};
typedef struct vertex_array_t VertexArray;

bool vao_create(struct vertex_buffer_t *p_vao);
void vao_delete(struct vertex_array_t *p_vao);
// same but for arrays, pass size as count
bool vao_create_arr(struct vertex_buffer_t **p_vao, size_t count);
void vao_delete_arr(struct vertex_array_t **p_vao, size_t count);
void vao_bind(struct vertex_array_t *p_vao);
void vao_unbind(struct vertex_array_t *p_vao);
void vao_attrib_ptr(struct vertex_array_t *p_vao, struct vertex_buffer_t *p_vbo,
					GLuint index, GLint size, GLenum type, GLboolean normalized,
					GLsizei stride, size_t offset);
// wrapper for gl{Enable,Disable}VertexAttrib()
void vao_attrib_enable(const GLuint index);
void vao_atrrib_disable(const GLuint index);

#endif // VAOBJECT_H
