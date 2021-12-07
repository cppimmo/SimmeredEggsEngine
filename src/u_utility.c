#include "u_utility.h"
#include "u_log.h"

#ifdef __unix__
#include <sys/statvfs.h>
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
#if __unix__
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
#elif _WIN32
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
	return 0;
}

