#ifndef __R_VERTEXARRAY_H__
#define __R_VERTEXARRAY_H__

#include "GL/glew.h"
#include "r_vertexbuffer.h"
#include "u_utility.h"

#include <stdlib.h>

/* wraps interfacing for glVertexAttrib */
struct vertexarray_t {
	GLuint id;
};

boolean R_CreateVertexArray(struct vertexarray_t *vao);
void R_DeleteVertexArray(struct vertexarray_t *vao);
// same but for arrays, pass size as count
boolean R_CreateVertexArrayArray(struct vertexarray_t **vao, size_t count);
void R_DeleteVertexArrayArray(struct vertexarray_t **vao, size_t count);
void R_BindVertexArray(struct vertexarray_t *vao);
void R_UnbindVertexArray(void);
void R_VertexAttribPtr(struct vertexarray_t *vao,
					   struct vertexbuffer_t *vbo,
					   GLuint index, GLint size, GLenum type,
					   GLboolean normalized, GLsizei stride,
					   size_t offset);
// wrapper for gl{Enable,Disable}VertexAttrib()
void R_VertexAttribEnable(const GLuint index);
void R_VertexAttribDisable(const GLuint index);

#endif
