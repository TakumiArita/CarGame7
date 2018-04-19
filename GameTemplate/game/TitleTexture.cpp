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
	}
	ss = NULL;

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

}

void TitleTexture::Update()
{
	if (ss != NULL)
	{
		ss->Update();
	}
}

void TitleTexture::Draw()
{

}

void TitleTexture::TitleSound()
{
	if (ss == NULL)
	{
		ss = new CSoundSource;
		ss->Init("Assets/sound/opening-reggae.wav");
		ss->SetVolume(0.5f);
		ss->Play(true);
	}

}
void TitleTexture::TitleRelease()
{
	TitleTexture::~TitleTexture();
}