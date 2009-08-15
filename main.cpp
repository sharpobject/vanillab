#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "Winmm.lib" )

#include "setup.h"
#include "sprites.h"

IDirect3DDevice9* gDevice = 0;
int gWidth  = 1024;
int gHeight = 768;

bool Display(int timeDelta)
{
	if( gDevice )
	{
		gDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff3E6B2E, 1.0f, 0);
		gDevice->BeginScene();
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
		MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	EnterMsgLoop();
	gDevice->Release();
	return 0;
}