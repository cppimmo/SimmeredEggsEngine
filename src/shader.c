#include "shader.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool program_create(GLuint *program, struct shader_info_t *shaders, size_t length)
{
	if (shaders == NULL) {
		log_write(LOG_ERR, "You didn't pass in a shader array!\n");
		return false;
	}
	*program = glCreateProgram();

	for (size_t i = 0; i <= length - 1; ++i) {
		struct shader_info_t *p_shader = &shaders[i];
		p_shader->shader = shader_create(p_shader->type);
		
		// check if the shader was actually created
		if (!shader_occupied(p_shader->shader)) {
			log_write(LOG_ERR, "Failed to create shader i=%d;%s\n", i,
					  p_shader->filename);
			for (size_t j = length; j >= 0; j--) {
				shader_delete(&shaders[j].shader);
			}
			return false;
		}

		const GLchar *source = shader_source(p_shader->filename);
		if (source == NULL) {
			log_write(LOG_ERR, "Failed to source shader i=%d;%s\n", i,
					  p_shader->filename);
			// shader_delete on previously created shaders
			for (size_t j = length; j >= 0; j--) {
				shader_delete(&shaders[j].shader);
			}
			return false;
		}

		glShaderSource(p_shader->shader, 1, &source, NULL);
		free(source);

		glCompileShader(p_shader->shader);
		if (!shader_compile_status(p_shader->shader)) {
			// shader_delete on previously created shaders
			for (size_t j = length; j >= 0; j--) {
				shader_delete(&shaders[j].shader);
			}
			return false;
		}
		glAttachShader(*program, p_shader->shader);
	}

	glLinkProgram(*program);
	if (!program_link_status(*program)) {
		for (size_t i = 0; i <= length - 1; ++i) {
			shader_delete(&shaders[i].shader);
		}
		return false;
	}
	return true;
}

// if return is zero then error
GLuint shader_create(GLenum type)
{
	return glCreateShader(type);
}

static const GLchar *shader_source(const char *filename)
{
	FILE *p_handle = fopen(filename, "rb");
	if (!p_handle) {
		log_write(LOG_ERR, "Failure loading shader source from %s!\n", filename);
		return NULL;
	}

	fseek(p_handle, 0, SEEK_END);
	size_t length = ftell(p_handle);
	fseek(p_handle, 0, SEEK_SET);
	
	GLchar *source = (GLchar *)malloc(length + 1);

	fread(source, 1, length, p_handle);
	if (fclose(p_handle) == EOF) {
		log_write(LOG_ERR, "Failure closing shader file: %s!", filename);
		free(source);
		return NULL;
	}

	source[length] = 0;
	return (const GLchar *)source;
}

// check to see if shader already exists
bool shader_occupied(GLuint shader)
{
	return glIsShader(shader);
}

// check to see if program already exists
bool program_occupied(GLuint program)
{
	return glIsProgram(program);
}

void shader_delete(GLuint *p_shader)
{
	glDeleteShader(*p_shader);
	// set value of shader to zero
	*p_shader = 0;
}

void program_use(GLuint program)
{
	glUseProgram(program);
}

void program_delete(GLuint program)
{
	glDeleteProgram(program);
}

bool uniform_bool(GLuint program, const char *name, bool value)
{
	if (!program_occupied(program))
		return false;
	glUniform1i(glGetUniformLocation(program, name), (int)value);
	return true;
}

bool uniform_float(GLuint program, const char *name, float value)
{
	if (!program_occupied(program))
		return false;
	glUniform1f(glGetUniformLocation(program, name), value);
	return true;
}

bool uniform_int(GLuint program, const char *name, int value)
{
	if (!program_occupied(program))
		return false;
	glUniform1i(glGetUniformLocation(program, name), value);
	return true;
}

bool uniform_vec2(GLuint program, const char *name, const vec2 value)
{
	if (!program_occupied(program))
		return false;
	glUniform2fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

bool uniform_vec3(GLuint program, const char *name, const vec3 value)
{
	if (!program_occupied(program))
		return false;
	glUniform3fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

bool uniform_vec4(GLuint program, const char *name, const vec4 value)
{
	if (!program_occupied(program))
		return false;
	glUniform4fv(glGetUniformLocation(program, name), 1, value);
	return true;
}

bool uniform_mat2(GLuint program, const char *name, const mat2 value)
{
	if (!program_occupied(program))
		return false;
	glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE, value[0]);
	return true;
}

bool uniform_mat3(GLuint program, const char *name, const mat3 value)
{
	if (!program_occupied(program))
		return false;
	glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, value[0]);
	return true;
}

bool uniform_mat4(GLuint program, const char *name, const mat4 value)
{
	if (!program_occupied(program))
		return false;
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, value[0]);
	return true;
}

bool get_uniform_bool(GLuint program, const char *name, bool *value)
{
	return true;
}

bool get_uniform_float(GLuint program, const char *name, float *value)
{
	return true;
}

bool get_uniform_int(GLuint program, const char *name, int *value)
{
	return true;
}

bool get_uniform_vec2(GLuint program, const char *name, const vec2 *value)
{
	return true;
}

bool get_uniform_vec3(GLuint program, const char *name, const vec3 *value)
{
	return true;
}

bool get_uniform_vec4(GLuint program, const char *name, const vec4 *value)
{
	return true;
}

bool get_uniform_mat2(GLuint program, const char *name, const mat2 *value)
{
	return true;
}

bool get_uniform_mat3(GLuint program, const char *name, const mat3 *value)
{
	return true;
}

bool get_uniform_mat4(GLuint program, const char *name, const mat4 *value)
{
	return true;
}

// returns true on success, false on failure
bool shader_compile_status(GLuint shader)
{
	int status;
	char typebuf[25];
	GLsizei log_length = 0;
	GLchar *logbuf = NULL;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	int shader_type;
	glGetShaderiv(shader, GL_SHADER_TYPE, &shader_type);
	switch (shader_type) {
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
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		logbuf = (GLchar *)malloc(log_length + 1);
		glGetShaderInfoLog(shader, log_length, &log_length, logbuf);
		log_write(LOG_ERR, "%s shader compilation failed: \n%s\n", typebuf, logbuf);
		free(logbuf);
		return false;
	}
	return true;
}

// returns true on success, false on failure
bool program_link_status(GLuint program)
{
	int status;
	GLsizei log_length = 0;
	GLchar *logbuf = NULL;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

		logbuf = (GLchar *)malloc(log_length + 1);
		glGetProgramInfoLog(program, log_length, &log_length, logbuf);
		log_write(LOG_ERR, "Shader program LINK failed: \n%s\n", logbuf);	
		free(logbuf);
		return false;
	}
	return true;
}

