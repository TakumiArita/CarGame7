#pragma once

#include "myEngine\Physics\CharacterController.h"
#include "myEngine\HID\Pad.h"
using namespace std;
class Player
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);

	//ポジション取得
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
	//カメラ回転角度
	float GetLookCamera()
	{
		return lookcamera;
	}
	//プレイヤーとカメラの回転
	float GetQCamera()
	{
		return qcamera;
	}
	//仮
	bool GetIsOnGround()
	{
		return characterController.IsOnGround();
	}
	bool GetIsJump()
	{
		return characterController.IsJump();
	}
	Light GetLight()
	{
		return light;
	}
	int GetStartToGoal()
	{
		return startToGoal;
	}
private:
	SkinModel           model;
	SkinModelData       modelData;
	Animation           animation;
	Light               light;               //ライト
	Pad                 pad;                 //パッド
	D3DXQUATERNION      rotation;            //回転
	CharacterController characterController; //キャラクターコントローラ
	float               movedirz = 0.0f;
	D3DXVECTOR3			moveDir = {-1.0f, 0.0f, 0.0f};	//車の進行方向。
	int startToGoal = 0;
	//止まっているタイマー
	int stoptimer;
	//加速タイマー
	int accelerationtimer;
	//失敗したタイマー
	int failuretimer;
	//カメラの向き
	float lookcamera;
	//プレイヤーの回転
	float qcamera;
	//法線マップ
	LPDIRECT3DTEXTURE9 normalMap = NULL;
};
