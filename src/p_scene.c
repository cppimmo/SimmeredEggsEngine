/* =============================================================================
** SimmeredEggsEngine, file: p_scene.c Created 12/6/2021
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
#include "p_scene.h"
#include "u_log.h"
#include "p_scenemenu.h"
#include "p_scenegame.h"

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

static void SceneSetter(ScenePtr scene, const char *name,
						SceneState *const state, P_SceneStartPtr start,
						P_SceneStartSubRountinePtr *startsub,
						P_SceneUpdatePtr update, P_SceneRenderPtr render,
						P_SceneDestroyPtr destroy);

static enum sceneavail_t activescene;
// pointers to the available scenes
static struct scene_t scenes[SCENE_MAX_COUNT];

inline void SceneSetter(ScenePtr scene, const char *name,
						SceneState *const state, P_SceneStartPtr start,
						P_SceneStartSubRountinePtr *startsub,
						P_SceneUpdatePtr update, P_SceneRenderPtr render,
						P_SceneDestroyPtr destroy) {
	strcpy(scene->name, name);
	scene->state.initialized = state->initialized;
	scene->state.destroyed = state->destroyed;
	scene->state.active = state->active;
	scene->start = start;
    // scene->startsub[0] = ;
	scene->update = update;
	scene->render = render;
	scene->destroy = destroy;
}

void P_SceneSetup(void) {
	// this work could be put into a static inline function
	strcpy(scenes[SCENE_MENU].name, "Menu");
	scenes[SCENE_MENU].state.initialized = false;
	scenes[SCENE_MENU].state.destroyed = false;
	scenes[SCENE_MENU].state.active = false;
	scenes[SCENE_MENU].start = P_MenuStart;
	// scenes[SCENE_MENU].startsub[0] = ;
	scenes[SCENE_MENU].update = P_MenuUpdate;
	scenes[SCENE_MENU].render = P_MenuRender;
	scenes[SCENE_MENU].destroy = P_MenuDestroy;

    strcpy(scenes[SCENE_GAME].name, "Game");
	scenes[SCENE_GAME].state.initialized = false;
	scenes[SCENE_GAME].state.destroyed = false;
	scenes[SCENE_GAME].state.active = false;
	scenes[SCENE_GAME].start = P_GameStart;
	// scenes[SCENE_GAME].startsub[0] = ;
	scenes[SCENE_GAME].update = P_GameUpdate;
	scenes[SCENE_GAME].render = P_GameRender;
	scenes[SCENE_GAME].destroy = P_GameDestroy;

	activescene = SCENE_GAME;
}

boolean P_SceneInit(enum sceneavail_t scene) {
	boolean result;
	result = scenes[scene].start();
	if (!result)
		return result;
	if (scenes[scene].startsub != NULL) {
		// size_t length = sizeof(p_scene->p_start_sub) / sizeof(p_scene->p_start_sub[0]);
		// pthread_t *threads = (pthread_t*)malloc(length * sizeof(pthread_t));
		pthread_t *threads[SCENE_MAX_THREADS];
		// loop through each scene start subroutine and run on a seperate thread
		for (size_t i = 0; i < SCENE_MAX_THREADS; ++i) {
			if (scenes[scene].startsub[i] == NULL)
				continue;
			if (pthread_create(&threads[i], NULL,
							   scenes[scene].startsub[i], NULL) != 0) {
				U_LogWrite(LOG_ERR, "Failed to create SceneStartSubRoutine"
						  "thread! index[%d]", i);
			}
		}
		for (size_t i = 0; i < SCENE_MAX_THREADS; ++i) {
			if (scenes[scene].startsub[i] == NULL)
				continue;
			boolean join_result;
			if (pthread_join(threads[i], (void**)&join_result) != 0) {
				U_LogWrite(LOG_ERR, "Failed to join SceneStartsubroutine thread!"
						  "index[%d]", i);
			}
			if (join_result == false) {
				U_LogWrite(LOG_ERR, "SceneStartSubrountine failed! index[%d]", i);
				result = join_result;
				break;
			}
		}
		// free(threads); // don't skip this guy! haha
	}
	scenes[scene].state.initialized = true;
	return result;
}

boolean P_SceneUpdate(enum sceneavail_t scene, GLfloat deltatime) {
	boolean result;
	result = scenes[scene].update(deltatime);
	return result;
}

boolean P_SceneRender(enum sceneavail_t scene, GLfloat deltatime) {
	boolean result;
	result = scenes[scene].render(deltatime);
	return result;
}

boolean P_SceneDestroy(enum sceneavail_t scene) {
	boolean result;
	result = scenes[scene].destroy();
	scenes[scene].state.destroyed = true;
	return result;
}

inline enum sceneavail_t P_GetActiveScene(void) {
	return activescene;
}

inline struct scene_t *P_GetActiveScenePtr(void) {
	return &scenes[activescene];
}

boolean P_ChangeScene(enum sceneavail_t scene) {
	boolean result;
	if (scenes[activescene].state.initialized)
		P_SceneDestroy(activescene);
	activescene = scene;
	// operate on new active scene
	scenes[activescene].state.active = true;
    if (!scenes[activescene].state.initialized)
		result = P_SceneInit(activescene);
	else
		result = true;
	return result;
}

