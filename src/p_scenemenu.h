#ifndef __P_SCENEMENU_H__
#define __P_SCENEMENU_H__

#include "p_scene.h"

struct scenemenu_t {

};
typedef struct scenemenu_t SceneMenu;

boolean P_MenuStart(void);
boolean P_MenuUpdate(GLfloat delta_time);
boolean P_MenuRender(GLfloat delta_time);
boolean P_MenuDestroy(void);

#endif
