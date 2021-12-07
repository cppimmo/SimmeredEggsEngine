/* =============================================================================
** SimmeredEggsEngine, file: r_camera.h Created 12/6/2021
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
#ifndef __R_CAMERA_H__
#define __R_CAMERA_H__

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "cglm/cglm.h"
#include "u_utility.h"

/* default structure values to be used if no configuration is given */
#define CAMERA_YAW_DEFAULT -90.0f
#define CAMERA_PITCH_DEFAULT 0.0f
#define CAMERA_SPEED_FORWARD_DEFAULT 2.5f
#define CAMERA_SPEED_STRAFE_DEFAULT 2.5f
#define CAMERA_FOV_DEFAULT 45.0f
#define CAMERA_SENSIVITY_DEFAULT 0.1f

enum cameradirection_t {
	CAMERA_FORWARD,
	CAMERA_BACKWARD,
	CAMERA_LEFT,
	CAMERA_RIGHT,
};

enum cameratype_t {
	CAMERA_TYPE_FIRST_PERSON,
	CAMERA_TYPE_ORBIT,
};

struct camera_t {
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldup;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat speedforward; // movement speed
	GLfloat speedstrafe;
	GLfloat fov; // zoom level
	GLfloat sensitivity;
	boolean locked; // is camera the priority of the mouse?
	enum cameratype_t type;
};

void R_CameraInit(struct camera_t *camera);
void R_CameraViewMatrix(struct camera_t *camera, mat4 *view);
void R_CameraFreeMouse(void);
void R_CameraLockMouse(void);
void R_CameraSetPos(vec3 position);
void R_CameraSetSensitity(GLfloat sensitivity);
void R_CameraSetSpeed(GLfloat forward, GLfloat strafe);
void R_CameraSetFOV(GLfloat fov);
void R_CameraMove(void);
void R_CameraUpdate(GLfloat deltatime);

#endif
