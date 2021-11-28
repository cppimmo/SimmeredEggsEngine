#ifndef __P_SCENEGAME_H__
#define __P_SCENEGAME_H__

#include "p_scene.h"

struct scenegame_t {

};
typedef struct scenegame_t SceneGame;

boolean P_GameStart(void);
boolean P_GameUpdate(GLfloat delta_time);
boolean P_GameRender(GLfloat delta_time);
boolean P_GameDestroy(void);

#endif
