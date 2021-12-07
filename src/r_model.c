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

/* boolean mdl_load(const char *filename, struct mdl_model_t *p_model) {
	FILE *file_handle = NULL;
	int i;

	file_handle = fopen(filename, "rb");
	if (file_handle == NULL) {
		U_LogWrite(LOG_ERR, "mdl_load(): Failed to open %s\n", filename);
		return false;
	}
	// read header
	fread(&p_model->header, 1, sizeof(struct mdl_header_t), file_handle);

	if ((p_model->header.ident != 1330660425) ||
		(p_model->header.version != 6)) {
		U_LogWrite(LOG_ERR, "mdl_load(): bad version or identifier\n");
		fclose(file_handle);
		return false;
	}

	// allocations
	p_model->skins = (struct mdl_skin_t*)malloc(sizeof(struct mdl_skin_t) * p_model->header.num_skins);
   	p_model->texcoords = (struct mdl_texcoord_t*)malloc(sizeof(struct mdl_texcoord_t) * p_model->header.num_verts);
	p_model->triangles = (struct mdl_triangle_t*)malloc(sizeof(struct mdl_triangle_t) * p_model->header.num_tris);
	p_model->frames = (struct mdl_frame_t*)malloc(sizeof(struct mdl_frame_t) * p_model->header.num_frames);
	p_model->tex_id = (GLuint*)malloc(sizeof(GLuint) * p_model->header.num_skins);

	p_model->iskin = 0;
	// read texture data
	for (i = 0; i < p_model->header.num_skins; ++i) {

        // p_model->tex_id[i] = ;

		free(p_model->skins[i].data);
		p_model->skins[i].data = NULL;
	}

	fread(p_model->texcoords, sizeof(struct mdl_texcoord_t),
		  p_model->header.num_verts, file_handle);
	fread(p_model->triangles, sizeof(struct mdl_triangle_t),
		  p_model->header.num_tris, file_handle);

	// read frames
	for (i = 0; i < p_model->header.num_frames; ++i) {
		// memory alloc for vertices of this frame
		p_model->frames[i].frame.verts = (struct mdl_vertex_t*)malloc(
			sizeof(struct mdl_vertex_t) * p_model->header.num_verts);

		// read frame data
	}

	fclose(file_handle);
	return true;
}

// create a texture given skin index 'n'
static GLuint mdl_mktexture(int n, const struct mdl_model_t *p_model)
{
	GLuint tex_id;
	GLubyte *pixels = (GLubyte*)malloc(p_model->header.skinwidth *
									   p_model->header.skinheight * 3);
	// convert indexed 8 bits texture to RGB 24 bits
	for (int i = 0; i < p_model->header.skinwidth * p_model->header.skinheight;
		 ++i) {
		pixels[(i * 3) + 0] = colormap[p_model->skins[n].data[i]][0];
		pixels[(i * 3) + 1] = colormap[p_model->skins[n].data[i]][1];
        pixels[(i * 3) + 2] = colormap[p_model->skins[n].data[i]][2];
	}
	// generate texture
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTextureImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_model->header.skinwidth,
					 p_model->header.skinheight, 0, GL_RGB, GLUNSIGNED_BYTE,
					 pixels);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, mdl->header.skinwidth,
    //               mdl->header.skinheight, GL_RGB, GL_UNSIGNED_BYTE,
    //             pixels);
	free (pixels);
	return tex_id;
}

void mdl_destroy(struct mdl_model_t *p_model)
{
	if (p_model->skins != NULL) {
		free(p_model->skins);
		p_model->skins = NULL;
	}
	if (p_model->texcoords != NULL) {
		free(p_model->texcoords);
		p_model->texcoords = NULL;
	}
	if (p_model->triangles != NULL) {
		free(p_model->triangles);
		p_model->triangles = NULL;
	}
	if (p_model->tex_id != NULL) {
		free(p_model->tex_id);
		p_model->tex_id = NULL;
	}
	if (p_model->frames != NULL) {
		for (int i = 0; i < p_model->header.num_frames; ++i) {
			free(p_model->frames[i].frame.verts);
			p_model->frames[i].frame.verts = NULL;
		}
		free(p_model->frames);
		p_model->frames = NULL;
	}
} */

/* struct mesh_sphere_t {
	GLfloat *vertices;
	GLuint *indices;
	GLuint *line_indices;
	GLfloat *normals;
	GLfloat *tex_coords;
};
typedef struct mesh_sphere_t MeshSphere;

void mesh_sphere_smooth(struct mesh_sphere_t *p_mesh, const size_t stack_count,
						const size_t sector_count, const GLfloat radius)
{
	GLfloat *vertices = p_mesh->vertices;
	GLuint *indices = p_mesh->indices;
	GLuint *line_indices = p_mesh->line_indices;
	GLfloat *normals = p_mesh->normals;
	GLfloat *tex_coords = p_mesh->tex_coords;

	GLfloat x, y, z, xy; // vertex position
	GLfloat nx, ny, nz, length_inv = 1.0f / radius; // vertex normal
	GLfloat s, t; // vertex tex coord

	// acos(-1.0) is PI
	GLfloat sector_step = 2 * acos(-1.0) / sector_count;
	GLfloat stack_step = acos(-1.0) / stack_count;
	GLfloat sector_angle, stack_angle;

	vertices = malloc(sector_count * stack_count * sizeof(GLfloat));
	normals = malloc(sector_count * stack_count * sizeof(GLfloat));
	tex_coords = malloc(sector_count * stack_count * sizeof(GLfloat));

	// add sector_count + 1 vertices per stack
	// the first and last vertices have some position and normal, but different
	// tex coords
	for (size_t i = 0; i <= stack_count; ++i) {
		stack_angle = acos(-1.0) / 2 -i * stack_step; // starting from pi/2 to -pi/2
		xy = radius * cosf(stack_angle); // r * cos(u)
		z = radius * sinf(stack_angle); // r * sin(u)

		for (size_t j = 0; j <= sector_count; ++j) {
			sector_angle = j * sector_step; // starting from 0 to 2pi

			// vertex position x,y,z
			x = xy * cosf(sector_angle); // r * cos(u) * cos(v)
			y = xy * sinf(sector_angle); // r * cos(u) * sin(v)
			// analgous to vertices[i][j]
			vertices[i * sector_count + j] = x;
			vertices[i * sector_count + j + 1] = y;
			vertices[i * sector_count + j + 2] = z;

			// normalized vertex normal nx,ny,nz
			nx = x * length_inv;
			ny = y * length_inv;
			nz = z * length_inv;
			normals[i * sector_count + j] = nx;
			normals[i * sector_count + j + 1] = ny;
			normals[i * sector_count + j + 2] = nz;

			// vertex tex coord s,t range between 0 and 1
			s = (GLfloat)j / sector_count;
			t = (GLfloat)i / stack_count;
			tex_coords[i * sector_count + j] = s;
			tex_coords[i * sector_count + j + 1] = t;
		}
	}

	indices = p_mesh->indices;
	line_indices = p_mesh->line_indices;
	indices = malloc(sector_count * stack_count * sizeof(GLuint));
	line_indices = malloc(sector_count * stack_count * sizeof(GLuint));

	int k1, k2;
	for (size_t i = 0; i < stack_count; ++i) {
		k1 = i * (sector_count + 1);
		k2 = k1 + sector_count + 1;

		for (size_t j = 0; j < sector_count; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices[i * sector_count + j] = k1;
				indices[i * sector_count + j + 1] = k2;
				indices[i * sector_count + j + 2] = k1 + 1;
			}

			if (i != (stack_count - 1)) {
				indices[i * sector_count + j + 3] = k1 + 1;
				indices[i * sector_count + j + 4] = k2;
				indices[i * sector_count + j + 5] = k2 + 1;
			}

			line_indices[i * sector_count + j] = k1;
			line_indices[i * sector_count + j + 1] = k2;
			if (i != 0) {
				line_indices[i * sector_count + j + 2] = k1;
				line_indices[i * sector_count + j + 3] = k1 + 1;
			}
		}
	}
}

void mesh_sphere_delete(struct mesh_sphere_t *p_mesh)
{
	free(p_mesh->vertices);
	free(p_mesh->indices);
	free(p_mesh->line_indices);
	free(p_mesh->normals);
	free(p_mesh->tex_coords);
} */

