/* =============================================================================
** SimmeredEggsEngine, file: u_lua.c Created 12/7/2021
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
#include "u_lua.h"
#include "u_log.h"

lua_State *currstate = NULL;
#define NULL_STATE(X) \
	if (currstate == NULL) \
		return X; \

boolean L_LuaCreate(lua_State *state) {
    state = luaL_newstate();
	if (state == NULL) {
		U_LogWrite(LOG_ERR, "L_LuaCreate(): failed to create state!\n");
		return false;
	}
	luaL_openlibs(state);
	return true;
}

void L_BindLuaState(lua_State *state) {
	currstate = state;
}

lua_State *L_GetLuaState(void) {
	return currstate;
}

void L_LuaError(lua_State *state, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	U_LogWrite(LOG_ERR, fmt, args);
	va_end(args);
	lua_close(state);
}

boolean L_LuaOkay(const int status) {
	if (status != 0) {
		U_LogWrite(LOG_ERR, "%s\n", lua_tostring(currstate, -1));
		return false;
	}
	return true;
}

void L_LuaDumpStack(lua_State *state) {
	const int top = lua_gettop(state);
    const enum logtype_t logtype = LOG_MSG;

	for (int i = 1; i < top; ++i) {
		int type = lua_type(state, i);
		switch (type) {
		case LUA_TNUMBER: {
			U_LogWrite(logtype, "%g", lua_tonumber(state, i));
			break;
		}
		case LUA_TBOOLEAN: {
			U_LogWrite(logtype, lua_toboolean(state, i)? "true" : "false");
			break;
		}
		case LUA_TSTRING: {
			U_LogWrite(logtype, "%s", lua_tostring(state, i));
			break;
		}
		default: {
			U_LogWrite(logtype, "%s", lua_typename(state, type));
			break;
	    }
		}
		U_LogWrite(logtype, " ");
	}
	U_LogWrite(logtype, "\n");
}

boolean L_DoString(const char *str) {
	NULL_STATE(false);
	const int result = luaL_dostring(currstate, str);
	return result;
}

boolean L_DoFile(const char *filename) {
	NULL_STATE(false);
	const int result = luaL_dofile(currstate, filename);
	return result;
}

void L_LuaDestroy(lua_State *state) {
	lua_close(state);
#ifndef LUA_VERBOSE
	U_LogWrite(logtype, "Closed lua_State.\n");
#endif
}

