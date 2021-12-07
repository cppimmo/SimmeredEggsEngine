/* =============================================================================
** SimmeredEggsEngine, file: r_vertexbuffer.h Created 12/6/2021
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
