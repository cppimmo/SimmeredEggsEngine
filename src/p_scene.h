#ifndef __P_SCENE_H__
#define __P_SCENE_H__

#include "GL/glew.h"
#include <stdlib.h>
#include "u_utility.h"

#define SCENE_MAX_THREADS 12
#define SCENE_NAME_MAX_LENGTH 75

typedef boolean (*P_SceneStartPtr)(void);
typedef boolean (*P_SceneStartSubRountinePtr)(void);
typedef boolean (*P_SceneUpdatePtr)(GLfloat);
typedef boolean (*P_SceneRenderPtr)(GLfloat);
typedef boolean (*P_SceneDestroyPtr)(void);

struct scenestate_t {
	boolean initialized;
	boolean destroyed;
	boolean active;
};
typedef struct scenestate_t SceneState;

enum sceneavail_t {
	SCENE_MENU = 0,
	SCENE_GAME = 1,
	SCENE_MAX_COUNT = 2, // number of scenes available; constant expression
};

struct scene_t {
	char name[SCENE_NAME_MAX_LENGTH];
	SceneState state;
	P_SceneStartPtr start;
	P_SceneStartSubRountinePtr startsub[SCENE_MAX_THREADS]; // array of funtion pointers
	P_SceneUpdatePtr update;
	P_SceneRenderPtr render;
	P_SceneDestroyPtr destroy;
};
typedef struct scene_t* ScenePtr;

// configure the scenes recognized by scene_avail_t
void P_SceneSetup(void);
boolean P_SceneInit(enum sceneavail_t scene);
boolean P_SceneUpdate(enum sceneavail_t scene, GLfloat delta_time);
boolean P_SceneRender(enum sceneavail_t scene, GLfloat delta_time);
boolean P_SceneDestroy(enum sceneavail_t scene);
enum sceneavail_t P_GetActiveScene(void);
struct scene_t *P_GetActiveScenePtr(void);
boolean P_ChangeScene(enum sceneavail_t scene);

#endif
