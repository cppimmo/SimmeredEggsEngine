#ifndef __U_LOG_H__
#define __U_LOG_H__

#include "u_utility.h"

#include <stdio.h>
#include <stdarg.h>

#define LOG_FILE "log.txt"

enum logtype_t {
	LOG_MSG = 0,
	LOG_LOG,
	LOG_ERR,
};

boolean U_LogOpen(const char *filename, boolean verbose);
void U_LogWrite(enum logtype_t type, const char *fmt, ...);
boolean U_LogClose(void);

#endif
