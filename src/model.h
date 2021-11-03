#ifndef MODEL_H
#define MODEL_H

/* MDL Quake model loader code from:
 * http://tfc.duke.free.fr/coding/mdl-specs-en.html
 */
#include "GL/glew.h"
#include "cglm/cglm.h"

/* The .mdl file's header contains all information needed to 
 * process the data.
 */
/* struct mdl_header_t {
	int ident;   // 
	int version; //

	vec3 scale;           // scale factor
	vec3 translate;       // translation factor
	float bounding_radius; //
	vec3 eye_position;     // eyes' position

	int num_skins;  // num textures
	int skin_width;  // texture width
	int skin_height; // texture height

	int num_verts;  // num vertices
	int num_tris;   // num triangles
	int num_frames; // num frames

	int synctype;   // 0 = synchron, 1 = random
	int flags;      // state flag
	float size;
};
typedef mdl_header_t MDLHeader;

// skin
struct mdl_skin_t {
	int group;
	GLubyte *data;
};
typedef mdl_skin_t MDLSkin;

// group of textures
struct MDLgroupskin_t {
	int group;      // group num
	int num;        // num textures
	float *time;    // time duration of each texture
	GLubyte **data; // texture data
};
typedef MDLgroupskin_t MDLGroupSkin;
// num_skins of MDLskin_t or MDLgroupskin_t

// texture coordinates
struct MDLtexcoord_t {
	int onseam;
	int s;
	int t;
};
typedef MDLtexcoord_t MDLTexCoord;

struct MDLtriangle_t {
	int facesfront; // 0 = backface, 1 = frontface
	int vertex[3];  // vertex indices
};
typedef MDLtriangle_t MDLTriangle;

// compressed vertex
struct MDLvertex_t {
	unsigned char vertex[3]
	unsigned char normalIndex;
};
typedef MDLvertex_t MDLVertex;

// simple frame
struct MDLsimpleframe_t {
	struct MDLvertex_t bboxmin;
	struct MDLvertex_t bboxmax;
	char name[16];
	struct MDLvertex_t *verts;
};
typedef MDLsimpleframe_t MDLSimpleFrame;

// model frame
struct MDLframe_t {
	int type; // 0 = simple, not 0 = group
	struct MDLsimpleframe_t frame; // this program can't read models composed of group frames!
};
typedef MDLframe_t MDLFrame;

// group of simple frames
struct MDLgroupframe_t {
	int type; // not 0 = group
	struct MDLvertex_t min;
	struct MDLvertex_t max;
	float *time;
	struct MDLsimpleframe_t *frames;
};
typedef MDLsimpleframe_t MDLSimpleFrame;

struct MDLmodel_t {
	struct mdl_header_t header;

	struct MDLskin_t *skins;
	struct MDLtexcoord_t *texcoords;
	struct MDLtriangle_t *triangles;
	struct MDLframe_t *frames;

	GLuint *tex_id;
	int iskin;
};

bool mdl_load(const char *filename, MDLModel *pModel);
void mdl_destroy(MDLModel *pModel);*/

#endif // MODEL_H
