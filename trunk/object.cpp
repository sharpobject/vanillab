#include "object.h"
#include "util.h"
#include "spriteman.h"
#include "objman.h"

extern int gWidth;
extern int gHeight;
extern lua_State *gLua;
extern SpriteMan *gSpriteMan;
extern ObjMan *gObjMan;

Object::Object()
{
	x=0;
	y=0;
	direction=0;
	speed=0;
	sprite=NO_SPRITE;
	myclass=SPECIAL_OBJECT;
	age=0;
	dead=true;
	yAccel=xAccel=accel=rotation=0.0f;
	yAccelTurns=xAccelTurns=accelTurns=rotationTurns=0;
	waitFrames=0;
	id=-1;
	prev=next=-1;
	childinfo=ObjInfo(NO_SPRITE,SPECIAL_OBJECT);
}

Object::Object(float px,float py, float pdirection, float pspeed, SpriteName psprite, ObjectClass pclass)
{
	x=px;
	y=py;
	direction=pdirection;
	speed=pspeed;
	sprite=psprite;
	myclass=pclass;
	age=0;
	dead=false;
	yAccel=xAccel=accel=rotation=0.0f;
	yAccelTurns=xAccelTurns=accelTurns=rotationTurns=0;
	waitFrames=0;
	id=-1;
	prev=next=-1;
	childinfo=ObjInfo(NO_SPRITE,SPECIAL_OBJECT);
}

Object::Object(const Object &orig)
{
	x=orig.x;
	y=orig.y;
	direction=orig.direction;
	speed=orig.speed;
	sprite=orig.sprite;
	myclass=orig.myclass;
	age=orig.age;
	dead=orig.dead;
	yAccel=orig.yAccel;
	xAccel=orig.xAccel;
	accel=orig.accel;
	rotation=orig.rotation;
	yAccelTurns=orig.yAccelTurns;
	xAccelTurns=orig.xAccelTurns;
	accelTurns=orig.accelTurns;
	rotationTurns=orig.rotationTurns;
	waitFrames=orig.waitFrames;
	id=-1;
	prev=next=-1;
	childinfo=orig.childinfo;
}

Object& Object::operator=(const Object &rhs)
{
	x=rhs.x;
	y=rhs.y;
	direction=rhs.direction;
	speed=rhs.speed;
	sprite=rhs.sprite;
	myclass=rhs.myclass;
	age=rhs.age;
	dead=rhs.dead;
	yAccel=rhs.yAccel;
	xAccel=rhs.xAccel;
	accel=rhs.accel;
	rotation=rhs.rotation;
	yAccelTurns=rhs.yAccelTurns;
	xAccelTurns=rhs.xAccelTurns;
	accelTurns=rhs.accelTurns;
	rotationTurns=rhs.rotationTurns;
	waitFrames=rhs.waitFrames;
	id=-1;
	prev=next=-1;
	childinfo=rhs.childinfo;
	return *this;
}

bool Object::operator<(const Object & rhs)
{
	return age>rhs.age;
}

void Object::run()
{
	if(waitFrames)
	{
//		MessageBox(0, "waitFrames nonzero", 0, 0);
		waitFrames--;
	}
	if(waitFrames==0)
	{
//		MessageBox(0, "running", 0, 0);
		lua_pushstring(gLua, "run");
		lua_gettable(gLua, LUA_GLOBALSINDEX);
		lua_pcall(gLua, 0, 0, 0);
	}
/*	switch(sprite)
	{
		case SPR_ARROW:
			direction+=DEGREE;
			if(age%9==0)
			{
				Object newguy(*this);
				newguy.age=0;
				newguy.speed=8.0f/3.0f;
				newguy.sprite=SPR_MED_CIR_BULLET;
				newguy.myclass=ENEMY_BULLET;
			//	gObjMan->add(newguy);
				int npaths=100;
				for(int i=0;i<npaths;i++)
				{
					newguy.direction=FULL_CIRCLE*i/npaths;//+direction;
					gObjMan->add(newguy);
				}
			}
			break;
		case SPR_MED_CIR_BULLET:
			if(age>242)
				dead=true;
			break;
	}*/
	move();
	age++;
}

void Object::move()
{
	if(accelTurns)
	{
		speed+=accel;
		accelTurns--;
	}
	float dx,dy;
	getCartesian(dx,dy,SPEED_SCALE*speed,direction);
	x+=dx;
	y+=dy;
	if(x<-100||y<-100||x>gWidth+100||y>gHeight+100)
		dead=true;
}

void Object::draw()
{
	if(x<-100||y<-100||x>gWidth+100||y>gHeight+100)
		return;
	if(sprite>NO_SPRITE)
		gSpriteMan->draw(sprite,x,y,25/TEXTURE_SZ,25/TEXTURE_SZ,-direction+PI/2);
}

bool Object::isDead()
{
	return dead;
}

Object::~Object()
{

}