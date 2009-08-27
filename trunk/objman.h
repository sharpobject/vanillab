#ifndef __ObjManH__
#define __ObjManH__

#include "object.h"
#include <list>
#include <algorithm>

using namespace std;

class ObjMan
{
public:
	ObjMan();
	void run();
	void draw();
	void add(Object o);
	void makedude();
	~ObjMan();
private:
	list<Object> m_objects;
};


#endif //__ObjManH__