#include "stdafx.h"
#include "GoalTexture.h"


GoalTexture::GoalTexture()
{
}


GoalTexture::~GoalTexture()
{
}

void GoalTexture::Init()
{
	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/Goal.png",
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
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

void GoalTexture::Update()
{

}

void GoalTexture::Draw()
{

}