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
