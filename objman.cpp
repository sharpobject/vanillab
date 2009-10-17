#include "objman.h"
#include "util.h"
#include <dinput.h>

using namespace std;

extern lua_State *gLua;

ObjMan::ObjMan()
{
	for(int i=0;i<MAX_N_OBJECTS;i++)
		freeIndices[i]=MAX_N_OBJECTS-i-1;
	nFreeIndices=MAX_N_OBJECTS-1;
	for(int i=0;i<N_OBJECT_CLASSES;i++)
		heads[i]=tails[i]=-1;
	heads[PLAYER]=tails[PLAYER]=0;
	Object player(512,700,FACING_UP,0.0,SPR_PLAYER,PLAYER);
	objects[0]=player;
	objects[0].id=0;
	rank=.5f;
}

void ObjMan::bucketsort(int n)
{
	for(int i=0;i<N_SPRITES;i++)
		bucketsz[i]=0;
	for(int i=0;i<n;i++)
	{
		SpriteName thesprite=objects[drawbuffer[i]].sprite;
		buckets[thesprite][bucketsz[thesprite]++]=drawbuffer[i];
	}
	for(int i=0,bufferidx=0;i<N_SPRITES;i++)
		for(int j=0;j<bucketsz[i];j++)
			objects[buckets[i][j]].draw();
}

void ObjMan::draw(int idx)
{
	int myguy=heads[idx];
	int drawbuffersz=0;
	while(myguy!=-1)
	{
		drawbuffer[drawbuffersz++]=myguy;//objects[myguy].draw();
		myguy=objects[myguy].next;
	}
	bucketsort(drawbuffersz);
}

void ObjMan::checkDeadness(int idx)
{
	if(objects[activeObject].isDead())
	{
		lua_pushstring(gLua,"cleanup");
		lua_gettable(gLua,LUA_GLOBALSINDEX);
		lua_call(gLua,0,0);
		//Link up the adjacent objects.
		if(objects[activeObject].prev!=-1)
			objects[objects[activeObject].prev].next=objects[activeObject].next;
		if(objects[activeObject].next!=-1)
			objects[objects[activeObject].next].prev=objects[activeObject].prev;
		//Add my ID to the pool of available IDs.
		freeIndices[nFreeIndices++]=activeObject;
		//Adjust head and tail entries if necessary.
		if(heads[idx]==activeObject)
			heads[idx]=objects[activeObject].next;
		if(tails[idx]==activeObject)
			tails[idx]=objects[activeObject].prev;
	}
}

void ObjMan::run(int idx)
{
	activeObject=heads[idx];
	while(activeObject!=-1)
	{
		objects[activeObject].run();
		checkDeadness(idx);
		activeObject=objects[activeObject].next;
	}
}

void ObjMan::collision(ObjectClass a,ObjectClass b)
{
	int i=heads[a];
	while(i!=-1)
	{
		float ix=objects[i].x;
		float iy=objects[i].y;
		float iradius=gSpriteCollisionRadius[objects[i].sprite];
		int j=heads[b];
		while(j!=-1)
		{
			float dx=objects[j].x-ix;
			float dy=objects[j].y-iy;
			float jradius=gSpriteCollisionRadius[objects[j].sprite];
			if(dx*dx+dy*dy<iradius*iradius+2*iradius*jradius+jradius*jradius)
			{
				int damage=min(objects[j].health,objects[i].health);
				objects[j].health-=damage;
				objects[i].health-=damage;
				if(objects[j].health==0)objects[j].dead=true;
				if(objects[i].health==0)objects[i].dead=true;
			}
			j=objects[j].next;
		}
		i=objects[i].next;
	}
	activeObject=heads[a];
	while(activeObject!=-1)
	{
		checkDeadness(a);
		activeObject=objects[activeObject].next;
	}
	activeObject=heads[b];
	while(activeObject!=-1)
	{
		checkDeadness(b);
		activeObject=objects[activeObject].next;
	}
}

void ObjMan::run(unsigned char* input)
{
	if(heads[PLAYER]!=-1)
	{
		float pdx=0,pdy=0,pdirection=0,pspeed=0;
		if(input[DIK_UP])
			pdy-=1;
		if(input[DIK_DOWN])
			pdy+=1;
		if(input[DIK_LEFT])
			pdx-=1;
		if(input[DIK_RIGHT])
			pdx+=1;
		getPolar(pdx,pdy,pspeed,pdirection);
		pspeed=min(1.0f,pspeed);
		pspeed*=7;
		if(input[DIK_LSHIFT])
			pspeed*=.5f;
		objects[heads[PLAYER]].speed=pspeed;
		if(pspeed!=0.0f)
			objects[heads[PLAYER]].direction=pdirection;
	}
	for(int i=0;i<N_OBJECT_CLASSES;i++)
		run(i);
	collision(ENEMY_BULLET,PLAYER);
	collision(PLAYER,ENEMY);
	collision(PLAYER_BULLET,ENEMY);
}

void ObjMan::draw()
{
	for(int i=0;i<N_OBJECT_CLASSES;i++)
		draw(i);
}

int ObjMan::add(Object &o)
{
	if(nFreeIndices==0)
	{
//		MessageBox(0, "Objman::add() - no room for more objects!", 0, 0);
		return -1;
	}
	int slot=freeIndices[nFreeIndices-1];
	newestObject=slot;
	nFreeIndices--;
	objects[slot]=o;
	objects[slot].id=slot;
	int type=o.myclass;
	if(heads[type]==-1)
	{
		heads[type]=tails[type]=slot;
	}
	else
	{
		objects[tails[type]].next=slot;
		objects[slot].prev=tails[type];
		tails[type]=slot;
	}
	return slot;
}

void ObjMan::makedude()
{
	Object o(256,256,FACING_DOWN,0.0f,SPR_APPLE,ENEMY);
	add(o);
	luaL_dostring(gLua,"register(bossturret);");
}

int ObjMan::size()
{
	return MAX_N_OBJECTS-nFreeIndices;
}