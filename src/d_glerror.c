/* =============================================================================
** SimmeredEggsEngine, file: d_glerror.c Created 12/6/2021
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
#include "d_glerror.h"
#include "u_log.h"
#include <string.h>

GLenum D_glCheckError(const char *filename, int line) {
	GLenum errcode;
	while ((errcode = glGetError()) != GL_NO_ERROR) {
		char errbuf[50];
		switch (errcode) {
		case GL_INVALID_ENUM:
			strcpy(errbuf, "INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			strcpy(errbuf, "INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			strcpy(errbuf, "INVALID_OPERATION");
			break;
		case GL_STACK_OVERFLOW:
			strcpy(errbuf, "STACK_OVERFLOW");
			break;
		case GL_STACK_UNDERFLOW:
			strcpy(errbuf, "STACK_UNDERFLOW");
			break;
		case GL_OUT_OF_MEMORY:
			strcpy(errbuf, "OUT_OF_MEMORY");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			strcpy(errbuf, "INVALID_FRAMEBUFFER_OPERATION");
			break;
		}
		U_LogWrite(LOG_ERR, "%s|%s(%d)\n", errbuf, filename, line);
	}
	return errcode;
}

void D_glDebugCallback(GLenum source,
					   GLenum type,
					   GLuint id,
					   GLenum severity,
					   GLsizei length,
					   const GLchar *message,
					   const void *userparam) {
	const char *sourcebuf;
	const char *typebuf;
	const char *severitybuf;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
		sourcebuf = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourcebuf = "WINDOW_SYSTEM";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourcebuf = "SHADER_COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourcebuf = "THIRD_PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
		sourcebuf = "APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
		sourcebuf = "SOURCE_OTHER";
        break;
    default:
		sourcebuf = "";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
		typebuf = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typebuf = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typebuf = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
		typebuf = "TYPE_PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
		typebuf = "TYPE_PORTABILITY";
        break;
    case GL_DEBUG_TYPE_MARKER:
		typebuf = "TYPE_MARKER";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
		typebuf = "PUSH_GROUP";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
		typebuf = "POP_GROUP";
        break;
    case GL_DEBUG_TYPE_OTHER:
		typebuf = "OTHER";
        break;
    default:
		typebuf = "UNKNOWN";
        break;
    }

    switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		severitybuf = "HIGH";
		U_LogWrite(LOG_ERR, "GL_DEBUG(%d):%s:%s:%s:%s\n", id, severitybuf,
				  sourcebuf, typebuf, message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
	case GL_DEBUG_SEVERITY_LOW:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severitybuf = "NOTIFICATION";
		U_LogWrite(LOG_MSG, "GL_DEBUG(%d):%s:%s:%s:%s\n", id, severitybuf,
				  sourcebuf, typebuf, message);
        //U_LogWrite(LOG_MSG, "GL_DEBUG:%s\n", message);
		break;
	}
}

