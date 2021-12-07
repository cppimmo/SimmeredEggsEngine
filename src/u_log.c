/* =============================================================================
** SimmeredEggsEngine, file: u_log.c Created 12/6/2021
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
#include "u_log.h"

#include <time.h>

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
	// const time_t curtime = time(NULL);
	// struct tm *loctime = localtime(&curtime);
	// vfprintf(handle, "%s", asctime(loctime));
	vfprintf(handle, fmt, args);
	va_end(args);

	va_start(args, fmt);
	if (loghandle != NULL) {
		// vfprintf(handle, "%s", asctime(loctime));
		vfprintf(loghandle, fmt, args);
	}
	va_end(args);
}

boolean U_LogClose(void) {
	if (fclose(loghandle))
		return true;
	return false;
}

