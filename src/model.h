#ifndef MODEL_H
#define MODEL_H

/* MDL Quake model loader code from:
 * http://tfc.duke.free.fr/coding/mdl-specs-en.html
 */
#include "GL/glew.h"
#include "cglm/cglm.h"

#define MDL_MAX_TRIANGLES 2048
#define MDL_MAX_VERTICES 1024
#define MDL_MAX_TEXTURE_COORDINATES 1024
#define MDL_MAX_FRAMES 256
#define MDL_MAX_NORMALS 162

/* The .mdl file's header contains all information needed to 
 * process the data.
 */
struct mdl_header_t {
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
typedef struct mdl_header_t MDLHeader;

// skin
struct mdl_skin_t {
	int group;
	GLubyte *data;
};
typedef struct mdl_skin_t MDLSkin;

// group of textures
struct mdl_groupskin_t {
	int group;      // group num
	int num;        // num textures
	float *time;    // time duration of each texture
	GLubyte **data; // texture data
};
typedef struct mdl_groupskin_t MDLGroupSkin;
// num_skins of mdl_skin_t or mdl_groupskin_t

// texture coordinates
struct mdl_texcoord_t {
	int onseam;
	int s;
	int t;
};
typedef struct mdl_texcoord_t MDLTexCoord;

struct mdl_triangle_t {
	int facesfront; // 0 = backface, 1 = frontface
	int vertex[3];  // vertex indices
};
typedef struct mdl_triangle_t MDLTriangle;

// compressed vertex
struct mdl_vertex_t {
	unsigned char vertex[3];
	unsigned char normalIndex;
};
typedef struct mdl_vertex_t MDLVertex;

// simple frame
struct mdl_simpleframe_t {
	struct mdl_vertex_t bboxmin;
	struct mdl_vertex_t bboxmax;
	char name[16];
	struct mdl_vertex_t *verts;
};
typedef struct mdl_simpleframe_t MDLSimpleFrame;

// model frame
struct mdl_frame_t {
	int type; // 0 = simple, not 0 = group
	struct mdl_simpleframe_t frame; // this program can't read models composed of group frames!
};
typedef struct mdl_frame_t MDLFrame;

// group of simple frames
struct mdl_groupframe_t {
	int type; // not 0 = group
	struct mdl_vertex_t min;
	struct mdl_vertex_t max;
	float *time;
	struct mdl_simpleframe_t *frames;
};
typedef struct mdl_simpleframe_t MDLSimpleFrame;

struct mdl_model_t {
	struct mdl_header_t header;

	struct mdl_skin_t *skins;
	struct mdl_texcoord_t *texcoords;
	struct mdl_triangle_t *triangles;
	struct mdl_frame_t *frames;

	GLuint *tex_id;
	int iskin;
};
typedef struct mdl_model_t MDLModel;

bool mdl_load(const char *filename, struct mdl_model_t *p_model);
void mdl_destroy(struct mdl_model_t *p_model);


#endif // MODEL_H
