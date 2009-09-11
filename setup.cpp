#pragma once

#include <windowsx.h>
#include "util.h"
#include <dinput.h>
#include "setup.h"
#include "spriteman.h"
#include "objman.h"

extern int gHeight;
extern int gWidth;
extern SpriteMan *gSpriteMan;
extern ObjMan *gObjMan;
extern LPDIRECTINPUT8 gDI;
extern LPDIRECTINPUTDEVICE8 gKeyboard;
extern LPDIRECT3DDEVICE9 gDevice;
D3DPRESENT_PARAMETERS d3dpp;

bool Setup(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	if( !RegisterClass(&wc) ) 
	{
		MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	HWND hwnd = 0;
	hwnd = CreateWindow("Direct3D9App", "vanillab", 
		WS_EX_TOPMOST,
		20, 20, width, height,
		0, 0, hInstance, 0); 

	if( !hwnd )
	{
		MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//Resize the window so the interior is the right size.
	RECT window_rect = {0,0,gWidth,gHeight};
	AdjustWindowRectEx(&window_rect,
		GetWindowStyle(hwnd),
		GetMenu(hwnd)!=NULL,
		GetWindowExStyle(hwnd));
	MoveWindow(hwnd,20,20,
		window_rect.right-window_rect.left,
		window_rect.bottom-window_rect.top,
		FALSE);

	HRESULT hr = 0;

	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if( !d3d9 )
	{
		MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
//	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
//	else
//		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
 
	d3dpp.BackBufferWidth            = width;
	d3dpp.BackBufferHeight           = height;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = windowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		deviceType,
		hwnd,
		vp,
	    &d3dpp,
	    device);
	if( FAILED(hr) )
	{
		d3d9->Release();
		MessageBox(0, "CreateDevice() - FAILED", 0, 0);
		return false;
	}
	d3d9->Release();

	gSpriteMan = new SpriteMan();
	gObjMan = new ObjMan();
	gObjMan -> makedude();
	if(FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8A,(LPVOID*)(&gDI),NULL)))
	{
		MessageBox(0, "DirectInput8Create() - FAILED", 0, 0);
	}
	gDI->CreateDevice(GUID_SysKeyboard, &gKeyboard, NULL);
	gKeyboard->SetDataFormat(&c_dfDIKeyboard);
	gKeyboard->Acquire();
	return true;
}

bool resetDevice()
{
	if(gSpriteMan)
	{
		delete gSpriteMan;
		gSpriteMan = 0;
	}
	if(SUCCEEDED(gDevice->Reset(&d3dpp)))
	{
//		MessageBox(0, "Oh dear sir.", 0, 0);
		gSpriteMan=new SpriteMan();
		return true;
	}
	else
	{
//		MessageBox(0, "Oh dear madam.", 0, 0);
		return false;
	}
}

int EnterMsgLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	int lastTime = timeGetTime(); 
	for(;;)
	{
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)
				return msg.wParam;
		}
		int currTime  = timeGetTime();
		int timeDelta = currTime - lastTime;
		Display(currTime,lastTime);
		lastTime = currTime;
    }
}

D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}