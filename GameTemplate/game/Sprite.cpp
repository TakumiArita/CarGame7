#include "stdafx.h"
#include "Sprite.h"
#include "SceneManager.h"

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
	scenemanager->gametimetexture.Init();
	scenemanager->startcounttexture.Init();
	scenemanager->roadaroundfrequencytexture.Init();
}

void Sprite::Draw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//�X�^�[�g�̃J�E���g�̃e�N�X�`����\��������B
	if (scenemanager->startcounttexture.GetStartCountTimer() > 0)
	{
		ppSprite->Draw(
			scenemanager->startcounttexture.pTexture[scenemanager->startcounttexture.starttime],
			NULL,
			&(D3DXVECTOR3(-300.0f, -30.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//����񐔂̃e�N�X�`����\��������B
	//if(roadaroundfrequencytexture)
	/*      1 / 2     */
	/*      1      */
	ppSprite->Draw(
		scenemanager->roadaroundfrequencytexture.pTexture[scenemanager->roadaroundfrequencytexture.GetAroundTexture()],
		NULL,
		&(D3DXVECTOR3(-660.0f, -0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      /       */
	ppSprite->Draw(
		scenemanager->roadaroundfrequencytexture.pTexture_Around,
		NULL,
		&(D3DXVECTOR3(-670.0f, -25.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      2      */
	ppSprite->Draw(
		scenemanager->roadaroundfrequencytexture.pTexture_No3,
		NULL,
		&(D3DXVECTOR3(-680.0f, -50.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);


	//�R������\��������B
	for (int i = 1; i < 3; i++)
	{
		ppSprite->Draw(
			scenemanager->gametimetexture.pTexture_dot,
			NULL,
			&(D3DXVECTOR3(-157.0f, (float)(i) * -13.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//�h�b�g��\��������B
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-237.0f, -30.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//�^�C���̃e�N�X�`����\��������B
	for (int i = 0; i < 4; i++)
	{
		ppSprite->Draw(
			scenemanager->gametimetexture.pTexture[scenemanager->gametimetexture.gametime[i]],
			NULL,
			&(D3DXVECTOR3((float)(i + 3) * -40.0f, 0.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//�^�C���̕\���B
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_time,
		NULL,
		&(D3DXVECTOR3(0.0f, 5.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	scenemanager->gametimetexture.Update();
	scenemanager->startcounttexture.Update();
	scenemanager->roadaroundfrequencytexture.Update();
	ppSprite->End();
}


void Sprite::SaveGameTimeDraw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//�u�ő����ԁv��\��������B
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_newRecord,
		NULL,
		&(D3DXVECTOR3(0.0f, -50.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//�R������\��������B
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-237.0f,-60.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-237.0f,-80.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	//�h�b�g��\��������B
	ppSprite->Draw(
		scenemanager->gametimetexture.pTexture_dot,
		NULL,
		&(D3DXVECTOR3(-317.0f, -80.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//�^�C���̃e�N�X�`����\��������B
	for (int i = 0; i < 4; i++)
	{
		ppSprite->Draw(
			scenemanager->gametimetexture.pTexture[scenemanager->gametimetexture.gametimeSave[i]],
			NULL,
			&(D3DXVECTOR3((float)(i + 5) * -40.0f, -50.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	scenemanager->gametimetexture.SaveUpdate();
	ppSprite->End();
}

