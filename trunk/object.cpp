#include "object.h"
#include "util.h"
#include "spriteman.h"
#include "objman.h"

extern SpriteMan *gSpriteMan;
extern ObjMan *gObjMan;

Object::Object(float px,float py, float pdirection, float pspeed, SpriteName psprite)
{
	x=px;
	y=py;
	direction=pdirection;
	speed=pspeed;
	sprite=psprite;
	age=0;
	dead=false;
}

Object::Object(const Object &orig)
{
	x=orig.x;
	y=orig.y;
	direction=orig.direction;
	speed=orig.speed;
	sprite=orig.sprite;
	age=orig.age;
	dead=orig.dead;
}

Object& Object::operator=(const Object &rhs)
{
	x=rhs.x;
	y=rhs.y;
	direction=rhs.direction;
	speed=rhs.speed;
	sprite=rhs.sprite;
	age=rhs.age;
	dead=rhs.dead;
	return *this;
}

bool Object::operator<(const Object & rhs)
{
	return age>rhs.age;
}

void Object::run()
{
	switch(sprite)
	{
		case SPR_ARROW:
			direction+=DEGREE;
			if(age%6==0)
			{
				Object newguy(*this);
				newguy.age=0;
				newguy.speed=4.0f;
				newguy.sprite=SPR_MED_CIR_BULLET;
				gObjMan->add(newguy);
				int npaths=16;
				for(int i=1;i<npaths;i++)
				{
					newguy.direction+=FULL_CIRCLE/npaths;
					gObjMan->add(newguy);
				}
			}
			break;
	//	case SPR_MED_CIR_BULLET:
	//		if(age>200)
	//			dead=true;
	//		break;
	}
	move();
	age++;
}

void Object::move()
{
	float dx,dy;
	getCartesian(dx,dy,speed,direction);
	x+=dx;
	y+=dy;
}

void Object::draw()
{
	if(sprite==SPR_ARROW)
		gSpriteMan->draw(sprite,x,y,70/TEXTURE_SZ,70/TEXTURE_SZ,-direction+PI/2);
	else
		gSpriteMan->draw(sprite,x,y,25/TEXTURE_SZ,25/TEXTURE_SZ,-direction+PI/2);
}

bool Object::isDead()
{
	return dead;
}

Object::~Object()
{

}