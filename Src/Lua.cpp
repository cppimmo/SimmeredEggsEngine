/* =============================================================================
** SimmeredEggsEngine, file: Lua.cpp Created 12/7/2021
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
#include "Lua.h"
#include "Log.h"

/* static void L_LuaError(lua_State *state, const char *fmt, ...);

lua_State *L_LuaCreate(void) {
	return luaL_newstate();
}

void L_LuaOpenLibraries(lua_State *state) {
	luaL_openlibs(state);
}

static void L_LuaError(lua_State *state, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	SEE::LogWrite(SEE::LogType::LOG_ERR, fmt, args);
	va_end(args);
	lua_close(state);
}

boolean L_LuaOkay(lua_State *state, const int status) {
	if (status != 0) {
		SEE::LogWrite(SEE::LogType::LOG_ERR, "%s\n", lua_tostring(state, -1));
		return false;
	}
	return true;
}

void L_LuaDumpStack(lua_State *state) {
	const int top = lua_gettop(state);
    const enum logtype_t logtype = SEE::LogType::LOG_MSG;

	for (int i = 1; i < top; ++i) {
		int type = lua_type(state, i);
		switch (type) {
		case LUA_TNUMBER: {
			SEE::LogWrite(logtype, "%g", lua_tonumber(state, i));
			break;
		}
		case LUA_TBOOLEAN: {
			SEE::LogWrite(logtype, lua_toboolean(state, i)? "true" : "false");
			break;
		}
		case LUA_TSTRING: {
			SEE::LogWrite(logtype, "%s", lua_tostring(state, i));
			break;
		}
		default: {
			SEE::LogWrite(logtype, "%s", lua_typename(state, type));
			break;
	    }
		}
		SEE::LogWrite(logtype, " ");
	}
	SEE::LogWrite(logtype, "\n");
}

boolean L_DoString(lua_State *state, const char *str) {
    return (luaL_dostring(state, str) > 0)? false : true;
}

boolean L_DoFile(lua_State *state, const char *filename) {
	// the below needs to be fixed, add preprocessor max math to u_deftypes.h
	char filepath[256 + 1 + 256];
	strcat(filepath, LUA_DIR);
	strcat(filepath, filename);
	return (luaL_dofile(state, filepath) > 0)? false : true;
}

boolean L_IsNil(lua_State *state, int index) {
	return lua_isnil(state, index);
}

boolean L_IsTable(lua_State *state, int index) {
	return lua_istable(state, index);
}

boolean L_IsUserData(lua_State *state, int index) {
	return lua_isuserdata(state, index);
}

boolean L_IsCFunction(lua_State *state, int index) {
	return lua_isfunction(state, index);
}

boolean L_IsNumber(lua_State *state, int index) {
	return lua_isnumber(state, index);
}

boolean L_IsString(lua_State *state, int index) {
	return lua_isstring(state, index);
}

boolean L_IsConvertibleToNumber(lua_State *state, int index) {
	return lua_isnumber(state, index);
}

boolean L_IsFunction(lua_State *state, int index) {
	return lua_isfunction(state, index);
}

boolean L_IsNone(lua_State *state, int index) {
	return lua_isnone(state, index);
}

boolean L_IsLightUserData(lua_State *state, int index) {
	return lua_islightuserdata(state, index);
}

boolean L_IsBoolean(lua_State *state, int index) {
	return lua_isboolean(state, index);
}

lua_Integer L_GetInteger(lua_State *state, int index) {
	return lua_tointeger(state, index);
}

float L_GetFloat(lua_State *state, int index) {
	return (float)lua_tonumber(state, index);
}

double L_GetDouble(lua_State *state, int index) {
	return (double)lua_tonumber(state, index);
}

void L_GetGlobal(lua_State *state, const char *name) {
	lua_getglobal(state, name);
}

const char *L_GetString(lua_State *state, int index, size_t *len) {
	return lua_tolstring(state, index, len);
}

void *L_GetUserData(lua_State *state, int index) {
	return lua_touserdata(state, index);
}

void *L_GetLightUserData(lua_State *state, int index) {
	return NULL;
}

boolean L_GetBoolean(lua_State *state, int index) {
	return lua_toboolean(state, index);
}

void L_AssignNil(lua_State *state) {
	lua_pushnil(state);
}

void L_AssignBoolean(lua_State *state, boolean value) {
	lua_pushboolean(state, value);
}

void L_AssignInteger(lua_State *state, lua_Integer value) {
	lua_pushinteger(state, value);
}

void L_AssignNumber(lua_State *state, lua_Number value) {
	lua_pushnumber(state, value);
}

void L_AssignString(lua_State *state, const char *value) {
	lua_pushstring(state, value);
}

void L_AssignUserData(lua_State *state, void *value) {
	lua_pushlightuserdata(state, value);
}

void L_AssignLightUserData(lua_State *state, void *value) {
	lua_pushlightuserdata(state, value);
}

// void L_AssignObject(lua_State *state) { }

void L_AssignNewTable(lua_State *state, int narray, int nhash) {
	// lua_pusha
}

void L_TableSetNil(lua_State *state, const char *key) {

}

void L_TableSetBoolean(lua_State *state, const char *key, boolean value) {

}

void L_TableSetInteger(lua_State *state, const char *key, lua_Integer value) {

}

void L_TableSetNumber(lua_State *state, const char *key, lua_Number value) {

}

void L_TableSetString(lua_State *state, const char *key, const char *value) {

}

void L_TableSetUserData(lua_State *state, const char *key, void *value) {

}

void L_TableSetLightUserData(lua_State *state, const char *key, void *value) {

}

// void L_TableSetObject(const char *key) { }

boolean L_TableGetBoolean(lua_State *state, const char *key) {
	boolean result;
	lua_getfield(state, -1, key);
	if (!lua_isboolean(state, -1))
		L_LuaError(state, "not boolean");
	result = (boolean)lua_toboolean(state, -1);
	lua_pop(state, 1);
	return result;
}

lua_Integer L_TableGetInteger(lua_State *state, const char *key) {
	lua_Integer result;
	lua_getfield(state, -1, key);
	if (!lua_isnumber(state, -1))
		L_LuaError(state, "not integer");
	result = lua_tointeger(state, -1);
	lua_pop(state, 1);
	return result;
}

lua_Number L_TableGetNumber(lua_State *state, const char *key) {
	lua_Number result;
	lua_getfield(state, -1, key);
	if (!lua_isnumber(state, -1))
		L_LuaError(state, "not number");
	result = lua_tonumber(state, -1);
	lua_pop(state, 1);
	return result;
}

const char *L_TableGetString(lua_State *state, const char *key) {
	const char *result;
	lua_getfield(state, -1, key);
	if (!lua_isstring(state, -1))
		L_LuaError(state, "not string");
	result = lua_tostring(state, -1);
	lua_pop(state, 1);
	return result;
}

void *L_TableGetUserData(lua_State *state, const char *key) {
	return NULL;
}

void *L_TableGetLightUserData(lua_State *state, const char *key) {
	return NULL;
}

void L_LuaDestroy(lua_State *state) {
	lua_close(state);
#ifndef LUA_VERBOSE
	SEE::LogWrite(logtype, "Closed lua_State.\n");
#endif
}
*/

