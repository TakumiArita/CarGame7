#include "stdafx.h"
#include "TitleTexture.h"


TitleTexture::TitleTexture()
{
}

TitleTexture::~TitleTexture()
{
	if (ss != NULL)
	{
		delete ss;

		ss->Update();
	}
	//delete ss;
}

void TitleTexture::Init()
{
	D3DXCreateTextureFromFileEx(
		//Direct3Dデバイス
		g_pd3dDevice,
		"Assets/modelData/Title2.png",
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
	ss = new CSoundSource;
}

void TitleTexture::Update()
{

}

void TitleTexture::Draw()
{

}

void TitleTexture::TitleSound()
{
	if (soundtime <= 0)
	{
		ss = new CSoundSource;
		ss->Init("Assets/sound/se_maoudamashii_effect02.wav");
		ss->SetVolume(0.1f);
		ss->Play(false);
	}
	soundtime += 1;

	if (soundtime >= 70)
	{
		soundtime = 0;
	}
	if (ss != NULL)
	{
		ss->Update();
	}
}
