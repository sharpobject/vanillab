#ifndef __ObjInfoH__
#define __ObjInfoH__

#include "util.h"
#include "setup.h"
#include "sprites.h"
#include "object.h"

class ObjInfo
{
public:
	ObjInfo();
	ObjInfo(const Object&);
	ObjInfo(const ObjInfo&);
	ObjInfo& operator=(const ObjInfo&);
	~ObjInfo();
public:
	SpriteName sprite;
	ObjectClass myclass;
};


#endif //__ObjInfoH__