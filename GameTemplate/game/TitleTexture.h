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
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture;
	//LPDIRECT3DTEXTURE9 pTexture;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;
private:
	CSoundSource* ss = NULL;     //サウンド
	int soundtime = 0;


};

