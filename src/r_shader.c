#include "r_shader.h"
#include "u_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const GLchar *ShaderSource(const char *filename);
static boolean ShaderCompileStatus(GLuint shader);
static boolean ProgramLinkStatus(GLuint program);

boolean R_CreateProgram(GLuint *program, struct shader_info_t *shaders,
						size_t length) {
	if (shaders == NULL) {
		U_LogWrite(LOG_ERR, "You didn't pass in a shader array!\n");
		return false;
	}
	*program = glCreateProgram();

	for (size_t i = 0; i <= length - 1; ++i) {
		struct shader_info_t *shader = &shaders[i];
		shader->shader = R_CreateShader(shader->type);

		// check if the shader was actually created
		if (!R_IsShader(shader->shader)) {
			U_LogWrite(LOG_ERR, "Failed to create shader i=%d;%s\n", i,
					  shader->filename);
			for (size_t j = length - 1; j > 0; j--) {
				glDeleteShader(shaders[j].shader);
			}
			return false;
		}

		const GLchar *source = ShaderSource(shader->filename);
		if (source == NULL) {
			U_LogWrite(LOG_ERR, "Failed to source shader i=%d;%s\n", i,
					  shader->filename);
			// shader_delete on previously created shaders
			for (size_t j = length - 1; j > 0; j--) {
				glDeleteShader(shaders[j].shader);
			}
			return false;
		}

		glShaderSource(shader->shader, 1, &source, NULL);
		free(source);

		glCompileShader(shader->shader);
		if (!ShaderCompileStatus(shader->shader)) {
			// shader_delete on previously created shaders
			for (size_t j = length - 1; j > 0; j--) {
				glDeleteShader(shaders[j].shader);
			}
			return false;
		}
		glAttachShader(*program, shader->shader);
	}

	glLinkProgram(*program);
	if (!ProgramLinkStatus(*program)) {
		for (size_t i = 0; i <= length - 1; ++i) {
			glDeleteShader(shaders[i].shader);
		}
		return false;
	}
	return true;
}

// if return is zero then error
inline GLuint R_CreateShader(GLenum type) {
	return glCreateShader(type);
}

const GLchar *ShaderSource(const char *filename) {
	FILE *p_handle = fopen(filename, "rb");
	if (!p_handle) {
		U_LogWrite(LOG_ERR, "Failure loading shader source from %s!\n", filename);
		return NULL;
	}

	fseek(p_handle, 0, SEEK_END);
	size_t length = ftell(p_handle);
	fseek(p_handle, 0, SEEK_SET);

	GLchar *source = (GLchar *)malloc(length + 1);

	fread(source, 1, length, p_handle);
	if (fclose(p_handle) == EOF) {
		U_LogWrite(LOG_ERR, "Failure closing shader file: %s!", filename);
		free(source);
		return NULL;
	}

	source[length] = 0;
	return (const GLchar *)source;
}

// check to see if shader already exists
boolean R_IsShader(GLuint shader) {
	return glIsShader(shader);
}

// check to see if program already exists
boolean R_IsProgram(GLuint program) {
	return glIsProgram(program);
}

void R_DeleteShader(GLuint *shader) {
	glDeleteShader(*shader);
	// set value of shader to zero
	*shader = 0;
}

void R_UseProgram(GLuint program) {
	glUseProgram(program);
}

void R_DeleteProgram(GLuint program) {
	glDeleteProgram(program);
}

boolean R_UniformBoolean(GLuint program, const char *name, boolean value) {
	if (!R_IsProgram(program))
		return false;
	glUniform1i(glGetUniformLocation(program, name), (int)value);
	return true;
}

boolean R_UniformFloat(GLuint program, const char *name, float value) {
	if (!R_IsProgram(program))
		return false;
	glUniform1f(glGetUniformLocation(program, name), value);
	return true;
}

boolean R_UniformInt(GLuint program, const char *name, int value) {
	if (!R_IsProgram(program))
		return false;
	glUniform1i(glGetUniformLocation(program, name), value);
	return true;
}

boolean R_UniformVec2(GLuint program, const char *name, const vec2 value) {
	if (!R_IsProgram(program))
		return false;
	glUniform2fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

boolean R_UniformVec3(GLuint program, const char *name, const vec3 value) {
	if (!R_IsProgram(program))
		return false;
	glUniform3fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

boolean R_UniformVec4(GLuint program, const char *name, const vec4 value) {
	if (!R_IsProgram(program))
		return false;
	glUniform4fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

boolean R_UniformMat2(GLuint program, const char *name, const mat2 value) {
	if (!R_IsProgram(program))
		return false;
	glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE,
					   value[0]);
	return true;
}

boolean R_UniformMat3(GLuint program, const char *name, const mat3 value) {
	if (!R_IsProgram(program))
		return false;
	glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE,
					   value[0]);
	return true;
}

boolean R_UniformMat4(GLuint program, const char *name, const mat4 value) {
	if (!R_IsProgram(program))
		return false;
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE,
					   value[0]);
	return true;
}

boolean R_GetUniformBoolean(GLuint program, const char *name, boolean *value) {
	return true;
}

boolean R_GetUniformFloat(GLuint program, const char *name, float *value) {
	return true;
}

boolean R_GetUniformInt(GLuint program, const char *name, int *value) {
	return true;
}

boolean R_GetUniformVec2(GLuint program, const char *name, const vec2 *value) {
	return true;
}

boolean R_GetUniformVec3(GLuint program, const char *name, const vec3 *value) {
	return true;
}

boolean R_GetUniformVec4(GLuint program, const char *name, const vec4 *value) {
	return true;
}

boolean R_GetUniformMat2(GLuint program, const char *name, const mat2 *value) {
	return true;
}

boolean R_GetUniformMat3(GLuint program, const char *name, const mat3 *value) {
	return true;
}

boolean R_GetUniformMat4(GLuint program, const char *name, const mat4 *value) {
	return true;
}

// returns true on success, false on failure
static boolean ShaderCompileStatus(GLuint shader) {
	int status;
	char typebuf[25];
	GLsizei length = 0;
	GLchar *logbuf = NULL;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	int type;
	glGetShaderiv(shader, GL_SHADER_TYPE, &type);
	switch (type) {
	case GL_VERTEX_SHADER:
		strcpy(typebuf, "VERTEX");
		break;
	case GL_FRAGMENT_SHADER:
		strcpy(typebuf, "FRAGMENT");
		break;
	case GL_TESS_CONTROL_SHADER:
		strcpy(typebuf, "TESS CONTROL");
		break;
	case GL_TESS_EVALUATION_SHADER:
		strcpy(typebuf, "TESS EVALUATION");
		break;
	case GL_GEOMETRY_SHADER:
		strcpy(typebuf, "GEOMETRY");
		break;
	case GL_COMPUTE_SHADER:
		strcpy(typebuf, "COMPUTE");
		break;
	default:
		strcpy(typebuf, "UNKNOWN");
	}
	if (!status) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		logbuf = (GLchar *)malloc((length + 1) * sizeof(GLchar *));
		glGetShaderInfoLog(shader, length, &length, logbuf);
		U_LogWrite(LOG_ERR, "%s shader compilation failed: \n%s\n", typebuf, logbuf);

		free(logbuf);
		return false;
	}
	return true;
}

// returns true on success, false on failure
static boolean ProgramLinkStatus(GLuint program) {
	int status;
	GLsizei length = 0;
	GLchar *logbuf = NULL;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		logbuf = (GLchar *)malloc(length + 1);
		glGetProgramInfoLog(program, length, &length, logbuf);
		U_LogWrite(LOG_ERR, "Shader program LINK failed: \n%s\n", logbuf);
		free(logbuf);
		return false;
	}
	return true;
}

