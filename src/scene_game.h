#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "scene.h"

struct scene_game_t {

};
typedef struct scene_game_t SceneGame;

boolean game_start();
boolean game_update(GLfloat delta_time);
boolean game_render(GLfloat delta_time);
boolean game_destroy();

#endif // SCENE_GAME_H
