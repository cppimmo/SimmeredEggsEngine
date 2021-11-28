#include "r_indexbuffer.h"

boolean R_CreateIndexBuffer(struct index_buffer_t *p_ibo, GLboolean dynamic) {
	return true;
}

void R_DeleteIndexBuffer(struct index_buffer_t *p_ibo) {

}

boolean R_CreateIndexBufferArray(struct index_buffer_t **p_ibo, size_t count,
								 GLboolean dynamic) {
	return true;
}

void R_DeleteIndexBufferArray(struct index_buffer_t **p_ibo, size_t count) {

}

void R_BindIndexBuffer(struct index_buffer_t *p_ibo) {

}

void R_UnbindIndexBuffer(struct index_buffer_t *p_ibo) {

}

void R_IndexBufferStorage(struct index_buffer_t *p_ibo, GLsizeiptr size,
						  const void *data) {

}

void R_IndexBufferData(struct index_buffer_t *p_ibo, GLsizeiptr size,
					   const void *data) {

}

