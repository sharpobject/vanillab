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
	//Putting these all in the header was a really dumb idea.
	//It seemed appealing because att he time I was only implementing the simple ones.
	//Move them to the source file sometime.
	float getX(){return objects[activeObject].x;}
	float getY(){return objects[activeObject].y;}
	float getTurn(){return (float)objects[activeObject].age;}
	float getRank(){return rank;}
	float getSpeedX(){return getXFromPolar(objects[activeObject].speed,objects[activeObject].direction);}
	float getSpeedY(){return getYFromPolar(objects[activeObject].speed,objects[activeObject].direction);}
	float getDirection(){return objects[activeObject].direction;}
	float getSpeed(){return objects[activeObject].speed;}
	float getID(){return (float)activeObject;}
	float getNewest(){return (float)newestObject;}
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
	void changeSpeed(float speed,int turns)
	{
		objects[activeObject].accel=(speed-objects[activeObject].speed)/turns;
		objects[activeObject].accelTurns=turns;
	}
	void changeDirection(float direction,int turns)
	{
		direction=fmod(30*FULL_CIRCLE+direction,FULL_CIRCLE);
		objects[activeObject].direction=fmod(30*FULL_CIRCLE+objects[activeObject].direction,FULL_CIRCLE);
		objects[activeObject].rotation=(direction-objects[activeObject].direction)/turns;
		objects[activeObject].rotationTurns=turns;
		if(direction-objects[activeObject].direction>PI)
			objects[activeObject].rotation=(direction-objects[activeObject].direction-FULL_CIRCLE)/turns;
		else if(direction-objects[activeObject].direction<-PI)
			objects[activeObject].rotation=(direction-objects[activeObject].direction+FULL_CIRCLE)/turns;
	}
	float aim()
	{
		if(heads[PLAYER]==-1)
			return FACING_DOWN;
		return getTheta(objects[heads[PLAYER]].x-objects[activeObject].x,
			objects[heads[PLAYER]].y-objects[activeObject].y);
	}
	void vanish(){objects[activeObject].dead=true;}
	void setChildSprite(SpriteName s){objects[activeObject].childinfo.sprite=s;}
	void setChildType(ObjectClass c){objects[activeObject].childinfo.myclass=c;}
	void setWaitFrames(int n){objects[activeObject].waitFrames=n;}
	void fire(float r,float theta)
	{
		Object o(objects[activeObject].x,
				objects[activeObject].y,
				theta,r,
				objects[activeObject].childinfo.sprite,
				objects[activeObject].childinfo.myclass);
		add(o);
	}

private:
	void run(int);
	void draw(int);
	void bucketsort(int);
	void collision(ObjectClass,ObjectClass);
	void checkDeadness(int idx);


	//This is an array in which linked lists will exist.
	Object objects[MAX_N_OBJECTS];
	//These are the available entries in the above array.  As a stack.
	int freeIndices[MAX_N_OBJECTS];
	int nFreeIndices;
	
	//Stuff for sorting objects to be drawn.
	int drawbuffer[MAX_N_OBJECTS];
	int buckets[N_SPRITES][MAX_N_OBJECTS];
	int bucketsz[N_SPRITES];

	//These are pointers to the heads of awesome linked lists of awesome.
	int heads[N_OBJECT_CLASSES],tails[N_OBJECT_CLASSES];

	//I don't know why this is here.
	float rank;
	
	
	//The active object.  Lua functions that change object variables will act on it.
	//Depending on what I end up doing it may belong in Object instead.
	int activeObject;
	//This is here mainly for the register() function.
	//It's good to be able to refer to the object you just created.
	int newestObject;
};


#endif //__ObjManH__