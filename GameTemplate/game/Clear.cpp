#include "stdafx.h"
#include "Clear.h"


Clear::Clear()
{
}

Clear::~Clear()
{
}

void Clear::Init()
{
	D3DXCreateSprite(
		g_pd3dDevice,
		&ppSprite
	);
	cleartexture.Init();
}

void Clear::Draw()
{
	ppSprite->Begin(0);
	ppSprite->Draw(
		cleartexture.pTexture,
		NULL,
		&(D3DXVECTOR3(10.0f, 0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->End();
}