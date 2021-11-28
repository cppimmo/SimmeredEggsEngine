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

enum camera_direction_t {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
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
};

void R_CameraInit(struct camera_t *p_camera);
void R_CameraViewMatrix(struct camera_t *p_camera, mat4 *p_view);
void R_CameraFreeMouse();
void R_CameraLockMouse();
void R_CameraMove();
void R_CameraUpdate(GLfloat delta_time);

#endif
