/* =============================================================================
** SimmeredEggsEngine, file: u_utility.h Created 12/6/2021
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
#ifndef __U_UTILITY_H__
#define __U_UTILITY_H__

#include "u_deftypes.h"

#include <cstdlib>
#include <string>

#define INSTANCE_FILE "/tmp/see_instance"

namespace SEE
{

void *Malloc(size_t size);
void Free(void *ptr);
int RandomInt(int minval, int maxval);
float RandomFloat(float minval, float maxval);
double RandomDouble(double minval, double maxval);
int RandomColorUnsignedChar(void);
float RandomColorNormalizedFloat(void);
boolean InstanceFileLock(void);
boolean IsOnlyInstance(void);
boolean InstanceFileUnlock(void);
boolean CheckStorage(const std::string &path, const unsigned long long needed);
boolean CheckMemory(void);
unsigned long GetCPUSpeed(void);

}

void *U_Malloc(size_t size);
void U_Free(void *ptr);
int U_RandomInt(int minval, int maxval);
float U_RandomFloat(float minval, float maxval);
double U_RandomDouble(double minval, double maxval);
int U_RandomColorUnsignedChar(void);
float U_RandomColorNormalizedFloat(void);
boolean U_InstanceFileLock(void);
boolean U_IsOnlyInstance(void);
boolean U_InstanceFileUnlock(void);
boolean U_CheckStorage(const char *path, const unsigned long long needed);
boolean U_CheckMemory(void);
unsigned long U_GetCPUSpeed(void);

#endif
