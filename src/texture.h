#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <stdbool.h>

GLuint texture_cubemap_load(const char *filenames[]);

#endif // TEXTURE_H
