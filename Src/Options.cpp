/* =============================================================================
** SimmeredEggsEngine, file: Options.cpp Created 12/6/2021
**
** Copyright 2021 Brian Hoffpauir TX, USA
** All rights reserved.
**
** Redistribution and use of this source file, with or without modification, is
** permitted provided that the following conditions are met:
**
** 1. Redistributions of this source file must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
** EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** =============================================================================
**/
#include "Options.h"
#include "u_lua.h"

// #include <unistd.h>

// static FILE *confhandle = NULL;

boolean SEE::OptionsLoad(const std::string &fileName, Options &options)
{
	/* confhandle = fopen(filename, "r");
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

	free(line); */
	/*lua_State *state = L_LuaCreate();
	if (state == NULL) {
		fprintf(stderr, "G_OptionsLoad(): failed to create state!\n");
		return false;
	}
	L_LuaOpenLibraries(state);
	if (!L_DoFile(state, filename)) {
		fprintf(stderr, "G_OptionsLoad(): failed to do %s!\n", filename);
		return false;
	}

	L_GetGlobal(state, "options");
	if (!L_IsTable(state, -1)) {
		fprintf(stderr, "G_OptionsLoad(): no options global in %s!\n",
				filename);
		return false;
	}

	const char *title = L_TableGetString(state, "title");
	lua_Integer sizex = L_TableGetInteger(state, "sizex");
	lua_Integer sizey = L_TableGetInteger(state, "sizey");
	boolean fullscreen = L_TableGetBoolean(state, "fullscreen");
	lua_Integer refreshrate = L_TableGetInteger(state, "refreshrate");
	boolean vsync = L_TableGetBoolean(state, "vsync");
	lua_Integer quality = L_TableGetInteger(state, "quality");
	printf("crap: %s, %d, %d, %d, %d, %d, %d\n",
		   title, sizex, sizey, fullscreen, refreshrate, vsync, quality);*/
	return true;
}

inline void SEE::OptionsClose(void)
{
	/* if (confhandle != NULL) {
		fclose(confhandle);
	} */
}

