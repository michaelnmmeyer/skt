#include <lua.h>
#include <lauxlib.h>

#include "../skt.h"

/* Begin compatibility code for Lua 5.1. Copy-pasted from Lua's source. */
#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM == 501

static void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
  luaL_checkstack(L, nup+1, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    lua_pushstring(L, l->name);
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      lua_pushvalue(L, -(nup+1));
    lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    lua_settable(L, -(nup + 3));
  }
  lua_pop(L, nup);  /* remove upvalues */
}

#define luaL_newlibtable(L,l) \
  lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)

#define luaL_newlib(L,l)   (luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))

#endif
/* End compatibility code. */


static int lua_skt_translit(lua_State *lua)
{
   size_t len;
   const char *str = luaL_checklstring(lua, 1, &len);

   const char *input = luaL_optstring(lua, 2, "velthuis");
   const char *output = luaL_optstring(lua, 3, "iast");
   skt_translit func = skt_translit_func(input, output);
   if (!func) {
      lua_pushnil(lua);
      lua_pushfstring(lua, "no such mapping: %s -> %s", input, output);
      return 2;
   }

   struct skt_buf buf = SKT_BUF_INIT;
   func(&buf, str, len);
   lua_pushlstring(lua, buf.data, buf.size);
   skt_buf_fini(&buf);

   return 1;
}

static int lua_skt_sort_key(lua_State *lua)
{
   size_t len;
   const char *str = luaL_checklstring(lua, 1, &len);

   struct skt_buf buf = SKT_BUF_INIT;
   skt_sort_key(&buf, str, len);
   lua_pushlstring(lua, buf.data, buf.size);
   skt_buf_fini(&buf);

   return 1;
}

static void add_constants(lua_State *lua)
{
   lua_newtable(lua);
   for (int i = 0; skt_schemes[i]; i++) {
      lua_pushstring(lua, skt_schemes[i]);
      lua_rawseti(lua, -2, i + 1);
   }
   lua_setfield(lua, -2, "schemes");
}

int luaopen_skt(lua_State *lua)
{
   const luaL_Reg lib[] = {
      {"translit", lua_skt_translit},
      {"sort_key", lua_skt_sort_key},
      {NULL, 0},
   };
   luaL_newlib(lua, lib);
   add_constants(lua);
   return 1;
}
