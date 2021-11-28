#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <stdlib.h>
#include "u_utility.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

GLuint texture_2d_load(const char *filename);
GLuint texture_cubemap_load(const char *filenames[]);

#endif // TEXTURE_H
