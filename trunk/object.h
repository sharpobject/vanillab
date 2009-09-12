#ifndef __ObjectH__
#define __ObjectH__

#include "setup.h"
#include "sprites.h"

class Object
{
public:
	Object(float x,float y, float direction, float speed, SpriteName sprite);
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
	int age;
	bool dead;
public:
	friend class ObjMan;
};


#endif //__ObjectH__