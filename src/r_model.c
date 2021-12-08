/* =============================================================================
** SimmeredEggsEngine, file: r_model.c Created 12/6/2021
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
#include "r_model.h"
#include "u_log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static GLuint ModelTextureFromSkin(int n, const struct mdlmodel_t *model);

boolean R_ModelLoad(const char *filename, struct mdlmodel_t *model) {
	FILE *handle = NULL;
	int i;

	handle = fopen(filename, "rb");
	if (handle == NULL) {
		U_LogWrite(LOG_ERR, "mdl_load(): Failed to open %s\n", filename);
		return false;
	}
	// read header
	fread(&model->header, 1, sizeof(struct mdlheader_t), handle);

	if ((model->header.ident != 1330660425) ||
		(model->header.version != 6)) {
		U_LogWrite(LOG_ERR, "mdl_load(): bad version or identifier\n");
		fclose(handle);
		return false;
	}

	// allocations
	model->skins = (struct mdlskin_t *)
		U_Malloc(sizeof(struct mdlskin_t) * model->header.numskins);
   	model->texcoords = (struct mdltexcoord_t *)
		U_Malloc(sizeof(struct mdltexcoord_t) * model->header.numverts);
	model->triangles = (struct mdltriangle_t *)
		U_Malloc(sizeof(struct mdltriangle_t) * model->header.numtris);
	model->frames = (struct mdlframe_t *)
		U_Malloc(sizeof(struct mdlframe_t) * model->header.numframes);
	model->texid = (GLuint *)
		U_Malloc(sizeof(GLuint) * model->header.numskins);

	model->iskin = 0;
	// read texture data
	for (i = 0; i < model->header.numskins; ++i) {
		model->skins[i].data = (GLubyte *)
			U_Malloc(sizeof(GLubyte) * model->header.skinwidth
					 * model->header.skinheight);

		fread(&model->skins[i].group, sizeof(int), 1, handle);
		fread(model->skins[i].data, sizeof(GLubyte), model->header.skinwidth
			  * model->header.skinheight, handle);
        model->texid[i] = ModelTextureFromSkin(i, model);

		U_Free(model->skins[i].data);
		model->skins[i].data = NULL;
	}

	fread(model->texcoords, sizeof(struct mdltexcoord_t),
		  model->header.numverts, handle);
	fread(model->triangles, sizeof(struct mdltriangle_t),
		  model->header.numtris, handle);

	// read frames
	for (i = 0; i < model->header.numframes; ++i) {
		// memory alloc for vertices of this frame
		model->frames[i].frame.verts = (struct mdlvertex_t *)
			U_Malloc(sizeof(struct mdlvertex_t) * model->header.numverts);
		// read frame data
		fread(&model->frames[i].type, sizeof(int), 1, handle);
		fread(&model->frames[i].frame.bboxmin,
			  sizeof(struct mdlvertex_t), 1, handle);
		fread(&model->frames[i].frame.bboxmax,
			  sizeof(struct mdlvertex_t), 1, handle);
		fread(model->frames[i].frame.name, sizeof(char), 16, handle);
		fread(model->frames[i].frame.verts, sizeof(struct mdlvertex_t),
			  model->header.numverts, handle);
	}

	fclose(handle);
	return true;
}

// create a texture given skin index 'n'
static GLuint ModelTextureFromSkin(int n, const struct mdlmodel_t *model) {
	GLuint texid;
	/* GLubyte *pixels = (GLubyte*)U_Malloc(model->header.skinwidth *
										 model->header.skinheight * 3);
	// convert indexed 8 bits texture to RGB 24 bits
	for (int i = 0; i < model->header.skinwidth * model->header.skinheight;
		 ++i) {
		pixels[(i * 3) + 0] = colormap[model->skins[n].data[i]][0];
		pixels[(i * 3) + 1] = colormap[model->skins[n].data[i]][1];
        pixels[(i * 3) + 2] = colormap[model->skins[n].data[i]][2];
	}
	// generate texture
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->header.skinwidth,
					 model->header.skinheight, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 pixels);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, model->header.skinwidth,
    //               model->header.skinheight, GL_RGB, GL_UNSIGNED_BYTE,
    //             pixels);
	free(pixels); */
	return texid;
}

void R_ModelDestroy(struct mdlmodel_t *model) {
	if (model->skins != NULL) {
		U_Free(model->skins);
		model->skins = NULL;
	}
	if (model->texcoords != NULL) {
		U_Free(model->texcoords);
		model->texcoords = NULL;
	}
	if (model->triangles != NULL) {
		U_Free(model->triangles);
		model->triangles = NULL;
	}
	if (model->texid != NULL) {
		U_Free(model->texid);
		model->texid = NULL;
	}
	if (model->frames != NULL) {
		for (int i = 0; i < model->header.numframes; ++i) {
			U_Free(model->frames[i].frame.verts);
			model->frames[i].frame.verts = NULL;
		}
		U_Free(model->frames);
		model->frames = NULL;
	}
}

