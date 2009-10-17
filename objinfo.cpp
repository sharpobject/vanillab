#include "objinfo.h"
#include "object.h"

ObjInfo::ObjInfo()
{
	sprite=NO_SPRITE;
	myclass=SPECIAL_OBJECT;
}
ObjInfo::ObjInfo(const Object& a)
{
	sprite=a.sprite;
	myclass=a.myclass;
}
ObjInfo::ObjInfo(const ObjInfo& a)
{
	sprite=a.sprite;
	myclass=a.myclass;
}
ObjInfo::ObjInfo(SpriteName sn,ObjectClass oc)
{
	sprite=sn;
	myclass=oc;
}
ObjInfo& ObjInfo::operator=(const ObjInfo& a)
{
	sprite=a.sprite;
	myclass=a.myclass;
	return *this;
}
ObjInfo& ObjInfo::operator=(const Object& a)
{
	sprite=a.sprite;
	myclass=a.myclass;
	return *this;
}