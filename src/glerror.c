#include "glerror.h"
#include "log.h"
#include <string.h>

void gl_debug_callback(GLenum source,
					GLenum type,
					GLuint id,
					GLenum severity,
					GLsizei length,
					const GLchar *message,
					const void *user_param)
{
	char source_buf[20];
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        strcpy(source_buf, "API");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        strcpy(source_buf, "WINDOW_SYSTEM");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        strcpy(source_buf, "SHADER_COMPILER");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        strcpy(source_buf, "THIRD_PARTY");
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        strcpy(source_buf, "APPLICATION");
        break;
    case GL_DEBUG_SOURCE_OTHER:
        strcpy(source_buf, "OTHER");
        break;
    default:
        break;
    }

	char type_buf[25];
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        strcpy(type_buf, "ERROR");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        strcpy(type_buf, "DEPRECEATED_BEHAVIOR");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        strcpy(type_buf, "UNDEFINED_BEHAVIOR");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        strcpy(type_buf, "PERFORMANCE");
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        strcpy(type_buf, "PORTABILITY");
        break;
    case GL_DEBUG_TYPE_MARKER:
        strcpy(type_buf, "MARKER");
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        strcpy(type_buf, "PUSH_GROUP");
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        strcpy(type_buf, "POP_GROUP");
        break;
    case GL_DEBUG_TYPE_OTHER:
        strcpy(type_buf, "OTHER");
        break;
    default:
        break;
    }

	char severity_buf[15];
    switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		strcpy(severity_buf, "HIGH");
		log_write(LOG_ERR, "GLDEBUG:%s:%s:%s:%s", severity_buf,
				  source_buf, type_buf, message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
	case GL_DEBUG_SEVERITY_LOW:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		strcpy(severity_buf, "NOTIFICATION");
		log_write(LOG_MSG, "GLDEBUG:%s:%s:%s:%s", severity_buf,
				  source_buf, type_buf, message);
		break;
	}	
}

