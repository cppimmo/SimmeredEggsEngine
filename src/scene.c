#include "scene.h"

static ScenePtr p_active_scene = NULL;

bool scene_init(ScenePtr p_scene)
{
	bool value;
	value = p_scene->p_start();
	p_scene->state.initialized = true;
	return value;
}

bool scene_update(ScenePtr p_scene)
{
	bool value;
	value = p_scene->p_update();
	return value;
}

bool scene_destroy(ScenePtr p_scene)
{
	bool value;
	value = p_scene->p_destroy();
	p_scene->state.destroyed = true;
	return value;
}

ScenePtr scene_active()
{
	return p_active_scene;
}

bool scene_change(ScenePtr p_scene)
{
	if (p_active_scene->state.initialized)
		scene_destroy(p_active_scene);
	p_active_scene = p_scene;
	// operate on new active scene
	p_active_scene->state.active = true;
    if (!p_active_scene->state.initialized)
		scene_init(p_active_scene);
}

