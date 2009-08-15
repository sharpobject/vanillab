#ifndef __SpriteManH__
#define __SpriteManH__

#include "setup.h"
#include "sprites.h"

class SpriteMan
{
public:
	SpriteMan();
	void begin();
	void draw(SpriteName spritename, float x, float y, float xscale, float yscale, float rotation, BOOL fromCenter=TRUE);
	void end();
	~SpriteMan();
private:
	LPD3DXSPRITE m_sprite;
	LPDIRECT3DTEXTURE9 m_textures[N_SPRITES];
	D3DXVECTOR2 m_centers[N_SPRITES];
};


#endif //__SpriteManH__