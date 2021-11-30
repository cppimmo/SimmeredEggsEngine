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
