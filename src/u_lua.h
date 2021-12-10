/* =============================================================================
** SimmeredEggsEngine, file: u_lua.h Created 12/7/2021
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
#ifndef __U_LUA_H__
#define __U_LUA_H__

#include "u_utility.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#ifdef __cplusplus
}
#endif
/* Wrapper for Lua version 5.1 */

#include <stdarg.h>

#ifndef NDEBUG
#define LUA_VERBOSE
#else
#define LUA_SHUTUP
#endif

#define LUA_DIR "assets/scripts/"

lua_State *L_LuaCreate(void);
void L_LuaOpenLibraries(lua_State *state);
// void L_BindLuaState(lua_State *state);
// lua_State *L_GetLuaState(void);
boolean L_LuaOkay(lua_State *state, const int status);
void L_LuaDumpStack(lua_State *state);
boolean L_DoString(lua_State *state, const char *str);
boolean L_DoFile(lua_State *state, const char *filename);
boolean L_IsNil(lua_State *state, int index);
boolean L_IsTable(lua_State *state, int index);
boolean L_IsUserData(lua_State *state, int index);
boolean L_IsCFunction(lua_State *state, int index);
boolean L_IsNumber(lua_State *state, int index);
boolean L_IsString(lua_State *state, int index);
boolean L_IsConvertibleToNumber(lua_State *state, int index);
boolean L_IsFunction(lua_State *state, int index);
boolean L_IsNone(lua_State *state, int index);
boolean L_IsLightUserData(lua_State *state, int index);
boolean L_IsBoolean(lua_State *state, int index);
lua_Integer L_GetInteger(lua_State *state, int index);
float L_GetFloat(lua_State *state, int index);
double L_GetDouble(lua_State *state, int index);
void L_GetGlobal(lua_State *state, const char *name);
const char *L_GetString(lua_State *state, int index, size_t *len);
void *L_GetUserData(lua_State *state, int index);
void *L_GetLightUserData(lua_State *state, int index);
boolean L_GetBoolean(lua_State *state, int index);
void L_AssignNil(lua_State *state);
void L_AssignBoolean(lua_State *state, boolean value);
void L_AssignInteger(lua_State *state, lua_Integer value);
void L_AssignNumber(lua_State *state, lua_Number value);
void L_AssignString(lua_State *state, const char *value);
void L_AssignUserData(lua_State *state, void *value);
void L_AssignLightUserData(lua_State *state, void *value);
// void L_AssignObject(lua_State *state);
void L_AssignNewTable(lua_State *state, int narray, int nhash);
void L_TableSetNil(lua_State *state, const char *key);
void L_TableSetBoolean(lua_State *state, const char *key, boolean value);
void L_TableSetInteger(lua_State *state, const char *key, lua_Integer value);
void L_TableSetNumber(lua_State *state, const char *key, lua_Number value);
void L_TableSetString(lua_State *state, const char *key, const char *value);
void L_TableSetUserData(lua_State *state, const char *key, void *value);
void L_TableSetLightUserData(lua_State *state, const char *key, void *value);
boolean L_TableGetBoolean(lua_State *state, const char *key);
lua_Integer L_TableGetInteger(lua_State *state, const char *key);
lua_Number L_TableGetNumber(lua_State *state, const char *key);
const char *L_TableGetString(lua_State *state, const char *key);
void *L_TableGetUserData(lua_State *state, const char *key);
void *L_TableGetLightUserData(lua_State *state, const char *key);
// void L_TableSetObject(const char *key);
void L_LuaDestroy(lua_State *state);

#endif
