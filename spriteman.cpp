#pragma comment( lib, "d3dx9.lib" )

#include "spriteman.h"

extern LPDIRECT3DDEVICE9 gDevice;

SpriteMan::SpriteMan()
{
	if(FAILED(D3DXCreateSprite(gDevice,&m_sprite)))
		MessageBox(0, "D3DXCreateSprite() - FAILED", 0, 0);
	for(int i=NO_SPRITE+1;i<N_SPRITES;i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(gDevice,gSpriteFiles[i],&(m_textures[i]))))
			MessageBox(0, "D3DXCreateTextureFromFile() - FAILED", 0, 0);
		D3DSURFACE_DESC surfaceDesc;
		m_textures[i]->GetLevelDesc(0, &surfaceDesc);
		m_centers[i]=D3DXVECTOR2(surfaceDesc.Width/2.0f,surfaceDesc.Height/2.0f);
	}
	if(FAILED(D3DXCreateFont( gDevice, 12, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Lucida Console"), &m_font)))
		MessageBox(0,"D3DXCreateFont() - FAILED",0,0);
	m_textrect.bottom=768-4;
	m_textrect.top=4;
	m_textrect.left=4;
	m_textrect.right=1024-4;
}

SpriteMan::~SpriteMan()
{
	for(int i=NO_SPRITE+1;i<N_SPRITES;i++)
	{
		m_textures[i]->Release();
	}
	m_sprite->Release();
}

void SpriteMan::begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void SpriteMan::end()
{
	m_sprite->End();
}

void SpriteMan::draw(SpriteName spritename, float x, float y, float xscale, float yscale,
					 float rotation, D3DCOLOR color, BOOL fromCenter)
{
	D3DXVECTOR2 trans(x,y);
	D3DXVECTOR2 center(xscale*m_centers[spritename].x,yscale*m_centers[spritename].y);
	if(fromCenter)
		trans=trans - center;
	D3DXVECTOR2 scaling(xscale,yscale);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&center,rotation,&trans);
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(m_textures[spritename],NULL,NULL,NULL,color);
}

void SpriteMan::drawFPS(string s)
{
	D3DXMATRIX mat;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			mat.m[i][j]=0;
	for(int i=0;i<4;i++)
		mat.m[i][i]=1;
	m_sprite->SetTransform(&mat);
	++++m_textrect.bottom;
	++m_textrect.right;
	m_font->DrawText(m_sprite,s.c_str(),s.size(),&m_textrect,DT_RIGHT|DT_BOTTOM,0xff000000);
	----m_textrect.bottom;
	--m_textrect.right;
	m_font->DrawText(m_sprite,s.c_str(),s.size(),&m_textrect,DT_RIGHT|DT_BOTTOM,0xffffffff);
}