#ifndef __U_UTILITY_H__
#define __U_UTILITY_H__

// phooey on you GCC!
#undef bool
#undef true
#undef false
#undef TRUE
#undef FALSE

enum boolean_t {
	false,
	true,
};
typedef enum boolean_t boolean;

#endif
