#ifndef __R_INDEXBUFFER_H__
#define __R_INDEXBUFFER_H__

#include "GL/glew.h"
#include "u_utility.h"

#include <stdlib.h>

struct indexbuffer_t {
	GLuint id;
	GLenum target;
	GLboolean dynamic;
};

boolean R_CreateIndexBuffer(struct indexbuffer_t *ibo, GLboolean dynamic);
void R_DeleteIndexBuffer(struct indexbuffer_t *ibo);
boolean R_CreateIndexBufferArray(struct indexbuffer_t **ibo, size_t count,
								 GLboolean dynamic);
void R_DeleteIndexBufferArray(struct indexbuffer_t **ibo, size_t count);
void R_BindIndexBuffer(struct indexbuffer_t *ibo);
void R_UnbindIndexBuffer(struct indexbuffer_t *ibo);
void R_IndexBufferStorage(struct indexbuffer_t *ibo, GLsizeiptr size,
						  const void *data);
void R_IndexBufferData(struct indexbuffer_t *ibo, GLsizeiptr size,
					   const void *data);

#endif
