#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
	D3DXCreateSprite(
		g_pd3dDevice,
		&ppSprite
	);
	gametimetexture.Init();
	startcounttexture.Init();
	roadaroundfrequencytexture.Init();
}

void Sprite::Draw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//コロンを表示させる。
	for (int i = 1; i < 3; i++)
	{
		ppSprite->Draw(
			gametimetexture.pTexture_dot,
			NULL,
			&(D3DXVECTOR3(-37.0f, (float)(i) * -13.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//ドットを表示させる。
	ppSprite->Draw(
		gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-117.0f, -30.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	//タイムのテクスチャを表示させる。
	for (int i = 0; i < 4; i++)
	{
		ppSprite->Draw(
			gametimetexture.pTexture[gametimetexture.gametime[i]],
			NULL,
			&(D3DXVECTOR3((float)(i) * -40.0f, 0.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}

	//スタートのカウントのテクスチャを表示させる。
	if (startcounttexture.GetStartCountTimer() > 0)
	{
		ppSprite->Draw(
			startcounttexture.pTexture[startcounttexture.starttime],
			NULL,
			&(D3DXVECTOR3(-300.0f, -30.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//周回回数のテクスチャを表示させる。
	//if(roadaroundfrequencytexture)
	/*      1 / 2     */
	/*      1      */
	ppSprite->Draw(
		roadaroundfrequencytexture.pTexture[roadaroundfrequencytexture.GetAroundTexture()],
		NULL,
		&(D3DXVECTOR3(-660.0f, -0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      /       */
	ppSprite->Draw(
		roadaroundfrequencytexture.pTexture_Around,
		NULL,
		&(D3DXVECTOR3(-670.0f, -25.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      2      */
	ppSprite->Draw(
		roadaroundfrequencytexture.pTexture_No3,
		NULL,
		&(D3DXVECTOR3(-680.0f, -50.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	gametimetexture.Update();
	startcounttexture.Update();
	roadaroundfrequencytexture.Update();
	ppSprite->End();
}
