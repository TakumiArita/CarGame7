#include "stdafx.h"
#include "Item.h"
#include "SceneManager.h"


Item::Item()
{
}

Item::~Item()
{
}

void Item::Init()
{
	//ライトの初期化。
	//D3DXVECTOR4 v = D3DXVECTOR4(0.707f, -100.0f, -0.707f, 1.0f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);   //正規化して大きさ１のベクトルに変換して、向きだけのベクトルにする。													 //w要素を含むと4要素のベクトルで正規化してしまうので、D3DXVECTOR3にキャスト。
	//light.SetDiffuseLightDirection(0, v);

	//v = { -0.707f, 100.707f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(1, v);

	//v = { -0.707f, -100.0f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(2, v);

	//v = { 0.707f, -100.707f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(3, v);

	//light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	//light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	//light.SetDiffuseLightColor(2, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	//light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));

	//モデルのロード。
	modelData.LoadModelData("Assets/modelData/potion2.X", &animation);
	//modelData.LoadModelData("Assets/modelData/Ringo1.X", &animation);

	model.Init(&modelData);
	model.SetLight(&light);

	//キャラクターコントローラーの初期化。
	characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 5.0f, 50.0f));
	//重力
	characterController.SetGravity(-50.0f);

	playerToItem.x = scenemanager->GetPlayer().GetPosition().x - GetPosition().x;
	playerToItem.z = scenemanager->GetPlayer().GetPosition().z - GetPosition().z;
	//playerToItem = GetPosition() - scenemanager->player.GetPosition();


}

void Item::Update()
{
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);
	
	playerToItem.x = scenemanager->GetPlayer().GetPosition().x - GetPosition().x;
	playerToItem.z = scenemanager->GetPlayer().GetPosition().z - GetPosition().z;
	//playerToItem = GetPosition() - scenemanager->player.GetPosition();
	if (itemEffectTime > 0)
	{
		itemEffectTime--;
	}
	//キャラクターコントローラーを実行。
	characterController.Execute();
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Item::Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec)
{
	if (itemEffectTime <= 0)
	{
		itemFlag = false;
		model.Draw(&ViewMatrix, &ProjectionMatrix, shadowmapD, shadowmapR, Pspec);
		if ((playerToItem.x <= 1.5f && playerToItem.x >= -1.5f)  )
		{
			if ((playerToItem.z <= 1.5f && playerToItem.z >= -1.5f))
			{
				itemEffectTime = 50;
				itemFlag = true;
			}
		}
	}
}