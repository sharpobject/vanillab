#ifndef __ObjectH__
#define __ObjectH__

#include "util.h"
#include "setup.h"
#include "sprites.h"
#include "objinfo.h"

class Object
{
public:
	Object();
	Object(float x,float y, float direction, float speed, SpriteName sprite,ObjectClass myclass);
	Object(const Object &orig);
	void run();
	void draw();
	Object& operator=(const Object &);
	bool operator<(const Object &);
	bool isDead();
	~Object();
private:
	void move();
private:
	float x,y,direction,speed;
	SpriteName sprite;
	int health;
	int age;
	bool dead;

	ObjectClass myclass;

	int id;
	
	//Variables for compatibility with ported BulletML code and similar.
	//These support accelerate, changespeed, and changedirection tags.
	float yAccel,xAccel,accel,rotation;
	int yAccelTurns,xAccelTurns,accelTurns,rotationTurns;
	int waitFrames;

	//Each object is (usually) its own node in an array-backed linked list.
	//I was stoned or something.  Don't ask.
	//Anyway, these are "pointers" to the adjacent objects.
	//-1 means null.
	int prev,next;

	//An ObjInfo representing the bullets fired by this object.
	ObjInfo childinfo;
public:
	friend class ObjMan;
	friend class ObjInfo;
};


#endif //__ObjectH__