/* =============================================================================
** SimmeredEggsEngine, file: r_render.h Created 12/6/2021
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
#ifndef __R_RENDER_H__
#define __R_RENDER_H__

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "u_utility.h"

#include "r_vertexarray.h"
#include "r_vertexbuffer.h"

// offset, and type
#define BUFFER_OFFSET(X, Y) ((void*)(X* sizeof(Y)))

void R_Clear(const GLbitfield mask);
void R_ClearColor(const GLfloat *value);
void R_Viewport(GLint x, GLint y, GLint width, GLint height);
GLboolean R_IsEnabled(GLenum capability);
void R_Enable(GLenum capability);
void R_Disable(GLenum capability);
void R_Wireframe(const boolean value);
void R_LineWidth(GLfloat width);
void R_DrawArrays(GLenum mode, GLint first, GLsizei count);
void R_DrawIndexed(GLenum mode, GLsizei count, GLenum type,
					const GLvoid *indices);
void R_MessageCallback(GLDEBUGPROC callback, void *userparam);
void R_MessageControl(GLenum source, GLenum type, GLenum severity,
					   GLsizei count, const GLuint *ids, GLboolean enabled);

#endif
