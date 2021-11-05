#include "texture.h"
#include "stb_image.h"
#incldue "log.h"
#include <stdlib.h>

// returns zero on failure
GLuint texture_cubemap_load(const char *filenames[])
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nr_channels;
	// stbi_set_flip_vertically_on_load(true);
	for (size_t i = 0; i < 6; ++i) {
		unsigned char *data = stbi_load(filenames[i], &width, &height,
										&nr_channels);
		if (data != NULL) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB GL_UNSIGNED_BYTE,
						 data);
			stbi_image_free(data);
		} else {
			log_write(LOG_ERR, "Failed to load texture: %s\n", filenames[i]);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

