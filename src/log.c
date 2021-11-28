#include "log.h"

static bool verbose_stdout;
static FILE *p_log_file = NULL;

bool log_open(const char *filename, bool verbose)
{
	verbose_stdout = verbose;
	p_log_file = fopen(filename, "w");
	if (p_log_file != NULL)
		return true;
	return false;
}

void log_write(enum LOG_TYPE type, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	FILE *p_handle = NULL;
	switch (type) {
	case LOG_MSG:
	case LOG_LOG:
		p_handle = stdout;
		break;
	case LOG_ERR:
		p_handle = stderr;
		break;
	default:
		p_handle = stdout;
	}
	vfprintf(p_handle, fmt, args);
	va_end(args);

	va_start(args, fmt);
	if (p_log_file != NULL)
		vfprintf(p_log_file, fmt, args);
	va_end(args);
}

bool log_close()
{
	if (fclose(p_log_file))
		return true;
	return false;
}

