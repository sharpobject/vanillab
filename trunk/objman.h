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
	void run(unsigned char*);
	void draw();
	void add(Object o);
	void makedude();
	~ObjMan();
	int size();
private:
	list<Object> m_objects;
	Object player;
};


#endif //__ObjManH__