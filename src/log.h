#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include "u_utility.h"
#include <stdarg.h>

#define LOG_FILE "log.txt"

enum LOG_TYPE {
	LOG_MSG = 0,
	LOG_LOG,
	LOG_ERR,
};

boolean log_open(const char *filename, boolean verbose);
// wrapper function for fprintf
void log_write(enum LOG_TYPE type, const char *fmt, ...);
boolean log_close();

#endif // LOG_H
