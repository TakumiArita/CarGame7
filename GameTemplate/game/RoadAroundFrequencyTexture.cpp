#include "stdafx.h"
#include "RoadAroundFrequencyTexture.h"
#include "SceneManager.h"
#include "Scenemanager.h"


RoadAroundFrequencyTexture::RoadAroundFrequencyTexture()
{
}


RoadAroundFrequencyTexture::~RoadAroundFrequencyTexture()
{
}

void RoadAroundFrequencyTexture::Init()
{
	Roadaroundtexture[0] = "Assets/modelData/No_1.png";
	Roadaroundtexture[1] = "Assets/modelData/No_2.png";
	Roadaroundtexture[2] = "Assets/modelData/No_3.png";

	for (aroundtexture = 0; aroundtexture < 3; aroundtexture++)
	{
		D3DXCreateTextureFromFileEx(
			//Direct3Dデバイス
			g_pd3dDevice,
			Roadaroundtexture[aroundtexture],
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
			&pTexture[aroundtexture]
		);
	}
	aroundtexture = 0;

	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/No_3.png",
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
		&pTexture_No3
	);

	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/No_Around.png",
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
		&pTexture_Around
	);
}

void RoadAroundFrequencyTexture::Update()
{
	if (aroundtexture < 3)
	{
		aroundtexture = scenemanager->player.GetCirclingTimes();
	}
	if (GetAsyncKeyState('O') || scenemanager->GetTitleFlag() != true)
	{
		aroundtexture = 0;
	}
}
void RoadAroundFrequencyTexture::Draw()
{

}
