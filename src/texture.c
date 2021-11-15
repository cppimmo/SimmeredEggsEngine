#include "texture.h"
#include "log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint texture_2d_load(const char *filename)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // texture wrapping & filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    unsigned char *data = stbi_load(filename, &width, &height, &nr_channels, 0);
    if (data == NULL) {
	log_write(LOG_ERR, "Texture, %s, failed to load!", filename);
	stbi_image_free(data);
	return 0;
    } else {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
    }
    return texture;
}

// returns zero on failure
GLuint texture_cubemap_load(const char *filenames[])
{
	/*	GLuint texture;
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
			log_write(LOG_ERR, "Failed to load texture: %s\n", filenames[i]);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	*/
	return 0;
}

