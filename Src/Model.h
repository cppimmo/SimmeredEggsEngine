/* =============================================================================
** SimmeredEggsEngine, file: Model.h Created 12/6/2021
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
#pragma once

/* MDL Quake model loader code from:
 * http://tfc.duke.free.fr/coding/mdl-specs-en.html
 */
#include "GL/glew.h"
#include "cglm/cglm.h"
#include "u_utility.h"

#define MDL_MAX_TRIANGLES 2048
#define MDL_MAX_VERTICES 1024
#define MDL_MAX_TEXTURE_COORDINATES 1024
#define MDL_MAX_FRAMES 256
#define MDL_MAX_NORMALS 162

/* The .mdl file's header contains all information needed to
 * process the data.
 */
struct mdlheader_t {
	int ident;   //
	int version; //

	vec3 scale;           // scale factor
	vec3 translate;       // translation factor
	float boundingradius; //
	vec3 eyeposition;     // eyes' position

	int numskins;  // num textures
	int skinwidth;  // texture width
	int skinheight; // texture height

	int numverts;  // num vertices
	int numtris;   // num triangles
	int numframes; // num frames

	int synctype;   // 0 = synchron, 1 = random
	int flags;      // state flag
	float size;
};

// skin
struct mdlskin_t {
	int group;
	GLubyte *data;
};

// group of textures
struct mdlgroupskin_t {
	int group;      // group num
	int num;        // num textures
	float *time;    // time duration of each texture
	GLubyte **data; // texture data
};
// num_skins of mdlskin_t or mdlgroupskin_t

// texture coordinates
struct mdltexcoord_t {
	int onseam;
	int s;
	int t;
};

struct mdltriangle_t {
	int facesfront; // 0 = backface, 1 = frontface
	int vertex[3];  // vertex indices
};

// compressed vertex
struct mdlvertex_t {
	unsigned char vertex[3];
	unsigned char normalIndex;
};

// simple frame
struct mdlsimpleframe_t {
	struct mdlvertex_t bboxmin;
	struct mdlvertex_t bboxmax;
	char name[16];
	struct mdlvertex_t *verts;
};

// model frame
struct mdlframe_t {
	int type; // 0 = simple, not 0 = group
	struct mdlsimpleframe_t frame; // this program can't read models composed of group frames!
};

// group of simple frames
struct mdlgroupframe_t {
	int type; // not 0 = group
	struct mdlvertex_t min;
	struct mdlvertex_t max;
	float *time;
	struct mdlsimpleframe_t *frames;
};

struct mdlmodel_t {
	struct mdlheader_t header;

	struct mdlskin_t *skins;
	struct mdltexcoord_t *texcoords;
	struct mdltriangle_t *triangles;
	struct mdlframe_t *frames;

	GLuint *texid;
	int iskin;
};

boolean R_ModelLoad(const char *filename, struct mdlmodel_t *model);
void R_ModelDestroy(struct mdlmodel_t *model);
boolean R_ObjLoad(const char *filename);
void R_ObjDestroy(void);

