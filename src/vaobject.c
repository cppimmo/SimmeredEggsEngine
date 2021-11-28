#include "vaobject.h"

boolean vao_create(struct vertex_array_t *p_vao)
{
	glCreateVertexArrays(1, &p_vao->id);
	if (!glIsVertexArray(p_vao->id))
		return false;
	return true;
}

// creating vertex arrays from arrays. needs work
boolean vao_create_arr(struct vertex_array_t **p_vao, size_t count)
{
	for (size_t i = 0; i < count; ++i) {
		glCreateVertexArrays(count, &p_vao[i]->id);
		if (!glIsVertexArray(p_vao[i]->id))
			return false;
	}
	return true;
}

void vao_delete(struct vertex_array_t *p_vao)
{
	glDeleteVertexArrays(1, &p_vao->id);
}

void vao_delete_arr(struct vertex_array_t **p_vao, size_t count)
{
	for (size_t i = 0; i < count; ++i) {
		glDeleteVertexArrays(1, &p_vao[i]->id);
	}
}

inline void vao_bind(struct vertex_array_t *p_vao)
{
	glBindVertexArray(p_vao->id);
}

inline void vao_unbind(struct vertex_array_t *p_vao)
{
	glBindVertexArray(0);
}

/* normalized parameter can be given dummy values when using types: integer and
   long double */
void vao_attrib_ptr(struct vertex_array_t *p_vao, struct vertex_buffer_t *p_vbo,
					GLuint index, GLint size, GLenum type, GLboolean normalized,
					GLsizei stride, size_t offset)
{
	vao_bind(p_vao);
	vbo_bind(p_vbo);

	switch (type) {
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_INT_2_10_10_10_REV:
	case GL_UNSIGNED_INT_2_10_10_10_REV:
 		// signed and unsigned integral version
		glVertexAttribIPointer(index, size, type, stride, (void*)offset);
		break;
	case GL_DOUBLE:
		// 64-bit floating point version
		glVertexAttribLPointer(index, size, type, stride, (void*)offset);
		break;
	default:
		// regular floating point version
		glVertexAttribPointer(index, size, type, normalized, stride,
							  offset);
		break;
	}
	//vao_unbind(p_vao);
	//vbo_unbind(p_vbo);
}

inline void vao_attrib_enable(const GLuint index)
{
	glEnableVertexAttribArray(index);
}

inline void vao_atrrib_disable(const GLuint index)
{
	glDisableVertexAttribArray(index);
}

