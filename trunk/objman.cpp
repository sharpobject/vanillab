#include "objman.h"
#include "util.h"
#include <dinput.h>

using namespace std;

ObjMan::ObjMan():player(512,700,FACING_UP,0.0,SPR_PLAYER)
{
}

void ObjMan::run(unsigned char* input)
{
	for(list<Object>::iterator element=m_objects.begin(); element!=m_objects.end();) 
	{
		(*element).run();
		if((*element).isDead())
			element=m_objects.erase(element);
		else
			++element;
	}
	float pdx=0,pdy=0,pdirection=0,pspeed=0;
	if(input[DIK_UP])
		pdy-=1;
	if(input[DIK_DOWN])
		pdy+=1;
	if(input[DIK_LEFT])
		pdx-=1;
	if(input[DIK_RIGHT])
		pdx+=1;
	getPolar(pdx,pdy,pspeed,pdirection);
	pspeed=min(1.0,pspeed);
	pspeed*=4;
	if(input[DIK_LSHIFT])
		pspeed*=.5f;
	player.speed=pspeed;
	if(pspeed!=0.0f)
		player.direction=pdirection;
	player.run();
}

void ObjMan::draw()
{
	for(list<Object>::iterator element=m_objects.begin(); element!=m_objects.end(); ++element) 
		(*element).draw();
	player.draw();
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

int ObjMan::size()
{
	return m_objects.size();
}