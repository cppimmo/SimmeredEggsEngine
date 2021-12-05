#include "r_geometry.h"

#include <stdlib.h>
#include <math.h>

static void
GeometryCylinderTopcap(struct meshdata_t *const data, GLfloat bottomradius,
					   GLfloat topradius, GLfloat height, GLuint slices,
					   GLuint stacks);
static void
GeometryCylinderBottomcap(struct meshdata_t *const data, GLfloat bottomradius,
						  GLfloat topradius, GLfloat height, GLuint slices,
						  GLuint stacks);
static void GeometrySubdivide(struct meshdata_t *const data);
static void SetVertexData(struct vertexdata_t *const data,
						  GLfloat x, GLfloat y, GLfloat z, GLfloat nx,
						  GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty,
						  GLfloat tz, GLfloat u, GLfloat v);

void R_GeometryCube(struct meshdata_t *const data, GLfloat width, GLfloat height,
					GLfloat depth) {
	struct vertexdata_t *vertices = data->vertices;
	const size_t vlength = 24;
	vertices = (struct vertexdata_t*)malloc(vlength *
											sizeof(struct vertexdata_t));
	// measurements that are half the size of arguments
	const GLfloat w2 = 0.5f * width;
	const GLfloat h2 = 0.5f * height;
	const GLfloat d2 = 0.5f * depth;

	// Fill in the front face vertex data.
	SetVertexData(&vertices[0], -w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
				  0.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[1], -w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
				  0.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[2], +w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);
	SetVertexData(&vertices[3], +w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 1.0f);
	// Fill in the back face vertex data.
	SetVertexData(&vertices[4], -w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
				  0.0f, 1.0f, 1.0f);
	SetVertexData(&vertices[5], +w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
				  0.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[6], +w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
				  0.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[7], -w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);
	// Fill in the top face vertex data.
	SetVertexData(&vertices[8], -w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				  0.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[9], -w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				  0.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[10], +w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);
	SetVertexData(&vertices[11], +w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 1.0f);
	// Fill in the bottom face vertex data.
	SetVertexData(&vertices[12], -w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
				  0.0f, 1.0f, 1.0f);
	SetVertexData(&vertices[13], +w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
				  0.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[14], +w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
				  0.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[15], -w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);
	// Fill in the left face vertex data.
	SetVertexData(&vertices[16], -w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  -1.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[17], -w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  -1.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[18], -w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  -1.0f, 1.0f, 0.0f);
	SetVertexData(&vertices[19], -w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  -1.0f, 1.0f, 1.0f);
	// Fill in the right face vertex data.
	SetVertexData(&vertices[20], +w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  1.0f, 0.0f, 1.0f);
	SetVertexData(&vertices[21], +w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  1.0f, 0.0f, 0.0f);
	SetVertexData(&vertices[22], +w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  1.0f, 1.0f, 0.0f);
	SetVertexData(&vertices[23], +w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				  1.0f, 1.0f, 1.0f);

	// Create the indices.
	GLuint *indices = data->indices;
	const size_t ilength = 36;
	indices = (GLuint*)malloc(ilength * sizeof(GLuint));
	// Fill in the front face index data
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	// Fill in the back face index data
	indices[6] = 4; indices[7]  = 5; indices[8]  = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;
	// Fill in the top face index data
	indices[12] = 8; indices[13] =  9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;
	// Fill in the bottom face index data
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;
	// Fill in the left face index data
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;
	// Fill in the right face index data
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;
}

void R_GeometrySphere(struct meshdata_t *const data, GLfloat radius,
					  GLuint slices, GLuint stacks) {
	/* compute the vertices starting at the top pole and moving down the stacks
	 * Poles: note that there will be texture coordinates distortion as there is
	 * not a unique point on the texture map to assign to the pole when mapping
	 * a rectangular texture onto a sphere. */
	struct vertexdata_t topvertex =
	{
		{0.0f, +radius, 0.0f}, {0.0f, +1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}
	};
	struct vertexdata_t bottomvertex =
    {
		{0.0f, -radius, 0.0f}, {0.0f, -1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}
	};
}

void R_GeometryCylinder(struct meshdata_t *const data, GLfloat bottomradius,
						GLfloat topradius, GLfloat height, GLuint slices,
						GLuint stacks) {
	// build stacks
	GLfloat stackheight = height / stacks;
	/* amount to increment radius as we move up each stack level from bottom
	 * to top. */
	GLfloat radiusstep = (topradius - bottomradius) / stacks;
	GLuint rings = stacks + 1; // ring count

	// compute vertices for each stack ring starting at the bottom and moving up
	for (GLuint i = 0; i < rings; ++i) {
		GLfloat y = -0.5f * height + i * stackheight;
		GLfloat r = bottomradius + i * radiusstep;

		// vertices of ring
		GLfloat dtheta = 2.0f * (GLfloat)acos(-1.0) / slices;
		for (GLuint j = 0; j <= slices; ++j) {
			struct vertexdata_t vertex;

			GLfloat c = cosf(j * dtheta);
			GLfloat s = sinf(j * dtheta);

			vertex.position[0] = r * c;
			vertex.position[1] = y;
			vertex.position[2] = r * s;

			vertex.texcoord[0] = (float)j / slices;
			vertex.texcoord[1] = 1.0f - (float)i / stacks;

			/* Cylinder can be parameterized as follows, where we introduce v
			 * parameter that goes in the same direction as the v tex-coord
			 * so that the bitangent goes in the same direction as the v tex-coord.
			 * Let r0 be the bottom radius and let r1 be the top radius.
			 * y(v) = h - hv for v in [0,1].
			 * r(v) = r1 + (r0-r1)v
			 *
			 * x(t, v) = r(v)*cos(t)
			 * y(t, v) = h - hv
			 * z(t, v) = r(v)*sin(t)
			 *
			 * dx/dt = -r(v)*sin(t)
			 * dy/dt = 0
			 * dz/dt = +r(v)*cos(t)
			 *
			 * dx/dv = (r0-r1)*cos(t)
			 * dy/dv = -h
			 * dz/dv = (r0-r1)*sin(t) */

			// this is unit length
			vertex.tangent[0] = -s;
			vertex.tangent[1] = 0.0f;
			vertex.tangent[2] = c;

			GLfloat dr = bottomradius - topradius;
			vec3 bitangent = {dr *c, -height, dr*s};

			vec3 T;
			glm_vec3_copy(vertex.tangent, T);
 			vec3 B;
			glm_vec3_copy(bitangent, B);
			vec3 N;
			glm_vec3_mul(T, B, N);
			glm_vec3_normalize(N);
			glm_vec3_copy(N, vertex.normal);
		}
	}
}

void
R_GeometryCylinderTopcap(struct meshdata_t *const data, GLfloat bottomradius,
						 GLfloat topradius, GLfloat height, GLuint slices,
						 GLuint stacks) {

}

void
R_GeometryCylinderBottomcap(struct meshdata_t *const data, GLfloat bottomradius,
							GLfloat topradius, GLfloat height, GLuint slices,
							GLuint stacks) {

}

void R_GeometryGrid(struct meshdata_t *const data, GLfloat width, GLfloat depth,
					GLuint m, GLuint n) {

}

// quad covering screen NDC coords. useful for postprocessing effects
void R_GeometryScreenQuad(struct meshdata_t *const data) {

}

void R_GeometrySubdivide(struct meshdata_t *const data) {

}

inline void R_FreeMeshData(struct meshdata_t *const data) {
	free(data->vertices);
	free(data->indices);
}

inline void SetVertexData(struct vertexdata_t *const data,
								 GLfloat x, GLfloat y, GLfloat z, GLfloat nx,
								 GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty,
								 GLfloat tz, GLfloat u, GLfloat v) {
	data->position[0] = x;
	data->position[1] = y;
	data->position[2] = z;

	data->normal[0] = nx;
	data->normal[1] = ny;
	data->normal[2] = nz;

	data->tangent[0] = tx;
	data->tangent[1] = ty;
	data->tangent[2] = tz;

	data->texcoord[0] = u;
	data->texcoord[1] = v;
}

