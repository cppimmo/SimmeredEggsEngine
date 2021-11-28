#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "scene.h"

struct scene_game_t {

};
typedef struct scene_game_t SceneGame;

bool game_start();
bool game_update(GLfloat delta_time);
bool game_render(GLfloat delta_time);
bool game_destroy();

#endif // SCENE_GAME_H
