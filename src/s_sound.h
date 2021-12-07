/* =============================================================================
** SimmeredEggsEngine, file: s_sound.h Created 12/6/2021
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
#ifndef __S_SOUND_H__
#define __S_SOUND_H__

#include "AL/al.h"
#include "AL/alc.h"
#include "u_utility.h"

#include <stdlib.h>

// implement dynamic context, source, & buffer interface
boolean S_SoundInit(void);
boolean S_SoundDestroy(void);
boolean S_CreateContext(ALCdevice *device, ALCcontext *context);
boolean S_SetContext(ALCcontext *context);
ALCcontext *S_GetContextCurrent(void);
// boolean S_CreateListener(ALClistener *pListener);
boolean S_GenSources(ALuint *sources);
boolean S_GenBuffers(ALuint *buffers);
void S_DeleteSources(ALuint *sources, ALuint count);
void S_DeleteBuffers(ALuint *buffers, ALuint count);

#endif
