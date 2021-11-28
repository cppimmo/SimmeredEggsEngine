#ifndef __R_INDEXBUFFER_H__
#define __R_INDEXBUFFER_H__

#include "GL/glew.h"
#include <stdlib.h>
#include "u_utility.h"

struct index_buffer_t {
	GLuint id;
	GLenum target;
	GLboolean dynamic;
};

boolean R_CreateIndexBuffer(struct index_buffer_t *p_ibo, GLboolean dynamic);
void R_DeleteIndexBuffer(struct index_buffer_t *p_ibo);
boolean R_CreateIndexBufferArray(struct index_buffer_t **p_ibo, size_t count,
								 GLboolean dynamic);
void R_DeleteIndexBufferArray(struct index_buffer_t **p_ibo, size_t count);
void R_BindIndexBuffer(struct index_buffer_t *p_ibo);
void R_UnbindIndexBuffer(struct index_buffer_t *p_ibo);
void R_IndexBufferStorage(struct index_buffer_t *p_ibo, GLsizeiptr size,
						  const void *data);
void R_IndexBufferData(struct index_buffer_t *p_ibo, GLsizeiptr size,
					   const void *data);

#endif
