#ifndef __P_SCENEGAME_H__
#define __P_SCENEGAME_H__

#include "p_scene.h"

struct scenegame_t {

};

boolean P_GameStart(void);
boolean P_GameUpdate(GLfloat deltatime);
boolean P_GameRender(GLfloat deltatime);
boolean P_GameDestroy(void);

#endif
