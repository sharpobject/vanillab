#ifndef __LuaFunctionsH__
#define __LuaFunctionsH__

//These are functions that can be called from inside the lua instance.

int getX(lua_State *L);
int getY(lua_State *L);
int getTurn(lua_State *L);
int getRank(lua_State *L);
int getSpeedX(lua_State *L);
int getSpeedY(lua_State *L);
int getDirection(lua_State *L);
int getSpeed(lua_State *L);
int getID(lua_State *L);
int getNewest(lua_State *L);

int setSpeed(lua_State *L);
int setSpeedCartesian(lua_State *L);

int changeSpeed(lua_State *L);

int vanish(lua_State *L);

int setChildSprite(lua_State *L);
int setChildType(lua_State *L);

int fire(lua_State *L);
int fireCartesian(lua_State *L);

int setWaitFrames(lua_State *L);

#endif //LuaFunctionsH