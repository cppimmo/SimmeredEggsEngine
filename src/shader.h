#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include "cglm/cglm.h"
#include <stdlib.h>
#include <stdbool.h>

struct shader_uniform_t {
	GLuint location;
	const GLchar *name;
};
typedef struct shader_uniform_t ShaderUniform;

struct shader_info_t {
	GLenum type;
	const char *filename;
	GLuint shader;
};
typedef struct shader_info_t ShaderInfo;

// load program from an array of shader_info_t
bool program_create(GLuint *program, struct shader_info_t *shaders, size_t length);
// if return is zero then error
GLuint shader_create(GLenum type);
// check to see if shader already exists
bool shader_occupied(GLuint shader);
void shader_delete(GLuint *p_shader);
bool program_occupied(GLuint program);
void program_use(GLuint program);
void program_delete(GLuint program);

// program uniform setter functions
// returns false on failure
bool uniform_bool(GLuint program, const char *name, bool value);
bool uniform_float(GLuint program, const char *name, float value);
bool uniform_int(GLuint program, const char *name, int value);
bool uniform_vec2(GLuint program, const char *name, const vec2 value);
bool uniform_vec3(GLuint program, const char *name, const vec3 value);
bool uniform_vec4(GLuint program, const char *name, const vec4 value);
bool uniform_mat2(GLuint program, const char *name, const mat2 value);
bool uniform_mat3(GLuint program, const char *name, const mat3 value);
bool uniform_mat4(GLuint program, const char *name, const mat4 value);

// program uniform getter functions
// returns false on failure
bool get_uniform_bool(GLuint program, const char *name, bool *value);
bool get_uniform_float(GLuint program, const char *name, float *value);
bool get_uniform_int(GLuint program, const char *name, int *value);
bool get_uniform_vec2(GLuint program, const char *name, const vec2 *value);
bool get_uniform_vec3(GLuint program, const char *name, const vec3 *value);
bool get_uniform_vec4(GLuint program, const char *name, const vec4 *value);
bool get_uniform_mat2(GLuint program, const char *name, const mat2 *value);
bool get_uniform_mat3(GLuint program, const char *name, const mat3 *value);
bool get_uniform_mat4(GLuint program, const char *name, const mat4 *value);
	
#endif // SHADER_H
