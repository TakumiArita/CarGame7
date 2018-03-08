#include "stdafx.h"
#include "GameTimeTexture.h"
#include "Scenemanager.h"

GameTimeTexture::GameTimeTexture()
{
}

GameTimeTexture::~GameTimeTexture()
{
}

void GameTimeTexture::Init()
{
	timetexture[0] = "Assets/modelData/No_0.png";
	timetexture[1] = "Assets/modelData/No_1.png";
	timetexture[2] = "Assets/modelData/No_2.png";
	timetexture[3] = "Assets/modelData/No_3.png";
	timetexture[4] = "Assets/modelData/No_4.png";
	timetexture[5] = "Assets/modelData/No_5.png";
	timetexture[6] = "Assets/modelData/No_6.png";
	timetexture[7] = "Assets/modelData/No_7.png";
	timetexture[8] = "Assets/modelData/No_8.png";
	timetexture[9] = "Assets/modelData/No_9.png";

	for (gametimer = 0; gametimer < 10; gametimer++)
	{
		D3DXCreateTextureFromFileEx(
			//Direct3Dデバイス
			g_pd3dDevice,
			timetexture[gametimer],
			CFRAME_BUFFER_WIDTH + 40,
			CFRAME_BUFFER_HEIGHT + 40,
			0,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&imgInfo,
			NULL,
			&pTexture[gametimer]
			//&pTexture
		);
	}
	gametimer = 0;

	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/dot.png",
		CFRAME_BUFFER_WIDTH  + 5,
		CFRAME_BUFFER_HEIGHT + 5,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&imgInfo,
		NULL,
		&pTexture_dot
	);
}

void GameTimeTexture::Update()
{
	//スタートカウントが0になったら
	if (scenemanager->startcounttexture.GetStartCountTimer() == 0)
	{
		//////タイマー秒数更新処理。/////
		////    1    2    3    4    ////
		////////////////////////////////
		//4
		gametime[3] = gametimer / 10;
		gametime[3] = gametime[3] % 10;
		//3
		gametime[2] = gametimer / 100;
		gametime[2] = gametime[2] % 10;
		//2
		gametime[1] = gametimer / 1000;
		gametime[1] = gametime[1] % 6;
		//1
		//gametime[0] = gametimer / 10000;
		//gametime[0] = gametime[0] % 10;

		gametime[0] = gametimer / 10000;
		gametime[0] = gametime[0] % 10;

		//ゴールするまで。
		if (scenemanager->player.GetCirclingTimes() <= 2)
		{
			gametimer++;
		}
	}
	//初期値に戻す。
	if (GetAsyncKeyState('O'))
	{
		gametimer = 0;
		gametime[3] = 0;
		gametime[2] = 0;
		gametime[1] = 0;
		gametime[0] = 0;
	}
}
void GameTimeTexture::Draw()
{

}
