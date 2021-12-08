/* =============================================================================
** SimmeredEggsEngine, file: r_shader.h Created 12/6/2021
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
#ifndef __R_SHADER_H__
#define __R_SHADER_H__

#include "GL/glew.h"
#include "cglm/cglm.h"
#include "u_utility.h"

#include <stdlib.h>

/* all shader source files are presumed to be in this directory, thus do not
   supply a leading directory for filenames */
#define SHADER_DIR "assets/shaders/"

struct shaderuniform_t {
	GLuint location;
	const GLchar *name;
};

struct shaderinfo_t {
	GLenum type;
	const char *filename;
	GLuint shader;
};

// load program from an array of shader_info_t
boolean R_CreateProgram(GLuint *program, struct shaderinfo_t *shaders, size_t length);
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
