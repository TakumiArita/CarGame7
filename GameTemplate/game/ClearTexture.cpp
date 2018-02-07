#include "stdafx.h"
#include "ClearTexture.h"


ClearTexture::ClearTexture()
{
}

ClearTexture::~ClearTexture()
{
}

void ClearTexture::Init()
{
	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/Goal1.png",
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

void ClearTexture::Update()
{

}

void ClearTexture::Draw()
{

}