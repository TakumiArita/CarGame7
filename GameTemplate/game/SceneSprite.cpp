#include "stdafx.h"
#include "SceneSprite.h"


SceneSprite::SceneSprite()
{
}

SceneSprite::~SceneSprite()
{
}

void SceneSprite::Init()
{
	D3DXCreateSprite(
		g_pd3dDevice,
		&ppSprite
	);
	titletexture.Init();
	goaltexture.Init();
	starttexture.Init();
}
void SceneSprite::TitleDraw()
{
	ppSprite->Begin(0);
	ppSprite->Draw(
		titletexture.pTexture,
		NULL,
		&(D3DXVECTOR3(10.0f, 0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->End();
}
void SceneSprite::GoalDraw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);
	ppSprite->Draw(
		goaltexture.pTexture,
		NULL,
		&(D3DXVECTOR3(10.0f, 0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->End();
}
void SceneSprite::StartDraw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);
	ppSprite->Draw(
		starttexture.pTexture,
		NULL,
		&(D3DXVECTOR3(10.0f, 0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->End();

}