#include "glerror.h"
#include "log.h"
#include <string.h>

GLenum gl_check_error(const char *filename, int line)
{
	GLenum error_code;
	while ((error_code = glGetError()) != GL_NO_ERROR) {
		char errbuf[50];
		switch (error_code) {
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
		log_write(LOG_ERR, "%s|%s(%d)\n", errbuf, filename, line);
	}
	return error_code;
}

void gl_debug_callback(GLenum source,
					GLenum type,
					GLuint id,
					GLenum severity,
					GLsizei length,
					const GLchar *message,
					const void *user_param)
{
	const char *source_buf;
	const char *type_buf;
	const char *severity_buf;
	
    switch (source) {
    case GL_DEBUG_SOURCE_API:
		source_buf = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		source_buf = "WINDOW_SYSTEM";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
		source_buf = "SHADER_COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
		source_buf = "THIRD_PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
		source_buf = "APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
		source_buf = "SOURCE_OTHER";
        break;
    default:
		source_buf = "";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
		type_buf = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type_buf = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type_buf = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
		type_buf = "TYPE_PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
		type_buf = "TYPE_PORTABILITY";
        break;
    case GL_DEBUG_TYPE_MARKER:
		type_buf = "TYPE_MARKER";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
		type_buf = "PUSH_GROUP";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
		type_buf = "POP_GROUP";
        break;
    case GL_DEBUG_TYPE_OTHER:
		type_buf = "OTHER";
        break;
    default:
		type_buf = "UNKNOWN";
        break;
    }

    switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		severity_buf = "HIGH";
		log_write(LOG_ERR, "GL_DEBUG(%d):%s:%s:%s:%s\n", id, severity_buf,
				  source_buf, type_buf, message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
	case GL_DEBUG_SEVERITY_LOW:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severity_buf = "NOTIFICATION";
		log_write(LOG_MSG, "GL_DEBUG(%d):%s:%s:%s:%s\n", id, severity_buf,
				  source_buf, type_buf, message);
        //log_write(LOG_MSG, "GL_DEBUG:%s\n", message);
		break;
	}
}

