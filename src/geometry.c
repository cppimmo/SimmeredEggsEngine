#include "geometry.h"
#include <stdlib.h>
#include <math.h>

static void
geom_cylinder_topcap(struct mesh_data_t *const p_data, GLfloat bottom_radius,
					 GLfloat top_radius, GLfloat height, GLuint slice_count,
					 GLuint stack_count);
static void
geom_cylinder_bottomcap(struct mesh_data_t *const p_data, GLfloat bottom_radius,
						GLfloat top_radius, GLfloat height, GLuint slice_count,
						GLuint stack_count);
static void geom_subdivide(struct mesh_data_t *const p_data);
vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 tex_coord;
static void set_vertex_data(struct vertex_data_t *const p_data,
							GLfloat x, GLfloat y, GLfloat z, GLfloat nx,
							GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty,
							GLfloat tz, GLfloat u, GLfloat v);

void geom_cube(struct mesh_data_t *const p_data, GLfloat width, GLfloat height,
			   GLfloat depth)
{
	struct vertex_data_t *vertices = p_data->vertices;
	const size_t vertices_length = 24;
	vertices = (struct vertex_data_t*)malloc(vertices_length *
											 sizeof(struct vertex_data_t));
	// measurements that are half the size of arguments
	const GLfloat w2 = 0.5f * width;
	const GLfloat h2 = 0.5f * height;
	const GLfloat d2 = 0.5f * depth;

	// Fill in the front face vertex data.
	set_vertex_data(&vertices[0], -w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[1], -w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[2], +w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	set_vertex_data(&vertices[3], +w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	// Fill in the back face vertex data.
	set_vertex_data(&vertices[4], -w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	set_vertex_data(&vertices[5], +w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[6], +w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[7], -w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	// Fill in the top face vertex data.
	set_vertex_data(&vertices[8], -w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[9], -w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[10], +w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	set_vertex_data(&vertices[11], +w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	// Fill in the bottom face vertex data.
	set_vertex_data(&vertices[12], -w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	set_vertex_data(&vertices[13], +w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[14], +w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[15], -w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	// Fill in the left face vertex data.
	set_vertex_data(&vertices[16], -w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[17], -w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[18], -w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	set_vertex_data(&vertices[19], -w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	// Fill in the right face vertex data.
	set_vertex_data(&vertices[20], +w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	set_vertex_data(&vertices[21], +w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	set_vertex_data(&vertices[22], +w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	set_vertex_data(&vertices[23], +w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	// Create the indices.
	GLuint *indices = p_data->indices;
	const size_t indices_length = 36;
	indices = (GLuint*)malloc(indices_length * sizeof(GLuint));
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

void geom_sphere(struct mesh_data_t *const p_data, GLfloat radius,
				 GLuint slice_count, GLuint stack_count)
{
	/* compute the vertices starting at the top pole and moving down the stacks
	 * Poles: note that there will be texture coordinates distortion as there is
	 * not a unique point on the texture map to assign to the pole when mapping
	 * a rectangular texture onto a sphere. */
	struct vertex_data_t top_vertex =
	{
		{0.0f, +radius, 0.0f}, {0.0f, +1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}
	};
	struct vertex_data_t bottom_vertex =
    {
		{0.0f, -radius, 0.0f}, {0.0f, -1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}
	};
}

void geom_cylinder(struct mesh_data_t *const p_data, GLfloat bottom_radius,
				   GLfloat top_radius, GLfloat height, GLuint slice_count,
				   GLuint stack_count)
{
	// build stacks
	GLfloat stack_height = height / stack_count;
	/* amount to increment radius as we move up each stack level from bottom
	 * to top. */
	GLfloat radius_step = (top_radius - bottom_radius) / stack_count;
	GLuint ring_count = stack_count + 1;

	// compute vertices for each stack ring starting at the bottom and moving up
	for (GLuint i = 0; i < ring_count; ++i) {
		GLfloat y = -0.5f * height + i * stack_height;
		GLfloat r = bottom_radius + i * radius_step;

		// vertices of ring
		GLfloat d_theta = 2.0f * (GLfloat)acos(-1.0) / slice_count;
		for (GLuint j = 0; j <= slice_count; ++j) {
			struct vertex_data_t vertex;

			GLfloat c = cosf(j * d_theta);
			GLfloat s = sinf(j * d_theta);

			vertex.position[0] = r * c;
			vertex.position[1] = y;
			vertex.position[2] = r * s;

			vertex.tex_coord[0] = (float)j / slice_count;
			vertex.tex_coord[1] = 1.0f - (float)i / stack_count;

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

			GLfloat dr = bottom_radius - top_radius;
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
geom_cylinder_topcap(struct mesh_data_t *const p_data, GLfloat bottom_radius,
					 GLfloat top_radius, GLfloat height, GLuint slice_count,
					 GLuint stack_count)
{

}

void
geom_cylinder_bottomcap(struct mesh_data_t *const p_data, GLfloat bottom_radius,
						GLfloat top_radius, GLfloat height, GLuint slice_count,
						GLuint stack_count)
{

}

void geom_grid(struct mesh_data_t *const p_data, GLfloat width, GLfloat depth,
			   GLuint m, GLuint n)
{

}

// quad covering screen NDC coords. useful for postprocessing effects
void geom_ndc_quad(struct mesh_data_t *const p_data)
{

}

void geom_subdivide(struct mesh_data_t *const p_data)
{

}

void free_mesh_data(struct mesh_data_t *const p_data)
{
	free(p_data->vertices);
	free(p_data->indices);
}

inline void set_vertex_data(struct vertex_data_t *const p_data,
							GLfloat x, GLfloat y, GLfloat z, GLfloat nx,
							GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty,
							GLfloat tz, GLfloat u, GLfloat v)
{
	p_data->position[0] = x;
	p_data->position[1] = y;
	p_data->position[2] = z;

	p_data->normal[0] = nx;
	p_data->normal[1] = ny;
	p_data->normal[2] = nz;

	p_data->tangent[0] = tx;
	p_data->tangent[1] = ty;
	p_data->tangent[2] = tz;

	p_data->tex_coord[0] = u;
	p_data->tex_coord[1] = v;
}

