#include "log.h"

static bool verbose_stdout;

bool log_open(const char *filename, bool verbose)
{
	verbose_stdout = verbose;
	pLogFile = fopen(filename, "w");
	if (pLogFile != NULL)
		return true;
	return false;
}

void log_write(enum LOG_TYPE type, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	FILE *pHandle = NULL;
	switch (type) {
	case LOG_MSG:
	case LOG_LOG:
		pHandle = stdout;
		break;
	case LOG_ERR:
		pHandle = stderr;
		break;
	default:
		pHandle = stdout;
	}
	vfprintf(pHandle, fmt, args);
	va_end(args);

	va_start(args, fmt);
	if (pLogFile != NULL)
		vfprintf(pLogFile, fmt, args);
	va_end(args);
}

bool log_close()
{
	if (fclose(pLogFile))
		return true;
	return false;
}

