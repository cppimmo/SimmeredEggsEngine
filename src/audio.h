#ifndef AUDIO_H
#define AUDIO_H

#include "AL/al.h"
#include "AL/alc.h"
#include <stdlib.h>
#include "u_utility.h"

// implement dynamic context, source, & buffer interface

boolean al_init();
boolean al_destroy();
boolean al_create_context(ALCdevice *p_device, ALCcontext *p_context);
boolean al_set_context(ALCcontext *p_context);
// boolean al_create_listener(ALClistener *pListener);
boolean al_gen_sources(ALuint *sources);
boolean al_gen_buffers(ALuint *buffers);
void al_delete_sources(ALuint *sources, ALuint count);
void al_delete_buffers(ALuint *buffers, ALuint count);

#endif // AUDIO_H
