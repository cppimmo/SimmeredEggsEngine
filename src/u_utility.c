#include "u_utility.h"
#include "u_log.h"

#ifdef __unix__
#include <sys/statvfs.h>
#endif

inline void *U_Malloc(size_t size) {
	void *ptr = malloc(size);
#ifndef NDEBUG
	if (ptr == NULL) {
		U_LogWrite(LOG_ERR, "Failed to allocated %d bytes!", size);
	} else {
		U_LogWrite(LOG_MSG, "Allocated %d bytes, at %p.", size, ptr);
	}
#endif
	return ptr;
}

inline void U_Free(void *ptr) {
	free(ptr);
#ifndef NDEBUG
	if (ptr == NULL) {
		U_LogWrite(LOG_MSG, "Memory located at %p freed.", ptr);
	} else {
		U_LogWrite(LOG_ERR, "Memory located at %p not freed!", ptr);
	}
#endif
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

