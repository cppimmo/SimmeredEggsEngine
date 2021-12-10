/* =============================================================================
** SimmeredEggsEngine, file: u_utility.c Created 12/6/2021
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
#include "u_utility.h"
#include "u_log.h"

#ifdef __OS_UNIX__
#include <sys/statvfs.h>
#endif
#ifdef __OS_WINDOWS__
#include "winclude.h"
#endif

inline void *U_Malloc(size_t size) {
	void *ptr = malloc(size);
#ifndef NDEBUG
	if (ptr == NULL) {
		U_LogWrite(LOG_ERR, "Failed to allocated %d bytes!\n", size);
	} else {
		U_LogWrite(LOG_MSG, "Allocated %d bytes, at %p.\n", size, ptr);
	}
#endif
	return ptr;
}

inline void U_Free(void *ptr) {
	free(ptr);
#ifndef NDEBUG
	if (ptr == NULL) {
		U_LogWrite(LOG_MSG, "Memory located at %p freed.\n", ptr);
	} else {
		U_LogWrite(LOG_ERR, "Memory located at %p not freed!\n", ptr);
	}
#endif
}

int U_RandomInt(int minval, int maxval) {
	static boolean hasran = false;
	if (!hasran) {
		hasran = true;
		srand(time(NULL));
	}
	return minval + rand() & (maxval + 1 - minval);
}

float U_RandomFloat(float minval, float maxval) {
	return (float)U_RandomInt(minval, maxval);
}

double U_RandomDouble(double minval, double maxval) {
	return (double)U_RandomInt(minval, maxval);
}

int U_RandomColorUnsignedChar(void) {
	return U_RandomInt(0, 255);
}

float U_RandomColorNormalizedFloat(void) {
	return 0.0f;
}

// use UNIX: https://rosettacode.org/wiki/Determine_if_only_one_instance_is_running#C
boolean U_InstanceFileLock(void) {
	return true;
}

boolean U_IsOnlyInstance(void) {
	return true;
}

boolean U_InstanceFileUnlock(void) {
	return true;
}

// check if the storage is available in path
// path value does not matter on windows
boolean U_CheckStorage(const char *path, const unsigned long long needed) {
	boolean retval = false;
#if __OS_UNIX__
	struct statvfs stat;

	if (statvfs(path, &stat) != 0) {
		U_LogWrite(LOG_ERR, "Call to statvfs failed.");
		retval = false;
	}
	// size in bytes
	const unsigned long available = stat.f_bsize * stat.f_bavail;
	if (available < needed)
		retval = false;
	else
		retval = true;
#elif defined(__OS_WINDOWS__)
	int const drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededclusters = needed /
		(diskfree.sectors_per_cluster * diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededclusters) {
		// if you get here you don't have enough disk space!
		U_LogWrite(LOG_ERR, "Not enough disk space available!");
		retval = false;
	}
#endif
	return retval;
}

unsigned long U_GetCPUSpeed(void) {
#ifdef __OS_LINUX__
	// read /proc/cpuinfo

#elif defined(__OS_FREEBSD__)

#elif defined(__OS_WINDOWS__)

#endif
	return 0;
}

