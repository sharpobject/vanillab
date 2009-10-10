#include "util.h"
#include "objman.h"
#include "luafunctions.h"

extern ObjMan *gObjMan;

int getX(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getX());
	return 1;
}

int getY(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getY());
	return 1;
}

int getTurn(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getTurn());
	return 1;
}

int getRank(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getRank());
	return 1;
}

int getSpeedX(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getSpeedX());
	return 1;
}

int getSpeedY(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getSpeedY());
	return 1;
}

int getDirection(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getDirection());
	return 1;
}

int getSpeed(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getSpeed());
	return 1;
}

int getID(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getID());
	return 1;
}

int getNewest(lua_State *L)
{
	lua_pushnumber(L,gObjMan->getNewest());
	return 1;
}

int setSpeed(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=2)
	{
		MessageBox(0, "setSpeed() failed - wrong number of args", 0, 0);
		return 0;
	}
	float r=lua_tonumber(L,1),theta=lua_tonumber(L,2);
	gObjMan->setSpeed(r,theta);
	return 0;
}

int setSpeedCartesian(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=2)
	{
		MessageBox(0, "setSpeedCartesian() failed - wrong number of args", 0, 0);
		return 0;
	}
	float x=lua_tonumber(L,1),y=lua_tonumber(L,2);
	gObjMan->setSpeedCartesian(x,y);
	return 0;
}

int changeSpeed(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=2)
	{
		MessageBox(0, "changeSpeed() failed - wrong number of args", 0, 0);
		return 0;
	}
	float speed=lua_tonumber(L,1);
	int turns=(int)lua_tonumber(L,2);
	if(turns<=0)
	{
		MessageBox(0, "changeSpeed() failed - turns must be positive", 0, 0);
		return 0;
	}
	gObjMan->changeSpeed(speed,turns);
}

int vanish(lua_State *L)
{
	gObjMan->vanish();
	return 0;
}

int setChildSprite(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=1)
	{
		MessageBox(0, "setChildSprite() failed - wrong number of args", 0, 0);
		return 0;
	}
	gObjMan->setChildSprite(  (SpriteName)  ((int)lua_tonumber(L,1))  );
	return 0;
}
int setChildType(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=1)
	{
		MessageBox(0, "setChildSprite() failed - wrong number of args", 0, 0);
		return 0;
	}
	gObjMan->setChildType(  (ObjectClass)  ((int)lua_tonumber(L,1))  );
	return 0;
}

int setWaitFrames(lua_State *L)
{
	int n = lua_gettop(L);
	if(n!=1)
	{
		MessageBox(0, "setWaitFrames() failed - wrong number of args", 0, 0);
		return 0;
	}
	gObjMan->setWaitFrames((int)lua_tonumber(L,1));
	return 0;
}

int fire(lua_State *L)
{
	int n = lua_gettop(L);
	if(n<2||n>3)
	{
		MessageBox(0, "fire() failed - wrong number of args", 0, 0);
		return 0;
	}
	float r=lua_tonumber(L,1),theta=lua_tonumber(L,2);
	gObjMan->fire(r,theta);

	return 0;
}