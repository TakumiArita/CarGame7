#pragma once
#include "CSoundSource.h"
class TitleTexture
{
public:
	TitleTexture();
	~TitleTexture();

	void Init();
	void Update();
	void Draw();
	void TitleRelease();
	void TitleSound();
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture;
	//LPDIRECT3DTEXTURE9 pTexture;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;
private:
	CSoundSource* ss = NULL;     //�T�E���h
	int soundtime = 0;


};

