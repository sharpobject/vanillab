#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "Winmm.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )

#include "util.h"
#include <sstream>
#include <dinput.h>
#include <windows.h>
#include <winbase.h>
#include "setup.h"
#include "sprites.h"
#include "spriteman.h"
#include "objman.h"

using namespace std;

lua_State *gLua = 0;
LPDIRECT3DDEVICE9 gDevice = 0;
LPDIRECTINPUT8 gDI = 0;
LPDIRECTINPUTDEVICE8 gKeyboard = 0;
int gWidth  = 1024;
int gHeight = 768;
SpriteMan *gSpriteMan = 0;
ObjMan *gObjMan = 0;
int gFrameTimes[FPS_UPDATE_INTERVAL];
int gFTidx;
float gFPS=0.0;
int gnObjects=0;

bool Display(int time,int prevtime)
{
	if( gDevice )
	{
		if(FAILED(gDevice->TestCooperativeLevel()))
		{
//			MessageBox(0,"One day you won't have your naughty bits any more.",0,0);
			while(!resetDevice())
				Sleep(17);
		}
		//POLL DA KEYBOARD YO
		gKeyboard->Poll();
		unsigned char keys[256];
		gKeyboard->GetDeviceState(256,&keys);
		//Calculate framerate and number of objects for display.
		gFrameTimes[gFTidx]=time-prevtime;
		gFTidx=(gFTidx+1)%FPS_UPDATE_INTERVAL;
		if(gFTidx==0)
		{
			float sum=0;
			for(int i=0;i<FPS_UPDATE_INTERVAL;i++)
				sum+=gFrameTimes[i];
			gFPS=FPS_UPDATE_INTERVAL*1000/sum;
			gFPS=((int)(gFPS*10+.5))*.1f;
			gnObjects=gObjMan->size();
		}		
		gObjMan->run((unsigned char*)&keys);
		//gnObjects=gObjMan->size();
		luaL_dostring(gLua,"myvalue=myvalue+1;");
		lua_pushstring(gLua, "myvalue");
		lua_gettable(gLua, LUA_GLOBALSINDEX);
		stringstream sout;
//		for(int i=0;i<min(time-prevtime-17,50);i++)
//			sout<<"DONGS\n";
		sout<<lua_tostring(gLua,-1)<<"  frames"<<"\n";
		sout<<gFPS<<"     FPS\n"<<gnObjects<<" Objects";
		lua_pop(gLua,1);
		gDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff3E6B2E, 1.0f, 0);
		gDevice->BeginScene();
		gSpriteMan->begin();
		gObjMan->draw();
		gSpriteMan->drawFPS(sout.str());
		gSpriteMan->end();
		gDevice->EndScene();
		gDevice->Present(0, 0, 0, 0);
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
//	case WM_KEYDOWN:
//		if( wParam == VK_ESCAPE )
//			DestroyWindow(hwnd);
//		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!Setup(hinstance,
		gWidth, gHeight, true, D3DDEVTYPE_HAL, &gDevice))
	{
		MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
	EnterMsgLoop();
	gDevice->Release();
	return 0;
}