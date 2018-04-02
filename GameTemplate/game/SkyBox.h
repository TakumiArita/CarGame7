#pragma once

#include "myEngine\Physics\CharacterController.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	//初期化。
	void Init();

	//更新。
	void Update();

	//描画
	void Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);

	//ポジション取得
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture;
	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;
private:
	CharacterController characterController; //キャラクターコントローラ
	SkinModel           m_skinmodel;
	SkinModelData       m_skinmodelData;
	D3DXVECTOR3         m_position;
	D3DXQUATERNION      m_rotation;
	D3DXVECTOR3         m_scale;
	Animation           m_animation;
	Light               m_light;

};

