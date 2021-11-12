#ifndef AUDIO_H
#define AUDIO_H

#include "AL/al.h"
#include "AL/alc.h"
#include <stdlib.h>
#include <stdbool.h>

// implement dynamic context, source, & buffer interface

bool al_init();
bool al_destroy();
static bool al_create_device(ALCdevice *p_device, const ALchar *name);
static bool al_device_enum_check();
static void al_list_devices(const ALCchar *devices);
bool al_create_context(ALCdevice *p_device, ALCcontext *p_context);
bool al_set_context(ALCcontext *p_context);
// bool al_create_listener(ALClistener *pListener);
bool al_gen_sources(ALuint *sources);
bool al_gen_buffers(ALuint *buffers);
void al_delete_sources(ALuint *sources, ALuint count);
void al_delete_buffers(ALuint *buffers, ALuint count);

static bool al_error(const ALchar *str);

#endif // AUDIO_H
