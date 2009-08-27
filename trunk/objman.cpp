#include "objman.h"
#include "util.h"

using namespace std;

ObjMan::ObjMan()
{

}

void ObjMan::run()
{
	for(list<Object>::iterator element=m_objects.begin(); element!=m_objects.end();) 
	{
		(*element).run();
		if((*element).isDead())
			element=m_objects.erase(element);
		else
			++element;
	}
}

void ObjMan::draw()
{
	for(list<Object>::iterator element=m_objects.begin(); element!=m_objects.end(); ++element) 
		(*element).draw();
}

void ObjMan::add(Object o)
{
	m_objects.push_back(o);
}

void ObjMan::makedude()
{
	Object o(1024.0f/2.0f,768.0f/2.0f,FACING_UP,0.0f,SPR_ARROW);
	add(o);
}