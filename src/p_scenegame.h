#ifndef __P_SCENEGAME_H__
#define __P_SCENEGAME_H__

#include "p_scene.h"

struct scenegame_t {

};

boolean P_GameStart(void);
boolean P_GameUpdate(GLfloat delta_time);
boolean P_GameRender(GLfloat delta_time);
boolean P_GameDestroy(void);

#endif
