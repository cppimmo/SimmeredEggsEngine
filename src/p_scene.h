/* =============================================================================
** SimmeredEggsEngine, file: p_scene.h Created 12/6/2021
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
#ifndef __P_SCENE_H__
#define __P_SCENE_H__

#include "GL/glew.h"
#include "u_utility.h"
#include "u_log.h"
#include "i_input.h"
#include "r_render.h"
#include "r_shader.h"

#include <stdlib.h>

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
boolean P_SceneUpdate(enum sceneavail_t scene, GLfloat deltatime);
boolean P_SceneRender(enum sceneavail_t scene, GLfloat deltatime);
boolean P_SceneDestroy(enum sceneavail_t scene);
enum sceneavail_t P_GetActiveScene(void);
struct scene_t *P_GetActiveScenePtr(void);
boolean P_ChangeScene(enum sceneavail_t scene);

#endif
