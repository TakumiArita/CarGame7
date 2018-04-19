#pragma once

#include "myEngine\Physics\CharacterController.h"
#include "CSoundSource.h"
//#include "SceneManager.h"
class Item
{
public:
	Item();
	~Item();

	void Init();
	void Update();
	void Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);

	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
	bool GetItemFlag()
	{
		return itemFlag;
	}

private:
	SkinModel           model;
	SkinModelData       modelData;
	Animation           animation;
	Light               light;               //ライト
	D3DXQUATERNION      rotation;            //回転
	CharacterController characterController; //キャラクターコントローラ
	D3DXVECTOR3 playerToItem = D3DXVECTOR3(NULL, NULL, NULL);
	int itemEffectTime = 0;
	bool itemFlag = false;
};

