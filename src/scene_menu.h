#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "scene.h"

struct scene_menu_t {

};
typedef struct scene_menu_t SceneMenu;

boolean menu_start();
boolean menu_update(GLfloat delta_time);
boolean menu_render(GLfloat delta_time);
boolean menu_destroy();

#endif // MENU_H
