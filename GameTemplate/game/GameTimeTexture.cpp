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

	for (auto i = 0; i < 10; i++)
	{
		D3DXCreateTextureFromFileEx(
			//Direct3Dデバイス
			g_pd3dDevice,
			timetexture[i],
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
			&pTexture[i]
			//&pTexture
		);
	}

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

	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/Time.png",
		CFRAME_BUFFER_WIDTH + 100,
		CFRAME_BUFFER_HEIGHT + 50,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&imgInfo,
		NULL,
		&pTexture_time
	);

	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/NewRecord.png",
		CFRAME_BUFFER_WIDTH + 200,
		CFRAME_BUFFER_HEIGHT + 50,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&imgInfo,
		NULL,
		&pTexture_newRecord
	);
	gametimer = 0;


	fp = fopen("Assets/saveData/SaveData.txt", "r");  //読み込み専用
	fgets(str, 10, fp);
	for (auto i = 0; i < 10; i++)
	{
		if (str[i] != NULL)
		{
			saveGametimer += str[i] - '0';
			saveGametimer *= 10;
		}
	}
	saveGametimer /= 10;
	fclose(fp);

}

void GameTimeTexture::Update()
{
	//スタートカウントが0になったら
	if (scenemanager->GetStartCountTexture().GetStartCountTimer() == 0)
	{
		if (firstTitleFlag == false)
		{
			firstTitleFlag = true;
			if (saveGametimer == 0)
			{
				saveGametimer = INT_MAX;
			}
		}
		//////タイマー秒数更新処理。/////
		////    1    2    3    4    ////
		////////////////////////////////
		//4
		gametime[3] = gametimer / 10;
		gametime[3] = gametime[3] % 10;   //いつ0に戻すか。
		//3
		gametime[2] = gametimer / 100;
		gametime[2] = gametime[2] % 10;
		//2
		gametime[1] = gametimer / 1000;
		gametime[1] = gametime[1] % 6;
		//1
		//gametime[0] = gametimer / 10000;
		//gametime[0] = gametime[0] % 10;

		gametime[0] = gametimer / 6000;
		gametime[0] = gametime[0] % 10;

		//ゴールするまで。
		if (scenemanager->GetPlayer().GetCirclingTimes() <= 2)
		{
			gametimer++;
		}
		else if (gametimer < saveGametimer)
		{
			if (gametimer != 0)
			{
				saveGametimer = gametimer;

				////fopen("Assets/saveData/SaveData.txt", "r");      //読み取り専用

				fp = fopen("Assets/saveData/SaveData.txt", "w");  //書き込み専用
				fprintf(fp, "%d", saveGametimer);            //書き込み
				fclose(fp);                                  //ファイルを閉じる。
			}
		}
	}
	//初期値に戻す。
	if (GetAsyncKeyState('O') || scenemanager->GetTitleFlag() != true)
	{
		gametimer = 0;
		gametime[3] = 0;
		gametime[2] = 0;
		gametime[1] = 0;
		gametime[0] = 0;
	}
}

void GameTimeTexture::SaveUpdate()
{

	//4
	gametimeSave[3] = saveGametimer / 10;
	gametimeSave[3] = gametimeSave[3] % 10;   //いつ0に戻すか。
	//3
	gametimeSave[2] = saveGametimer / 100;
	gametimeSave[2] = gametimeSave[2] % 10;
	//2
	gametimeSave[1] = saveGametimer / 1000;
	gametimeSave[1] = gametimeSave[1] % 6;
	//1
	//gametime[0] = saveGametimer / 10000;
	//gametime[0] = gametime[0] % 10;

	gametimeSave[0] = saveGametimer / 6000;
	gametimeSave[0] = gametimeSave[0] % 10;

}

void GameTimeTexture::Draw()
{

}
