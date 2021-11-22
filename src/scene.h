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
	SceneState state;
	SceneStartPtr p_start;
	SceneUpdatePtr p_update;
	SceneDestroyPtr p_destroy;
};
typedef struct scene_t Scene;
typedef Scene *ScenePtr; 

bool scene_init(ScenePtr p_start);
bool scene_update(ScenePtr p_update);
bool scene_destroy(ScenePtr p_destroy);
ScenePtr scene_active();
bool scene_change(ScenePtr p_scene);

#endif // SCENE_H
