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
}

void Sprite::Draw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//�R������\��������B
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
	//�h�b�g��\��������B
	ppSprite->Draw(
		gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-117.0f, -30.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	//�^�C���̃e�N�X�`����\��������B
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

	//�X�^�[�g�̃J�E���g�̃e�N�X�`����\��������B
	if (startcounttexture.GetStartCountTimer() > 0)
	{
		ppSprite->Draw(
			startcounttexture.pTexture[startcounttexture.starttime],
			NULL,
			&(D3DXVECTOR3(-300.0f, -50.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}


	gametimetexture.Update();
	startcounttexture.Update();
	ppSprite->End();
}