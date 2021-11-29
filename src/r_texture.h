#ifndef __R_TEXTURE_H__
#define __R_TEXTURE_H__

#include "GL/glew.h"
#include "u_utility.h"

GLuint R_LoadTexture2D(const char *filename);
GLuint R_LoadTextureCubemap(const char *filenames[]);

#endif
