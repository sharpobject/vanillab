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
	void add(Object &o);
	void makedude();
	~ObjMan();
	int size();
private:
	void run(int);
	void draw(int);


	//This is an array in which linked lists will exist.
	Object objects[MAX_N_OBJECTS];
	//These are the available entries in the above array.  As a stack.
	int freeIndices[MAX_N_OBJECTS];
	int nFreeIndices;
	//These are pointers to the heads of awesome linked lists of awesome.
	int heads[N_OBJECT_CLASSES],tails[N_OBJECT_CLASSES];
	
	
	//The active object.  Lua functions that change object variables will act on it.
	//Depending on what I end up doing it may belong in Object instead.
	int activeObject;
};


#endif //__ObjManH__