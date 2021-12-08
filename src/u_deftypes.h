/* =============================================================================
** SimmeredEggsEngine, file: u_types.h Created 12/7/2021
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
#ifndef __U_DEFTYPES_H__
#define __U_DEFTYPES_H__

/* this file stores type definitions and other constants */

/*
 * CONSTANTS
 */
#define ENGINE_NAME "SimmeredEggsEngine"
enum {
	ENGINE_VERSION_MAJOR = 1,
	ENGINE_VERSION_MINOR = 0,
	ENGINE_VERSION_PATCH = 0,
};
#define EMPTY_STRING ""

/*
 * TYPES
 */
#ifdef __cplusplus
// use builtin bool type with C++
typedef bool boolean;
#else
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

#endif
