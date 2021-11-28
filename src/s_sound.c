#include "s_sound.h"
#include "log.h"
#include <string.h>
// #include "audio/wave.h" // libaudio

static boolean AL_CreateDevice(ALCdevice *p_device, const ALchar *name);
static boolean AL_DeviceEnumCheck(void);
static void AL_ListDevices(const ALCchar *devices);
static boolean AL_Error(const ALchar *str);

static ALCdevice *aldevice = NULL;
static ALCcontext *alcontext = NULL;

boolean S_SoundInit(void) {
	if (!AL_DeviceEnumCheck())
		log_write(LOG_ERR, "AL Enumeration extension not available\n");
	AL_ListDevices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    const ALchar *defdevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	if (!AL_CreateDevice(&aldevice, defdevice)) {
		log_write(LOG_ERR, "Failed to create ALCdevice!\n");
		return false;
	} else
		log_write(LOG_LOG, "Audio Device %s\n", alcGetString(aldevice, ALC_DEVICE_SPECIFIER));

	if (!S_CreateContext(&aldevice, &alcontext)) {
		log_write(LOG_ERR, "Failed to create ALCcontext!\n");
		return false;
	}

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	return true;
}

boolean S_SoundDestroy(void) {

	return true;
}

static boolean AL_CreateDevice(ALCdevice *device, const ALchar *name) {
	AL_ListDevices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	device = alcOpenDevice(name);
	if (device == NULL) {
		log_write(LOG_ERR, "");
		return false;
	}
	return true;
}

static boolean AL_DeviceEnumCheck(void) { 
    // check if the impl support enumerating devices
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	return (enumeration == AL_FALSE) ? false : true;
}

static void AL_ListDevices(const ALCchar *devices) {
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

boolean S_CreateContext(ALCdevice *device, ALCcontext *context) {
	if (device == NULL) {
		log_write(LOG_ERR, "Can't create ALCcontext, ALCdevice is null pointer!\n");
		return false;
	}
    context = alcCreateContext(device, NULL);
	if (context == NULL) {
		log_write(LOG_ERR, "alcCreateContext() failed!\n");
		return false;
	}
	return true;
}

boolean S_SetContext(ALCcontext *context) {
	if (!alcMakeContextCurrent(context)) {
		log_write(LOG_ERR, "alcMakeContextCurrent() failed!\n");
		return false;
	}
	return true;
}

boolean S_GenSources(ALuint *sources) {

	return true;
}

boolean S_GenBuffers(ALuint *buffers) {

	return true;
}

inline boolean AL_Error(const ALchar *str) {
	ALCenum error = alGetError();
	if (error != AL_NO_ERROR) {
		log_write(LOG_ERR, str);
		return false;
	}
	return true;
}

