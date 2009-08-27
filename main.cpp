#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "Winmm.lib" )

#include "util.h"
#include "setup.h"
#include "sprites.h"
#include "spriteman.h"
#include "objman.h"

using namespace std;

LPDIRECT3DDEVICE9 gDevice = 0;
int gWidth  = 1024;
int gHeight = 768;
SpriteMan *gSpriteMan = 0;
ObjMan *gObjMan = 0;

bool Display(int timeDelta)
{
	if( gDevice )
	{
		gObjMan->run();
		gDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff3E6B2E, 1.0f, 0);
		gDevice->BeginScene();
		gSpriteMan->begin();
		gObjMan->draw();
		//for(int j=-32;j<50;j++)
		//	for(int i=0;i<100;i++)
		//	{
		//		gSpriteMan->draw(SPR_MED_CIR_BULLET,25*j+10*i,10*i,25/TEXTURE_SZ,25/TEXTURE_SZ,0);
		//	}			
		//for(int i=0;i<timeDelta;i++)
		//	gSpriteMan->draw(SPR_ARROW,40+25*i,400,25/TEXTURE_SZ,25/TEXTURE_SZ,PI*i/4);
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
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			DestroyWindow(hwnd);
		break;
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