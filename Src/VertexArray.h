/* =============================================================================
** SimmeredEggsEngine, file: r_vertexarray.h Created 12/6/2021
**
** Copyright 2021 Brian Hoffpauir TX, USA
** All rights reserved.
**
** Redistribution and use of this source file, with or without modification, is
** permitted provided that the following conditions are met:
**
** 1. Redistributions of this source file must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
** EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** =============================================================================
**/
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
