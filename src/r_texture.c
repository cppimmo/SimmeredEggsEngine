/* =============================================================================
** SimmeredEggsEngine, r_texture.c Created 12/6/2021
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
#include "r_texture.h"
#include "u_log.h"
// god bless you stb!
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>

boolean R_CreateTexture(struct texture_t *texture, GLenum target) {
    texture->target = target;
	glCreateTextures(target, 1, &texture->id);
	if (glIsTexture(texture->id))
		return false;
	return true;
}

void R_DeleteTexture(struct texture_t *texture) {
	glDeleteTextures(1, &texture->id);
}

boolean R_CreateTextureArray(struct texture_t **texture, size_t count,
							 GLenum target) {
	for (size_t i = 0; i < count; ++i) {
		texture[i]->target = target;
		glCreateTextures(target, 1, &texture[i]->id);
		if (!glIsTexture(texture[i]->id))
			return false;
	}
	return true;
}

void R_DeleteTextureArray(struct texture_t **texture, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		glDeleteTextures(1, &texture[i]->id);
	}
}

GLuint R_LoadTexture2D(const char *filename) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // texture wrapping & filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    unsigned char *data = stbi_load(filename, &width, &height, &nr_channels, 0);
    if (data == NULL) {
	U_LogWrite(LOG_ERR, "Texture, %s, failed to load!", filename);
	stbi_image_free(data);
	return 0;
    } else {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
    }
    return texture;
}

// returns zero on failure
GLuint R_LoadTextureCubemap(const char *filenames[]) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nr_channels;
	// stbi_set_flip_vertically_on_load(true);
	for (size_t i = 0; i < 6; ++i) {
		unsigned char *data = stbi_load(filenames[i], &width, &height,
										&nr_channels, 0);
		if (data != NULL) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
						 data);
			stbi_image_free(data);
		} else {
			U_LogWrite(LOG_ERR, "Failed to load texture: %s\n", filenames[i]);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // stbi_set_flip_vertically_on_load(false);
	return 0;
}

