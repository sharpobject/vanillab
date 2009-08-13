#include "setup.h"
#include <windowsx.h>

extern int gHeight;
extern int gWidth;

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
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
 
	D3DPRESENT_PARAMETERS d3dpp;
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
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;

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
	return true;
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
		Display(timeDelta);
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