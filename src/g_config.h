#ifndef __G_CONFIG_H__
#define __G_CONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include "u_utility.h"

#define CONFIG_FILE "starshipfleet.ini"

struct config_t {
	char title[75];
	unsigned int sizex;
	unsigned int sizey;
	boolean fullscreen;
	unsigned int refreshrate;
	boolean vsync;
	unsigned int quality;
};

boolean G_ConfigLoad(const char *filename, struct config_t *const options);
void G_ConfigClose(void);

#endif
