#include "g_config.h"
#include <unistd.h>

static FILE *confhandle = NULL;

boolean G_ConfigLoad(const char *filename, struct config_t *const config) {
	confhandle = fopen(filename, "r");
	if (confhandle == NULL) {
		fprintf(stderr, "Failed to reading configuration file.\n");
		return false;
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	while ((nread = getline(&line, &len, confhandle)) != -1) {
		printf("Retrieved line of length %zd:\n", nread);
		fwrite(line, nread, 1, stdout);
	}

	free(line);
	return true;
}

void G_ConfigClose(void) {
	if (confhandle != NULL) {
		fclose(confhandle);
	}
}

