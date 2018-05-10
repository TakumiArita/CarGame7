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
	scenemanager->GetGameTimeTexture().Init();
	scenemanager->GetStartCountTexture().Init();
	scenemanager->GetRoadAroundFrequencyTexture().Init();
}

void Sprite::Draw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//スタートのカウントのテクスチャを表示させる。
	if (scenemanager->GetStartCountTexture().GetStartCountTimer() > 0)
	{
		ppSprite->Draw(
			scenemanager->GetStartCountTexture().SetpTexture(scenemanager->GetStartCountTexture().GetStarttime()),
			NULL,
			&(D3DXVECTOR3(-575.0f, -30.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//周回回数のテクスチャを表示させる。
	//if(roadaroundfrequencytexture)
	/*      1 / 2     */
	/*      1      */
	ppSprite->Draw(
		scenemanager->GetRoadAroundFrequencyTexture().SetpTexture(scenemanager->GetRoadAroundFrequencyTexture().GetAroundTexture()),
		NULL,
		&(D3DXVECTOR3(-660.0f * 1.95f, -0.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      /       */
	ppSprite->Draw(
		scenemanager->GetRoadAroundFrequencyTexture().GetpTexture_Around(),
		NULL,
		&(D3DXVECTOR3(-670.0f * 1.95f, -25.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	/*      2      */
	ppSprite->Draw(
		scenemanager->GetRoadAroundFrequencyTexture().GetpTexture_No3(),
		NULL,
		&(D3DXVECTOR3(-680.0f * 1.95f, -50.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);


	//コロンを表示させる。
	for (int i = 1; i < 3; i++)
	{
		ppSprite->Draw(
			scenemanager->GetGameTimeTexture().GetpTexture_dot(),
			NULL,
			&(D3DXVECTOR3(-157.0f, (float)(i) * -13.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//ドットを表示させる。
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_dot(),
		NULL,
		&(D3DXVECTOR3(-237.0f, -30.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//タイムのテクスチャを表示させる。
	for (int i = 0; i < 4; i++)
	{
		ppSprite->Draw(
			scenemanager->GetGameTimeTexture().SetpTexture(scenemanager->GetGameTimeTexture().SetGameTime(i)),
			NULL,
			&(D3DXVECTOR3((float)(i + 3) * -40.0f, 0.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	//タイムの表示。
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_time(),
		NULL,
		&(D3DXVECTOR3(0.0f, 5.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	scenemanager->GetGameTimeTexture().Update();
	scenemanager->GetStartCountTexture().Update();
	scenemanager->GetRoadAroundFrequencyTexture().Update();
	ppSprite->End();
}


void Sprite::SaveGameTimeDraw()
{
	ppSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//「最速時間」を表示させる。
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_newRecord(),
		NULL,
		&(D3DXVECTOR3(0.0f, -50.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//コロンを表示させる。
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_dot(),
		NULL,
		&(D3DXVECTOR3(-237.0f,-60.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_dot(),
		NULL,
		&(D3DXVECTOR3(-237.0f,-80.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);

	//ドットを表示させる。
	ppSprite->Draw(
		scenemanager->GetGameTimeTexture().GetpTexture_dot(),
		NULL,
		&(D3DXVECTOR3(-317.0f, -80.0f, 0.0f)),
		&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		(D3DCOLOR_ARGB(255, 255, 255, 255))
	);
	//タイムのテクスチャを表示させる。
	for (int i = 0; i < 4; i++)
	{
		ppSprite->Draw(
			scenemanager->GetGameTimeTexture().SetpTexture(scenemanager->GetGameTimeTexture().SetGameTimeSave(i)),
			NULL,
			&(D3DXVECTOR3((float)(i + 5) * -40.0f, -50.0f, 0.0f)),
			&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			(D3DCOLOR_ARGB(255, 255, 255, 255))
		);
	}
	scenemanager->GetGameTimeTexture().SaveUpdate();
	ppSprite->End();
}

