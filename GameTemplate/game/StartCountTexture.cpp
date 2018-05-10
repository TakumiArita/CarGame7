#include "stdafx.h"
#include "StartCountTexture.h"
#include "SceneManager.h"


StartCountTexture::StartCountTexture()
{
}

StartCountTexture::~StartCountTexture()
{
}

void StartCountTexture::Init()
{
	timetexture[0] = "Assets/modelData/S_1.png";
	timetexture[1] = "Assets/modelData/S_2.png";
	timetexture[2] = "Assets/modelData/S_3.png";
	for (int i = 0; i < 3; i++)
	{
		D3DXCreateTextureFromFileEx(
			g_pd3dDevice,
			timetexture[i],
			250,
			250,
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
		);
	}
	starttimer = 300;
}

void StartCountTexture::Update()
{


	if (scenemanager->GetTitleFlag() == true)
	{

		if (starttimer == 300)
		{
			starttime = 2;
		}
		if (starttimer == 200)
		{
			starttime = 1;
		}
		if (starttimer == 100)
		{
			starttime = 0;
		}
		if (starttimer != 0)
		{
			starttimer--;
		}
	}
	if (GetAsyncKeyState('O') || scenemanager->GetTitleFlag() != true)
	{
		starttimer = 300;
	}
}

void StartCountTexture::Draw()
{

}