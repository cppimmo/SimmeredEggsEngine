/* =============================================================================
** SimmeredEggsEngine, file: r_skybox.h Created 12/6/2021
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
#ifndef __R_SKYBOX_H__
#define __R_SKYBOX_H__

#include "cglm/cglm.h"
#include "u_utility.h"
#include "r_vertexarray.h"
#include "r_vertexbuffer.h"

struct skybox_t {
	struct vertexarray_t vao;
	struct vertexbuffer_t vbo;
	GLuint texture;
	GLuint program; // shader program
};
typedef struct skybox_t Skybox;

boolean R_SkyboxInit(Skybox *skybox, const char *filenames[]);
void R_SkyboxRender(Skybox *skybox, mat4 *view, mat4 *projection);
void R_SkyboxDestroy(Skybox *skybox);

#endif
