#include "log.h"
#include <stdarg.h>

bool LogOpen(const char *filename)
{
	if ((pLogFile = fopen(LOG_FILE, "w")))
		return true;
	return false;
}

void LogWrite(const char *str)
{
	fprintf(pLogFile, str);
}

bool LogClose()
{
	if (fclose(pLogFile))
		return true;
	return false;
}
