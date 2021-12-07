/* =============================================================================
** SimmeredEggsEngine, file: s_sound.c Created 12/6/2021
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
#include "s_sound.h"
#include "u_log.h"
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
		U_LogWrite(LOG_ERR, "AL Enumeration extension not available\n");
	AL_ListDevices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    const ALchar *defdevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	if (!AL_CreateDevice(aldevice, defdevice)) {
		U_LogWrite(LOG_ERR, "Failed to create ALCdevice!\n");
		return false;
	} else
		U_LogWrite(LOG_LOG, "Audio Device %s\n", alcGetString(aldevice, ALC_DEVICE_SPECIFIER));

	/* if (!S_CreateContext(aldevice, alcontext)) {
		U_LogWrite(LOG_ERR, "Failed to create ALCcontext!\n");
		return false;
	} */

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
		U_LogWrite(LOG_ERR, "alcOpenDevice() failed!\n");
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

	U_LogWrite(LOG_LOG, "Audio Device List:\n");
	U_LogWrite(LOG_LOG, "------------------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		U_LogWrite(LOG_LOG, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	U_LogWrite(LOG_LOG, "------------------\n");
}

boolean S_CreateContext(ALCdevice *device, ALCcontext *context) {
	if (device == NULL) {
		U_LogWrite(LOG_ERR, "Can't create ALCcontext, ALCdevice is null pointer!\n");
		return false;
	}
    context = alcCreateContext(device, NULL);
	if (context == NULL) {
		U_LogWrite(LOG_ERR, "alcCreateContext() failed!\n");
		return false;
	}
	return true;
}

boolean S_SetContext(ALCcontext *context) {
	if (!alcMakeContextCurrent(context)) {
		U_LogWrite(LOG_ERR, "alcMakeContextCurrent() failed!\n");
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
		U_LogWrite(LOG_ERR, str);
		return false;
	}
	return true;
}

