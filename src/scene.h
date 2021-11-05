#ifndef SCENE_H
#define SCENE_H

#include <stdlib.h>
#include <stdbool.h>

typedef bool (*SceneStartPtr)(void);
typedef bool (*SceneUpdatePtr)(void);
typedef bool (*SceneDestroyPtr)(void);

struct scene_state_t {
	bool initialized;
	bool destroyed;
	bool active;
};
typedef struct scene_state_t SceneState;

struct scene_t {
	const char *name;
	SceneState scene_state;
	SceneStartPtr p_scene_start;
	SceneUpdatePtr p_scene_update;
	SceneDestroyPtr p_scene_destroy;
};
typedef struct scene_t Scene;
typedef Scene *ScenePtr; 

static ScenePtr p_active_scene = NULL;

bool scene_init(SceneStartPtr p_scene_start);
bool scene_update(SceneUpdatePtr p_scene_update);
bool scene_destroy(SceneDestroyPtr p_scene_destroy);
ScenePtr scene_active();
bool scene_change(ScenePtr p_scene);

#endif // SCENE_H
