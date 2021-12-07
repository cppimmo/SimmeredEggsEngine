/* =============================================================================
** SimmeredEggsEngine, file: r_indexbuffer.h Created 12/6/2021
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
