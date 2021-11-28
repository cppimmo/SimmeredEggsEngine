#include "scene.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "log.h"

#include "scene_menu.h"
#include "scene_game.h"

static void scene_setter(ScenePtr p_scene, const char *name,
						 SceneState *const p_state, SceneStartPtr p_start,
						 SceneStartSubRountinePtr *p_start_sub,
						 SceneUpdatePtr p_update, SceneRenderPtr p_render,
						 SceneDestroyPtr p_destroy);

static enum scene_avail_t active_scene;
// pointers to the available scenes
static struct scene_t g_scenes[SCENE_MAX_COUNT];

inline void scene_setter(ScenePtr p_scene, const char *name,
						 SceneState *const p_state, SceneStartPtr p_start,
						 SceneStartSubRountinePtr *p_start_sub,
						 SceneUpdatePtr p_update, SceneRenderPtr p_render,
						 SceneDestroyPtr p_destroy)
{
	// p_scene->name = name;
	p_scene->state.initialized = p_state->initialized;
	p_scene->state.destroyed = p_state->destroyed;
	p_scene->state.active = p_state->active;

}

void scene_setup()
{
	// this work could be put into a static inline function
	strcpy(g_scenes[SCENE_MENU].name, "Menu");
	g_scenes[SCENE_MENU].state.initialized = false;
	g_scenes[SCENE_MENU].state.destroyed = false;
	g_scenes[SCENE_MENU].state.active = false;
	g_scenes[SCENE_MENU].p_start = menu_start;
	// g_scenes[SCENE_MENU].p_start_sub[0] = ;
	g_scenes[SCENE_MENU].p_update = menu_update;
	g_scenes[SCENE_MENU].p_render = menu_render;
	g_scenes[SCENE_MENU].p_destroy = menu_destroy;

    strcpy(g_scenes[SCENE_GAME].name, "Game");
	g_scenes[SCENE_GAME].state.initialized = false;
	g_scenes[SCENE_GAME].state.destroyed = false;
	g_scenes[SCENE_GAME].state.active = false;
	g_scenes[SCENE_GAME].p_start = game_start;
	// g_scenes[SCENE_GAME].p_start_sub[0] = ;
	g_scenes[SCENE_GAME].p_update = game_update;
	g_scenes[SCENE_GAME].p_render = game_render;
	g_scenes[SCENE_GAME].p_destroy = game_destroy;

	active_scene = SCENE_GAME;
}

boolean scene_init(const enum scene_avail_t scene)
{
	boolean result;
	result = g_scenes[scene].p_start();
	if (!result)
		return result;
	if (g_scenes[scene].p_start_sub != NULL) {
		// size_t length = sizeof(p_scene->p_start_sub) / sizeof(p_scene->p_start_sub[0]);
		// pthread_t *threads = (pthread_t*)malloc(length * sizeof(pthread_t));
		pthread_t *threads[SCENE_MAX_THREADS];
		// loop through each scene start subroutine and run on a seperate thread
		for (size_t i = 0; i < SCENE_MAX_THREADS; ++i) {
			if (g_scenes[scene].p_start_sub[i] == NULL)
				continue;
			if (pthread_create(&threads[i], NULL,
							   g_scenes[scene].p_start_sub[i], NULL) != 0) {
				log_write(LOG_ERR, "Failed to create SceneStartSubRoutine"
						  "thread! index[%d]", i);
			}
		}
		for (size_t i = 0; i < SCENE_MAX_THREADS; ++i) {
			if (g_scenes[scene].p_start_sub[i] == NULL)
				continue;
			boolean join_result;
			if (pthread_join(threads[i], (void**)&join_result) != 0) {
				log_write(LOG_ERR, "Failed to join SceneStartsubroutine thread!"
						  "index[%d]", i);
			}
			if (join_result == false) {
				log_write(LOG_ERR, "SceneStartSubrountine failed! index[%d]", i);
				result = join_result;
				break;
			}
		}
		// free(threads); // don't skip this guy! haha
	}
	g_scenes[scene].state.initialized = true;
	return result;
}

boolean scene_update(const enum scene_avail_t scene, GLfloat delta_time)
{
	boolean result;
	result = g_scenes[scene].p_update(delta_time);
	return result;
}

boolean scene_render(const enum scene_avail_t scene, GLfloat delta_time)
{
	boolean result;
	result = g_scenes[scene].p_render(delta_time);
	return result;
}

boolean scene_destroy(const enum scene_avail_t scene)
{
	boolean result;
	result = g_scenes[scene].p_destroy();
	g_scenes[scene].state.destroyed = true;
	return result;
}

inline enum scene_avail_t scene_active()
{
	return active_scene;
}

inline ScenePtr scene_active_ptr()
{
	return &g_scenes[active_scene];
}

boolean scene_change(const enum scene_avail_t scene)
{
	boolean result;
	if (g_scenes[active_scene].state.initialized)
		scene_destroy(active_scene);
	active_scene = scene;
	// operate on new active scene
	g_scenes[active_scene].state.active = true;
    if (!g_scenes[active_scene].state.initialized)
		result = scene_init(active_scene);
	else
		result = true;
	return result;
}

