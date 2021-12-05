#ifndef __U_UTILITY_H__
#define __U_UTILITY_H__

#include <stdlib.h>

// phooey on you GCC!
#undef bool
#undef true
#undef false
#undef TRUE
#undef FALSE

#define INSTANCE_FILE "/tmp/see_instance"

enum boolean_t {
	false,
	true,
};
typedef enum boolean_t boolean;

void *U_Malloc(size_t size);
void U_Free(void *ptr);
boolean U_InstanceFileLock(void);
boolean U_IsOnlyInstance(const char *title);
boolean U_InstanceFileUnlock(void);
boolean U_CheckStorage(const char *path, const unsigned long long needed);
boolean U_CheckMemory(void);
unsigned long U_GetCPUSpeed(void);

#endif
