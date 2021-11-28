#ifndef SCENE_H
#define SCENE_H

#include "GL/glew.h"
#include <stdlib.h>
#include "u_utility.h"

#define SCENE_MAX_THREADS 12
#define SCENE_NAME_MAX_LENGTH 75

typedef boolean (*SceneStartPtr)(void);
typedef boolean (*SceneStartSubRountinePtr)(void);
typedef boolean (*SceneUpdatePtr)(GLfloat);
typedef boolean (*SceneRenderPtr)(GLfloat);
typedef boolean (*SceneDestroyPtr)(void);

struct scene_state_t {
	boolean initialized;
	boolean destroyed;
	boolean active;
};
typedef struct scene_state_t SceneState;

enum scene_avail_t {
	SCENE_MENU = 0,
	SCENE_GAME = 1,
	SCENE_MAX_COUNT = 2, // number of scenes available; constant expression
};
typedef enum scene_avail_t SceneSelection;

struct scene_t {
	char name[SCENE_NAME_MAX_LENGTH];
	SceneState state;
	SceneStartPtr p_start;
	SceneStartSubRountinePtr p_start_sub[SCENE_MAX_THREADS]; // array of funtion pointers
	SceneUpdatePtr p_update;
	SceneRenderPtr p_render;
	SceneDestroyPtr p_destroy;
};
typedef struct scene_t Scene;
typedef Scene *ScenePtr; 

// configure the scenes recognized by scene_avail_t
void scene_setup();
boolean scene_init(const enum scene_avail_t scene);
boolean scene_update(const enum scene_avail_t scene, GLfloat delta_time);
boolean scene_render(const enum scene_avail_t scene, GLfloat delta_time);
boolean scene_destroy(const enum scene_avail_t scene);
enum scene_avail_t scene_active();
ScenePtr scene_active_ptr();
boolean scene_change(const enum scene_avail_t scene);

#endif // SCENE_H
