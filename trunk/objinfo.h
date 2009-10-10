#ifndef __ObjInfoH__
#define __ObjInfoH__

#include "util.h"
#include "setup.h"
#include "sprites.h"

class Object;

class ObjInfo
{
public:
	ObjInfo();
	ObjInfo(const Object&);
	ObjInfo(const ObjInfo&);
	ObjInfo(SpriteName,ObjectClass);
	ObjInfo& operator=(const ObjInfo&);
	ObjInfo& operator=(const Object&);
public:
	SpriteName sprite;
	ObjectClass myclass;
};


#endif //__ObjInfoH__