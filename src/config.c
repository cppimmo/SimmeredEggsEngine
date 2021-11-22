#include "config.h"
#include <unistd.h>

static FILE *p_config_file = NULL;

bool config_load(const char *filename, Options *p_options)
{
	p_config_file = fopen(filename, "r");
	if (p_config_file == NULL) {
		fprintf(stderr, "Failed to reading configuration file.\n");
		return false;
	}
	
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	while ((nread = getline(&line, &len, p_config_file)) != -1) {
		printf("Retrieved line of length %zd:\n", nread);
		fwrite(line, nread, 1, stdout);
	}

	free(line);
	return true;
}

void config_close()
{
	if (p_config_file != NULL) {
		fclose(p_config_file);
	}
}

