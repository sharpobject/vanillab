#pragma comment( lib, "d3dx9.lib" )

#include "spriteman.h"

extern LPDIRECT3DDEVICE9 gDevice;

SpriteMan::SpriteMan()
{
	if(FAILED(D3DXCreateSprite(gDevice,&m_sprite)))
		MessageBox(0, "D3DXCreateSprite() - FAILED", 0, 0);
	for(int i=0;i<N_SPRITES;i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(gDevice,gSpriteFiles[i],&(m_textures[i]))))
			MessageBox(0, "D3DXCreateTextureFromFile() - FAILED", 0, 0);
		D3DSURFACE_DESC surfaceDesc;
		m_textures[i]->GetLevelDesc(0, &surfaceDesc);
		m_centers[i]=D3DXVECTOR2(surfaceDesc.Width/2.0f,surfaceDesc.Height/2.0f);
	}
}

SpriteMan::~SpriteMan()
{
	m_sprite->Release();
	for(int i=0;i<N_SPRITES;i++)
	{
		m_textures[i]->Release();
	}
}

void SpriteMan::begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void SpriteMan::end()
{
	m_sprite->End();
}

void SpriteMan::draw(SpriteName spritename, float x, float y, float xscale, float yscale, float rotation, BOOL fromCenter)
{
	D3DXVECTOR2 trans=D3DXVECTOR2(x,y);
	D3DXVECTOR2 center=D3DXVECTOR2(xscale*m_centers[spritename].x,yscale*m_centers[spritename].y);
	if(fromCenter)
		trans-=center;
	D3DXVECTOR2 scaling=D3DXVECTOR2(xscale,yscale);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&center,rotation,&trans);
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(m_textures[spritename],NULL,NULL,NULL,0xFFFFFFFF);
}