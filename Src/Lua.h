/* =============================================================================
** SimmeredEggsEngine, file: Lua.h Created 12/7/2021
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
#ifndef __LUA_H__
#define __LUA_H__

#include "Utility.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

/* Wrapper for Lua version 5.1 */

#include <stdarg.h>

#ifndef NDEBUG
#define LUA_VERBOSE
#else
#define LUA_SHUTUP
#endif

#define LUA_DIR "assets/scripts/"

namespace SEE
{

// using LuaState = lua_State;
using LuaInteger = lua_Integer;
using LuaNumber = lua_Number;

class LuaState;
class LuaObject;

class LuaManager
{
public:
	LuaManager(void);
	LuaManager(const LuaManager&);
	LuaManager &operator=(const LuaManager&);
	LuaManager(LuaManager&&);
	LuaManager &operator=(LuaManager&&);
	~LuaManager(void);

	boolean Init(void);
	void OpenLibraries(void);
private:
	static boolean Error(const LuaState &state, const int status);
	static void DumpStack(const LuaState &state);
private:
	LuaState state;
};

class LuaState
{
public:
	LuaState(void);
	~LuaState(void);
private:
	lua_State *pState;
};

class LuaObject
{
public:

private:

};

}

/* LLuaState *L_LuaCreate(void);
void L_LuaOpenLibraries(LLuaState *state);
// void L_BindLuaState(LLuaState *state);
// LLuaState *L_GetLuaState(void);
boolean L_LuaOkay(LLuaState *state, const int status);
void L_LuaDumpStack(LLuaState *state);
boolean L_DoString(LLuaState *state, const char *str);
boolean L_DoFile(LLuaState *state, const char *filename);
boolean L_IsNil(LLuaState *state, int index);
boolean L_IsTable(LLuaState *state, int index);
boolean L_IsUserData(LLuaState *state, int index);
boolean L_IsCFunction(LLuaState *state, int index);
boolean L_IsNumber(LLuaState *state, int index);
boolean L_IsString(LLuaState *state, int index);
boolean L_IsConvertibleToNumber(LLuaState *state, int index);
boolean L_IsFunction(LLuaState *state, int index);
boolean L_IsNone(LLuaState *state, int index);
boolean L_IsLightUserData(LLuaState *state, int index);
boolean L_IsBoolean(LLuaState *state, int index);
lua_Integer L_GetInteger(LLuaState *state, int index);
float L_GetFloat(LLuaState *state, int index);
double L_GetDouble(LLuaState *state, int index);
void L_GetGlobal(LLuaState *state, const char *name);
const char *L_GetString(LLuaState *state, int index, size_t *len);
void *L_GetUserData(LLuaState *state, int index);
void *L_GetLightUserData(LLuaState *state, int index);
boolean L_GetBoolean(LLuaState *state, int index);
void L_AssignNil(LLuaState *state);
void L_AssignBoolean(LLuaState *state, boolean value);
void L_AssignInteger(LLuaState *state, lua_Integer value);
void L_AssignNumber(LLuaState *state, lua_Number value);
void L_AssignString(LLuaState *state, const char *value);
void L_AssignUserData(LLuaState *state, void *value);
void L_AssignLightUserData(LLuaState *state, void *value);
// void L_AssignObject(LLuaState *state);
void L_AssignNewTable(LLuaState *state, int narray, int nhash);
void L_TableSetNil(LLuaState *state, const char *key);
void L_TableSetBoolean(LLuaState *state, const char *key, boolean value);
void L_TableSetInteger(LLuaState *state, const char *key, lua_Integer value);
void L_TableSetNumber(LLuaState *state, const char *key, lua_Number value);
void L_TableSetString(LLuaState *state, const char *key, const char *value);
void L_TableSetUserData(LLuaState *state, const char *key, void *value);
void L_TableSetLightUserData(LLuaState *state, const char *key, void *value);
boolean L_TableGetBoolean(LLuaState *state, const char *key);
lua_Integer L_TableGetInteger(LLuaState *state, const char *key);
lua_Number L_TableGetNumber(LLuaState *state, const char *key);
const char *L_TableGetString(LLuaState *state, const char *key);
void *L_TableGetUserData(LLuaState *state, const char *key);
void *L_TableGetLightUserData(LLuaState *state, const char *key);
// void L_TableSetObject(const char *key);
void L_LuaDestroy(LLuaState *state); */

#endif
