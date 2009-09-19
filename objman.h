#ifndef __ObjManH__
#define __ObjManH__

#include "util.h"
#include "object.h"
#include "sprites.h"
#include <list>
#include <algorithm>

using namespace std;

class ObjMan
{
public:
	ObjMan();
	void run(unsigned char*);
	void draw();
	int add(Object &o);
	void makedude();
	~ObjMan();
	int size();

	//A set of functions for manipulating the active object.
	float getX(){return objects[activeObject].x;}
	float getY(){return objects[activeObject].y;}
	float getTurn(){return (float)objects[activeObject].age;}
	float getRank(){return rank;}
	float getSpeedX(){return getXFromPolar(objects[activeObject].speed,objects[activeObject].direction);}
	float getSpeedY(){return getYFromPolar(objects[activeObject].speed,objects[activeObject].direction);}
	float getDirection(){return objects[activeObject].direction;}
	float getSpeed(){return objects[activeObject].speed;}
	float getID(){return (float)activeObject;}
	void setSpeed(float r,float theta)
	{
		objects[activeObject].speed=r;
		objects[activeObject].direction=theta;
	}
	void setSpeedCartesian(float x,float y)
	{
		float r,theta;
		getPolar(x,y,r,theta);
		setSpeed(r,theta);
	}
	void vanish(){objects[activeObject].dead=true;}
	void setWaitFrames(int n){objects[activeObject].waitFrames=n;}
	void fire(float r,float theta)
	{
		Object o(objects[activeObject].x,
				objects[activeObject].y,
				theta,r,
				SPR_MED_CIR_BULLET,
				ENEMY_BULLET);
		add(o);
	}

private:
	void run(int);
	void draw(int);


	//This is an array in which linked lists will exist.
	Object objects[MAX_N_OBJECTS];
	//These are the available entries in the above array.  As a stack.
	int freeIndices[MAX_N_OBJECTS];
	int nFreeIndices;
	//These are pointers to the heads of awesome linked lists of awesome.
	int heads[N_OBJECT_CLASSES],tails[N_OBJECT_CLASSES];

	//I don't know why this is here.
	float rank;
	
	
	//The active object.  Lua functions that change object variables will act on it.
	//Depending on what I end up doing it may belong in Object instead.
	int activeObject;
};


#endif //__ObjManH__