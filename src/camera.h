#ifndef CAMERA_H
#define CAMERA_H

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
typedef enum camera_direction_t CameraDirection;

struct camera_t {
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 world_up;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat speed_forward; // movement speed
	GLfloat speed_strafe;
	GLfloat field_of_view; // zoom level
	GLfloat sensitivity;
	boolean is_locked; // is camera the priority of the mouse?
};
typedef struct camera_t Camera;

void camera_init(struct camera_t *p_camera);
void camera_view_matrix(struct camera_t *p_camera, mat4 *p_view);
void camera_freemouse();
void camera_lockmouse();
void camera_move();
void camera_update(GLfloat delta_time);

#endif // CAMERA_H
