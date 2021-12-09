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

#define LUA_DIR "scripts/"

boolean L_LuaCreate(lua_State *state);
void L_BindLuaState(lua_State *state);
lua_State *L_GetLuaState(void);
void L_LuaError(lua_State *state, const char *fmt, ...);
boolean L_LuaOkay(const int status);
void L_LuaDumpStack(lua_State *state);
boolean L_DoString(const char *str);
boolean L_DoFile(const char *filename);
boolean L_IsNil(void);
boolean L_IsTable(void);
boolean L_IsUserData(void);
boolean L_IsCFunction(void);
boolean L_IsNumber(void);
boolean L_IsString(void);
boolean L_IsConvertibleToNumber(void);
boolean L_IsFunction(void);
boolean L_IsNone(void);
boolean L_IsLightUserData(void);
boolean L_IsBoolean(void);
int L_GetInteger(void);
float L_GetFloat(void);
double L_GetDouble(void);
const char *L_GetString(void);
void *L_GetUserData(void);
void *L_GetLightUserData(void);
boolean L_GetBoolean(void);
void L_AssignNil(lua_State *state);
void L_AssignBoolean(lua_State *state, boolean value);
void L_AssignInteger(lua_State *state, int value);
void L_AssignNumber(lua_State *state, double value);
void L_AssignString(lua_State *state, const char *value);
void L_AssignUserData(lua_State *state, void *value);
void L_AssignLightUserData(lua_State *state, void *value);
// void L_AssignObject(lua_State *state);
void L_AssignNewTable(lua_State *state, int narray, int nhash);
void L_TableSetNil(const char *key);
void L_TableSetBoolean(const char *key, boolean value);
void L_TableSetInteger(const char *key, int value);
void L_TableSetNumber(const char *key, double value);
void L_TableSetString(const char *key, const char *value);
void L_TableSetUserData(const char *key, void *value);
void L_TableSetLightUserData(const char *key, void *value);
// void L_TableSetObject(const char *key);
void L_LuaDestroy(lua_State *state);

#endif
