#ifndef __P_SCENEMENU_H__
#define __P_SCENEMENU_H__

#include "p_scene.h"

struct scenemenu_t {

};

boolean P_MenuStart(void);
boolean P_MenuUpdate(GLfloat deltatime);
boolean P_MenuRender(GLfloat deltatime);
boolean P_MenuDestroy(void);

#endif
