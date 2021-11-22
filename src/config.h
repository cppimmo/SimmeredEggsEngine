#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONFIG_FILE "starshipfleet.ini"

typedef struct {
	char window_title[75];
	size_t window_size_x;
	size_t window_size_y;
	bool is_fullscreen;
	unsigned int refresh_rate;
	bool vsync_enabled;
	unsigned int graphics_quality;
} Options;

bool config_load(const char *filename, Options *p_options);
void config_close();

#endif // CONFIG_H
