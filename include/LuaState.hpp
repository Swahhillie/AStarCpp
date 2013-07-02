#ifndef LUASTATE_H
#define LUASTATE_H


#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaState
{
  lua_State *L;
public:
  LuaState() : L(lua_open()) { }

  ~LuaState() {
    lua_close(L);
  }

  // implicitly act as a lua_State pointer
  inline operator lua_State*() {
    return L;
  }
};

static int execute_program(lua_State *L)
{
  // make a short function to make program behaviour more clear
  return lua_pcall(L, 0, LUA_MULTRET, 0);
}

static void report_errors(lua_State *L, const int status)
{
  if ( status!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}

#endif // LUASTATE_H
