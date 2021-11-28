#include "audio.h"
#include "log.h"
#include <string.h>
// #include "audio/wave.h" // libaudio

static boolean al_create_device(ALCdevice *p_device, const ALchar *name);
static boolean al_device_enum_check();
static void al_list_devices(const ALCchar *devices);
static boolean al_error(const ALchar *str);

static ALCdevice *g_device = NULL;
static ALCcontext *g_context = NULL;

boolean al_init()
{
	if (!al_device_enum_check())
		log_write(LOG_ERR, "AL Enumeration extension not available\n");
	al_list_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    const ALchar *def_device = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	if (!al_create_device(&g_device, def_device)) {
		log_write(LOG_ERR, "Failed to create ALCdevice!\n");
		return false;
	} else
		log_write(LOG_LOG, "Audio Device %s\n", alcGetString(g_device, ALC_DEVICE_SPECIFIER));

	if (!al_create_context(&g_device, &g_context)) {
		log_write(LOG_ERR, "Failed to create ALCcontext!\n");
		return false;
	}

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	return true;
}

boolean al_destroy()
{

	return true;
}

static boolean al_create_device(ALCdevice *p_device, const ALchar *name)
{
	al_list_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	p_device = alcOpenDevice(name);
	if (p_device == NULL) {
		log_write(LOG_ERR, "");
		return false;
	}
	return true;
}

static boolean al_device_enum_check()
{ // check if the impl support enumerating devices
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	return (enumeration == AL_FALSE) ? false : true;
}

static void al_list_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	log_write(LOG_LOG, "Audio Device List:\n");
	log_write(LOG_LOG, "------------------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		log_write(LOG_LOG, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	log_write(LOG_LOG, "------------------\n");
}

boolean al_create_context(ALCdevice *p_device, ALCcontext *p_context)
{
	if (p_device == NULL) {
		log_write(LOG_ERR, "Can't create ALCcontext, ALCdevice is null pointer!\n");
		return false;
	}
	p_context = alcCreateContext(p_device, NULL);
	if (p_context == NULL) {
		log_write(LOG_ERR, "alcCreateContext() failed!\n");
		return false;
	}
	return true;
}

boolean al_set_context(ALCcontext *p_context)
{
	if (!alcMakeContextCurrent(p_context)) {
		log_write(LOG_ERR, "alcMakeContextCurrent() failed!\n");
		return false;
	}
	return true;
}

boolean al_gen_sources(ALuint *sources)
{

	return true;
}

boolean al_gen_buffers(ALuint *buffers)
{

	return true;
}

inline boolean al_error(const ALchar *str)
{
	ALCenum error = alGetError();
	if (error != AL_NO_ERROR) {
		log_write(LOG_ERR, str);
		return false;
	}
	return true;
}

