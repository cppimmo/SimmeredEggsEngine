#include "u_log.h"

static boolean verbosestdout;
static FILE *loghandle = NULL;

boolean U_LogOpen(const char *filename, boolean verbose) {
	verbosestdout = verbose;
	loghandle = fopen(filename, "w");
	if (loghandle != NULL)
		return true;
	return false;
}

void U_LogWrite(enum logtype_t type, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	FILE *handle = NULL;
	switch (type) {
	case LOG_MSG:
	case LOG_LOG:
		handle = stdout;
		break;
	case LOG_ERR:
		handle = stderr;
		break;
	default:
		handle = stdout;
	}
	vfprintf(handle, fmt, args);
	va_end(args);

	va_start(args, fmt);
	if (loghandle != NULL)
		vfprintf(loghandle, fmt, args);
	va_end(args);
}

boolean U_LogClose(void) {
	if (fclose(loghandle))
		return true;
	return false;
}

