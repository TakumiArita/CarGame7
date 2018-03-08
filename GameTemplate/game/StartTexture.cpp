#include "stdafx.h"
#include "StartTexture.h"
#include "SceneManager.h"


StartTexture::StartTexture()
{
}

StartTexture::~StartTexture()
{
}

void StartTexture::Init()
{
	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/Start.png",
		FRAME_BUFFER_WIDTH + 100,
		FRAME_BUFFER_HEIGHT + 100,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&imgInfo,
		NULL,
		&pTexture
	);
}

void StartTexture::Update()
{

}

void StartTexture::Draw()
{

}