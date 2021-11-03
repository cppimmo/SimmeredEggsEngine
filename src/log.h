#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define LOG_FILE "log.txt"
static FILE *pLogFile = NULL;

enum LOG_TYPE {
	LOG_MSG,
	LOG_LOG,
	LOG_ERR,
};

bool log_open(const char *filename, bool verbose);
// wrapper function for fprintf
void log_write(enum LOG_TYPE type, const char *fmt, ...);
bool log_close();

#endif // LOG_H
