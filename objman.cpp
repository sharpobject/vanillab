#include "objman.h"
#include "util.h"
#include <dinput.h>

using namespace std;

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
}

void ObjMan::draw(int idx)
{
	int myguy=heads[idx];
	while(myguy!=-1)
	{
		objects[myguy].draw();
		myguy=objects[myguy].next;
	}
}

void ObjMan::run(int idx)
{
	int myguy=heads[idx];
	while(myguy!=-1)
	{
		objects[myguy].run();
		if(objects[myguy].isDead())
		{
			//Link up the adjacent objects.
			if(objects[myguy].prev!=-1)
				objects[objects[myguy].prev].next=objects[myguy].next;
			if(objects[myguy].next!=-1)
				objects[objects[myguy].next].prev=objects[myguy].prev;
			//Add my ID to the pool of available IDs.
			freeIndices[nFreeIndices++]=myguy;
			//Adjust head and tail entries if necessary.
			if(heads[idx]==myguy)
				heads[idx]=objects[myguy].next;
			if(tails[idx]==myguy)
				tails[idx]=objects[myguy].prev;
		}
		myguy=objects[myguy].next;
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
		pspeed*=4;
		if(input[DIK_LSHIFT])
			pspeed*=.5f;
		objects[heads[PLAYER]].speed=pspeed;
		if(pspeed!=0.0f)
			objects[heads[PLAYER]].direction=pdirection;
	}
	for(int i=0;i<N_OBJECT_CLASSES;i++)
		run(i);
}

void ObjMan::draw()
{
	for(int i=0;i<N_OBJECT_CLASSES;i++)
		draw(i);
}

void ObjMan::add(Object &o)
{
	if(nFreeIndices==0)
	{
//		MessageBox(0, "Objman::add() - no room for more objects!", 0, 0);
		return;
	}
	int slot=freeIndices[nFreeIndices-1];
	nFreeIndices--;
	objects[slot]=o;
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
}

void ObjMan::makedude()
{
	Object o(1024.0f/2.0f,768.0f/2.0f,FACING_DOWN,0.0f,SPR_ARROW,ENEMY);
	add(o);
}

int ObjMan::size()
{
	return MAX_N_OBJECTS-nFreeIndices;
}