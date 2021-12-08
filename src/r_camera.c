/* =============================================================================
** SimmeredEggsEngine, file: r_camera.c Created 12/6/2021
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
#include "r_camera.h"
#include "i_input.h"

struct camera_t *activecamera;
#define NULL_CAMERA(X) \
	if (activecamera == NULL) \
		return X \

boolean R_CameraInit(struct camera_t *camera,
					 enum cameraprojection_t projection,
					 enum cameratype_t type) {
	if (camera == NULL)
		return false;
	glm_vec3_zero(camera->position);
	glm_vec3_zero(camera->front);
	glm_vec3_zero(camera->up);
	glm_vec3_zero(camera->right);
	glm_vec3_zero(camera->worldup);
	camera->yaw = CAMERA_YAW_DEFAULT;
	camera->pitch = CAMERA_PITCH_DEFAULT;
	camera->speedforward = CAMERA_SPEED_FORWARD_DEFAULT;
	camera->speedstrafe = CAMERA_SPEED_STRAFE_DEFAULT;
	camera->fov = CAMERA_FOV_DEFAULT;
	camera->sensitivity = CAMERA_SENSIVITY_DEFAULT;
	camera->locked = false;
    camera->type = type;
    // other stuff
	camera->firstmouse = true;
	camera->lastx = 0.0f;
	camera->lasty = 0.0f;
	return true;
}

inline void R_SetActiveCamera(struct camera_t *camera) {
	activecamera = camera;
}

void R_CameraViewMatrix(struct camera_t *camera, mat4 *view) {

}

inline void R_CameraFreeMouse(void) {
	NULL_CAMERA();
	activecamera->locked = false;
}

inline void R_CameraLockMouse(void) {
	NULL_CAMERA();
	activecamera->locked = true;
}

inline void R_CameraSetPos(vec3 position) {
	NULL_CAMERA();
	glm_vec3_copy(position, activecamera->position);
}

void R_CameraSetSensitity(GLfloat sensitivity) {
	NULL_CAMERA();
	activecamera->sensitivity = sensitivity;
}

void R_CameraSetSpeed(GLfloat forward, GLfloat strafe) {
	NULL_CAMERA();
	activecamera->speedforward = forward;
	activecamera->speedstrafe = strafe;
}

inline void R_CameraSetFieldOfView(GLfloat fov) {
	NULL_CAMERA();
	activecamera->fov = fov;
}

void R_CameraMove(void) {
	if (I_IsKeyDown(SDL_SCANCODE_W)) {

	}
	if (I_IsKeyDown(SDL_SCANCODE_A)) {

	}
	if (I_IsKeyDown(SDL_SCANCODE_S)) {

	}
	if (I_IsKeyDown(SDL_SCANCODE_D)) {

	}
}

void R_CameraUpdate(GLfloat deltatime) {
	NULL_CAMERA();
	struct mousepos_t *mousepos = I_GetMousePos();
	if (activecamera->firstmouse) {
		activecamera->lastx = (GLfloat)mousepos->x;
		activecamera->lasty = (GLfloat)mousepos->y;
		activecamera->firstmouse = false;
	}

	const float xoffset = mousepos->x - activecamera->lastx;
	// reversed since y-coords go from bottom to top
	const float yoffset = activecamera->lasty - mousepos->y;

	activecamera->lastx = (GLfloat)mousepos->x;
	activecamera->lasty = (GLfloat)mousepos->y;

	// process mouse movement (xoffset, yoffset)
}

