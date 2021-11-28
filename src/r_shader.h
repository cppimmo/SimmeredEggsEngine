#ifndef __R_SHADER_H__
#define __R_SHADER_H__

#include "GL/glew.h"
#include "cglm/cglm.h"
#include <stdlib.h>
#include "u_utility.h"

struct shader_uniform_t {
	GLuint location;
	const GLchar *name;
};

struct shader_info_t {
	GLenum type;
	const char *filename;
	GLuint shader;
};

// load program from an array of shader_info_t
boolean R_CreateProgram(GLuint *program, struct shader_info_t *shaders, size_t length);
// if return is zero then error
GLuint R_CreateShader(GLenum type);
// check to see if shader already exists
boolean R_IsShader(GLuint shader);
void R_DeleteShader(GLuint *shader);
boolean R_IsProgram(GLuint program);
void R_UseProgram(GLuint program);
void R_DeleteProgram(GLuint program);
// program uniform setter functions
// returns false on failure
boolean R_UniformBoolean(GLuint program, const char *name, boolean value);
boolean R_UniformFloat(GLuint program, const char *name, float value);
boolean R_UniformInt(GLuint program, const char *name, int value);
boolean R_UniformVec2(GLuint program, const char *name, const vec2 value);
boolean R_UniformVec3(GLuint program, const char *name, const vec3 value);
boolean R_UniformVec4(GLuint program, const char *name, const vec4 value);
boolean R_UniformMat2(GLuint program, const char *name, const mat2 value);
boolean R_UniformMat3(GLuint program, const char *name, const mat3 value);
boolean R_UniformMat4(GLuint program, const char *name, const mat4 value);
// program uniform getter functions
// returns false on failure
boolean R_GetUniformBoolean(GLuint program, const char *name, boolean *value);
boolean R_GetUniformFloat(GLuint program, const char *name, float *value);
boolean R_GetUniformInt(GLuint program, const char *name, int *value);
boolean R_GetUniformVec2(GLuint program, const char *name, const vec2 *value);
boolean R_GetUniformVec3(GLuint program, const char *name, const vec3 *value);
boolean R_GetUniformVec4(GLuint program, const char *name, const vec4 *value);
boolean R_GetUniformMat2(GLuint program, const char *name, const mat2 *value);
boolean R_GetUniformMat3(GLuint program, const char *name, const mat3 *value);
boolean R_GetUniformMat4(GLuint program, const char *name, const mat4 *value);

#endif
