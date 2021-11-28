#ifndef IBUFFER_H
#define IBUFFER_H

#include "GL/glew.h"
#include <stdbool.h>
#include <stdlib.h>

struct index_buffer_t {
	GLuint id;
	GLenum target;
	GLboolean dynamic;
};
typedef struct index_buffer_t IndexBuffer;

bool ibo_create(struct index_buffer_t *p_ibo, GLboolean dynamic);
void ibo_delete(struct index_buffer_t *p_ibo);
bool ibo_create_arr(struct index_buffer_t **p_ibo, size_t count,
					GLboolean dynamic);
void ibo_delete_arr(struct index_buffer_t **p_ibo, size_t count);
void ibo_bind(struct index_buffer_t *p_ibo);
void ibo_unbind(struct index_buffer_t *p_ibo);
void ibo_buffer_storage(struct index_buffer_t *p_ibo, GLsizeiptr size,
						const void *data);
void ibo_buffer_data(struct index_buffer_t *p_ibo, GLsizeiptr size,
					 const void *data);

#endif // IBUFFER_H
