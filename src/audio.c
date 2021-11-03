#include "audio.h"
#include "log.h"
#include <string.h>
// #include "audio/wave.h" // libaudio

bool al_init()
{

	return true;
}

bool al_destroy()
{
	
	return true;
}

bool al_create_device(ALCdevice *pDevice)
{
	al_list_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	pDevice = alcOpenDevice(NULL);
	if (pDevice == NULL) {
		log_write(LOG_ERR, "");
		return false;
	}
	return true;
}

bool al_device_enum_check()
{ // check if the impl support enumerating devices
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	return (enumeration == AL_FALSE) ? false : true;
}

void al_list_devices(const ALCchar *devices)
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

bool al_create_context(ALCcontext *pContext)
{
	if (pDevice == NULL) {
		log_write(LOG_ERR, "Can't create ALCcontext, ALCdevice is null pointer!\n");
		return false;
	}
	pContext = alcCreateContext(pDevice, NULL);
	if (pContext == NULL) {
		log_write(LOG_ERR, "alcCreateContext() failed!\n");
		return false;
	}
	return true;
}

bool al_set_context(ALCcontext *pContext)
{
	if (!alcMakeContextCurrent(pContext)) {
		log_write(LOG_ERR, "alcMakeContextCurrent() failed!\n");
		return false;
	}
	return true;
}

bool al_gen_sources(ALuint *sources)
{

	return true;
}

bool al_gen_buffers(ALuint *buffers)
{

	return true;
}

inline bool al_error(const char *str)
{
	ALCenum error = alGetError();
	if (error != AL_NO_ERROR) {
		log_write(LOG_ERR, str);
		return false;
	}
	return true;
}

