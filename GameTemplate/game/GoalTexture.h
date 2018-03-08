#pragma once
class GoalTexture
{
public:
	GoalTexture();
	~GoalTexture();

	void Init();
	void Update();
	void Draw();
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture;
	//LPDIRECT3DTEXTURE9 pTexture;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;
};

