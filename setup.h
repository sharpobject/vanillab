#ifndef __SetupH__
#define __SetupH__

#include <d3dx9.h>
#include <string>

bool Setup(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device);

int EnterMsgLoop();

bool Display(int timeDelta);

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT msg, 
	WPARAM wParam,
	LPARAM lParam);

#endif // __SetupH__