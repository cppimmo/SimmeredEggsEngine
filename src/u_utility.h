#ifndef UTILITY_H
#define UTILITY_H

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

#endif // UTILITY_H
