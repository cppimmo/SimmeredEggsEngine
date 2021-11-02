#include "config.h"

bool config_load(const char *filename, Options *pOtions)
{
	if (!(pConfigFile = fopen(CONFIG_FILE, "r"))) {
		fprintf(stderr, "Failed to reading configuration file.\n");
		return false;
	}
	return true;
}

bool config_close()
{
	return true;
}

