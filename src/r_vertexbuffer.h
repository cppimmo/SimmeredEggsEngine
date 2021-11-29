#ifndef __R_VERTEXBUFFER_H__
#define __R_VERTEXBUFFER_H__

#include "GL/glew.h"
#include "u_utility.h"

#include <stdlib.h>

struct vertexbuffer_t {
	GLuint id;
	GLenum target;
	GLboolean dynamic;
};

boolean R_CreateVertexBuffer(struct vertexbuffer_t *vbo, GLenum target,
							 GLboolean dynamic);
void R_DeleteVertexBuffer(struct vertexbuffer_t *vbo);
boolean R_CreateVertexBufferArray(struct vertexbuffer_t **vbo, size_t count,
								  GLenum target, GLboolean dynamic);
void R_DeleteVertexBufferArray(struct vertexbuffer_t **vbo, size_t count);
void R_BindVertexBuffer(struct vertexbuffer_t *vbo);
void R_UnbindVertexBuffer(struct vertexbuffer_t *vbo);
void R_VertexBufferStorage(struct vertexbuffer_t *vbo, GLsizeiptr size,
						   const void *data);
void R_VertexBufferData(struct vertexbuffer_t *vbo, GLsizeiptr size,
					 const void *data);

#endif
