#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "scene.h"

struct scene_menu_t {

};
typedef struct scene_menu_t SceneMenu;

bool menu_start();
bool menu_update(GLfloat delta_time);
bool menu_render(GLfloat delta_time);
bool menu_destroy();

#endif // MENU_H
