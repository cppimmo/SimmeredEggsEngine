/* =============================================================================
** SimmeredEggsEngine, file: r_geometry.h Created 12/6/2021
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
#ifndef __R_GEOMETRY_H__
#define __R_GEOMETRY_H__

#include "GL/glew.h"
#include "cglm/cglm.h"

struct vertexdata_t {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 texcoord;
};

struct meshdata_t {
	struct vertexdata_t *vertices;
	GLuint *indices;
};

void R_GeometryCube(struct meshdata_t *const data, GLfloat width, GLfloat height,
					GLfloat depth);
void R_GeometrySphere(struct meshdata_t *const data, GLfloat radius,
					  GLuint slices, GLuint stacks);
void R_GeometryCylinder(struct meshdata_t *const data, GLfloat bottomradius,
						GLfloat topradius, GLfloat height, GLuint slices,
						GLuint stackcount);
void R_GeometryGrid(struct meshdata_t *const data, GLfloat width, GLfloat depth,
					GLuint m, GLuint n);
void R_GeometrySreenQuad(struct meshdata_t *const data);
void R_FreeMeshData(struct meshdata_t *const data);

#endif
