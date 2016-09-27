#include <string>

extern "C"{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

using std::string;

bool luaRun(const std::string& expression,double &result,string& errorMessage)
{
    lua_State *L = luaL_newstate();

    string expr = "result = "+expression;

    if(luaL_dostring (L, expr.c_str()))
    {
        errorMessage=string("lua error: ")+lua_tostring(L, -1);
        lua_close(L);
        return false;
    }

    lua_getglobal(L, "result");
    result = lua_tonumber(L,-1);

    lua_close(L);

    return true;
}
