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
#include "u_log.h"

#include <math.h>

static void UpdateCameraVectors(Camera *camera);

static Camera *activecamera;
#define NULL_CAMERA(X) \
	if (activecamera == NULL) \
		return X \

boolean R_CameraInit(Camera *camera,
					 CameraProjection projection,
					 CameraType type) {
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
	camera->contrainpitch = true;
	camera->lastx = 0.0f;
	camera->lasty = 0.0f;
	return true;
}

inline void R_SetActiveCamera(Camera *camera) {
	activecamera = camera;
}

void R_CameraViewMatrix(Camera *camera, mat4 view) {
	vec3 dest;
	glm_vec3_add(camera->position, camera->front, dest);
	glm_lookat(camera->position, dest, camera->up, view);
}

static void UpdateCameraVectors(Camera *camera) {
	vec3 front; // calculate new front vector
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	front[1] = sin(glm_rad(camera->pitch));
	front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize(front);
	// calculate the right and up vector
	glm_vec3_cross(camera->front, camera->worldup, camera->right);
	glm_normalize(camera->right); // normalize vectors to increase movement speed
	glm_vec3_cross(camera->right, camera->front, camera->up);
	glm_normalize(camera->up);
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

void R_CameraProcessMovement(GLfloat deltatime) {
	GLfloat forwardspeed = activecamera->speedforward * deltatime;
	GLfloat strafespeed = activecamera->speedstrafe * deltatime;

	vec3 vecforward; glm_vec3_broadcast(forwardspeed, vecforward);
	vec3 vecstrafe; glm_vec3_broadcast(strafespeed, vecstrafe);
	if (I_IsKeyDown(SDL_SCANCODE_W)) {
		vec3 result;
		printf("Vecforward %.2f %.2f %.2f\n", vecforward[0], vecforward[1], vecforward[2]);
		glm_vec3_mul(activecamera->front, vecforward, result);
		printf("result %.2f %.2f %.2f\n", result[0], result[1], result[2]);
		glm_vec3_add(activecamera->position, result, activecamera->position);
	}
	if (I_IsKeyDown(SDL_SCANCODE_A)) {
		vec3 result;
		glm_vec3_mul(activecamera->right, vecstrafe, result);
		glm_vec3_sub(activecamera->position, result, activecamera->position);
	}
	if (I_IsKeyDown(SDL_SCANCODE_S)) {
		vec3 result;
		glm_vec3_mul(activecamera->front, vecforward, result);
		glm_vec3_sub(activecamera->position, result, activecamera->position);
	}
	if (I_IsKeyDown(SDL_SCANCODE_D)) {
		vec3 result;
		glm_vec3_mul(activecamera->right, vecstrafe, result);
		glm_vec3_add(activecamera->position, result, activecamera->position);
	}
}

void R_CameraProcessMouse(void) {
	IMousePos *pos = I_GetMousePos();

	activecamera->lastx *= activecamera->sensitivity;
	activecamera->lasty *= activecamera->sensitivity;

	activecamera->yaw += activecamera->lastx;
	activecamera->pitch += activecamera->lasty;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (activecamera->contrainpitch) {
		if (activecamera->pitch > 89.0f)
			activecamera->pitch = 89.0f;
		if (activecamera->pitch < -89.0f)
			activecamera->pitch = -89.0f;
	}

	activecamera->lastx = (GLfloat)pos->x;
	activecamera->lasty = (GLfloat)pos->y;
}

void R_CameraProcessScroll(GLfloat deltatime) {
	IMouseWheel *wheel = I_GetMouseWheelState();
    // last value, you should really make this non-static lol
	static GLfloat yoffset = 0.0f;
	activecamera->fov -= yoffset;

	if (activecamera->fov < 1.0f)
		activecamera->fov = 1.0f;
	if (activecamera->fov > 45.0f)
		activecamera->fov = 45.0f;

	yoffset = (GLfloat)wheel->y;
}

void R_CameraUpdate(GLfloat deltatime) {
	NULL_CAMERA();
	/* struct mousepos_t *mousepos = I_GetMousePos();
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
	// process mouse movement (xoffset, yoffset) */
	R_CameraProcessMovement(deltatime);
	U_LogWrite(LOG_MSG, "%.2f,%.2f,%.2f\n", activecamera->position[0],
			   activecamera->position[1], activecamera->position[2]);
	R_CameraProcessMouse();
	R_CameraProcessScroll(deltatime);
	UpdateCameraVectors(activecamera);
}

