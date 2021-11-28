#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GL/glew.h"
#include "cglm/cglm.h"

struct vertex_data_t {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec2 tex_coord;
};
typedef struct vertex_data_t VertexData;

struct mesh_data_t {
	struct vertex_data_t *vertices;
	GLuint *indices;
};
typedef struct mesh_data_t MeshData;

void geom_cube(struct mesh_data_t *const p_data, GLfloat width, GLfloat height,
			   GLfloat depth);
void geom_sphere(struct mesh_data_t *const p_data, GLfloat radius,
				 GLuint slice_count, GLuint stack_count);
void geom_cylinder(struct mesh_data_t *const p_data, GLfloat bottom_radius,
				   GLfloat top_radius, GLfloat height, GLuint slice_count,
				   GLuint stack_count);
void geom_grid(struct mesh_data_t *const p_data, GLfloat width, GLfloat depth,
			   GLuint m, GLuint n);
void geom_ndc_quad(struct mesh_data_t *const p_data);
void free_mesh_data(struct mesh_data_t *const p_data);

#endif // GEOMETRY_H
