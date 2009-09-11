#ifndef __SpriteManH__
#define __SpriteManH__

#include "setup.h"
#include "sprites.h"
#include <string>

using namespace std;

class SpriteMan
{
public:
	SpriteMan();
	void begin();
	void draw(SpriteName spritename, float x, float y, float xscale, float yscale,
		float rotation,D3DCOLOR color=0xffffffff, BOOL fromCenter=TRUE);
	void end();
	void drawFPS(string s);
	~SpriteMan();
private:
	LPD3DXSPRITE m_sprite;
	LPD3DXFONT m_font;
	LPDIRECT3DTEXTURE9 m_textures[N_SPRITES];
	D3DXVECTOR2 m_centers[N_SPRITES];
	RECT m_textrect;
};


#endif //__SpriteManH__