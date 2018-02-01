#include "stdafx.h"
#include "Player.h"
#include "SceneManager.h"
#include "myEngine/HID/Pad.h"
#include "CCourcePath.h"
//#include <math.h>

//#define ENABLE_ACCEL_SAMPLE		//この定義を有効にすると加速度のサンプルが有効になる。

//////////////////////////////////////////////////////////////      ifndefの使い方。
////Endを表示する。
//#define End
////有効にすると表示されるもの。
//#ifndef End
////範囲の終わりに定義するもの。
//#endif
//////////////////////////////////////////////////////////////

Player::Player()
{              
}

Player::~Player()
{
	if (normalMap != NULL) {
		//normalMapがNULLじゃないならロードされているので解放する。
		normalMap->Release();
	}
}
	
void Player::Init()
{
	/*
	//ライトの初期化
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(2.707f, 50.0f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-2.707f, -50.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(-2.0f, 50.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(2.0f, -50.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	*/
	//ライトの初期化
	D3DXVECTOR4 v = D3DXVECTOR4(0.707f, -100.0f, -0.707f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);	//正規化して大きさ１のベクトルに変換して、向きだけのベクトルにする。
															//w要素を含むと4要素のベクトルで正規化してしまうので、D3DXVECTOR3にキャスト、
	light.SetDiffuseLightDirection(0, v);

	v = { -0.707f, 100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(1, v);

	v = { -0.707f, -100.0f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(2, v);

	v = { 0.707f, -100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(3, v);

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	light.SetAmbientLight(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	
	//モデルのロード
	modelData.LoadModelData("Assets/modelData/Car1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/Ringo1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/potion1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/potion2.X", &animation);

	model.Init(&modelData);
	model.SetLight(&light);

	//法線マップのロード。
	D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		//法線マップ用のテクスチャ。                                             //今はない。
		"Assets/model/C3.tga",
		&normalMap
	);
	//キャラクターコントローラーの初期化
	//characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 20.0f, 0.0f));

	//コースパスの座標確認にプレイヤーの座標を使う。
	characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	//重力の設定

	//characterController.SetGravity(-35.0f);
	characterController.SetGravity(-50.0f);
	//車が止まってる時間
	stoptimer = 0;
	//車の初期加速
	accelerationtimer = 0;
	//車の初期加速失敗のタイマー
	failuretimer = 0;
	//カメラの向き初期化
	lookcamera = 0.0f;
	//プレイヤーの初期化
	qcamera = 0.0f;

	//scenemanager->ccourcepath.SCourceEdge.startToEnd
	//scenemanager->ccourcepath.SCourceEdge scourceedge;
}

void Player::Update()
{
	//パッドの入力で動かす。
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	D3DXVECTOR3 direction = GetPosition();
	D3DXVECTOR3 CCPListdirection;
	//プレイヤー回転の初期化
	D3DXQUATERNION addRot;
	D3DXQuaternionIdentity(&addRot);

	//カメラの回転
	if (GetAsyncKeyState(VK_RIGHT)/* && lookcamera >= -10.0f  && lookcamera < 10.0f*/)
	{
		lookcamera -= 1.0f;
		if (GetAsyncKeyState('S'))
		{
			lookcamera -= 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) /*&& lookcamera > -10.0f && lookcamera <= 10.0f*/)
	{
		lookcamera += 1.0f;
		if (GetAsyncKeyState('S'))
		{
			lookcamera += 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_UP)/* && lookcamera >= -10.0f  && lookcamera < 10.0f*/)
	{
		uplookcamera += 1.0f;
		if (GetAsyncKeyState('S'))
		{
			uplookcamera += 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) /*&& lookcamera > -10.0f && lookcamera <= 10.0f*/)
	{
		uplookcamera -= 1.0f;
		if (GetAsyncKeyState('S'))
		{
			uplookcamera -= 1.5f;
		}
	}

#ifndef ENABLE_ACCEL_SAMPLE 
	float accel = 0.025f;
	//プレイヤーの回転更新。
	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-GetLookCamera()));

	//上//
	if (GetAsyncKeyState('W') || pad.IsPress(pad.enButtonB))
	{
		//プレイヤーの速度。
		moveSpeed = D3DXVECTOR3(-cos(D3DXToRadian(GetLookCamera())) * 100.0f, -10.0f, -sin(D3DXToRadian(GetLookCamera())) * 100.0f);
	}
	//摩擦抵抗
	moveSpeed *= 0.95f;
	//moveSpeed *= 0.93f;
#else
	float	accel = 0.0f;
	if (pad.IsPress(pad.enButtonRB2)) {
		accel += 0.3f;
	}
	moveSpeed += moveDir * accel;
	//摩擦抵抗。
	moveSpeed *= 0.98f;
#endif
	//車が止まっている時に加速ボタンを押した時
	if ( GetAsyncKeyState(VK_UP) || pad.IsPress(pad.enButtonB))
	{
		if (moveSpeed == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			stoptimer += 1;
		}

		//加速ボタンが押されたのが短い
		if (stoptimer < 50 &&( pad.GetLStickYF() == true || pad.GetLStickXF() == true))
		{
			stoptimer = 0;
		}
		//加速ボタンが押されたのが範囲内
		else if (stoptimer >= 50 && stoptimer <= 100 &&( pad.GetLStickYF() == true || pad.GetLStickXF() == true))
		{
			//加速している
			if (accelerationtimer < 100)
			{
				moveSpeed.x *= 5.0f;
				moveSpeed.z *= 5.0f;
				accelerationtimer += 1;
			}
			//加速が終わった
			else
			{
				accelerationtimer = 0;
				stoptimer = 0;
			}
		}
		//加速ボタンが押されたのが長い
		else if (stoptimer > 100 )
		{
			failuretimer += 1;
			//発進失敗の処理開始。
			if (failuretimer <= 100)
			{
				//回転させる
				if (GetIsOnGround() == true)
				{
					//ジャンプ
					moveSpeed.y = 50.0f;
					//ジャンプしたことをキャラクタコントローラーに通知。
					characterController.Jump();
				}
				moveSpeed.x = 0.0f;
				moveSpeed.z = 0.0f;
			}
			//発進失敗の処理終了。
			else
			{
				failuretimer = 0;
				accelerationtimer = 0;
				stoptimer = 0;
			}
		}
	}
	if (!pad.IsPress(pad.enButtonB))
	{
		failuretimer = 0;
		accelerationtimer = 0;
		stoptimer = 0;
	}

	//ジャンプ
	if (GetAsyncKeyState('P'))
	{
		if (GetIsOnGround() == true)
		{
			//ジャンプ
			moveSpeed.y = 50.0f;
			//ジャンプしたことをキャラクタコントローラーに通知。
			characterController.Jump();
		}
	}

	//初期位置に戻る
	if (GetAsyncKeyState('O'))
	{
		characterController.SetPosition(D3DXVECTOR3(10.0f, 20.0f, 0.0f));
		lookcamera = 0.0f;
	}

	if (GetAsyncKeyState('J'))
	{
		if (GetIsOnGround() == true)
		{
			//ジャンプ
			moveSpeed.y = 50.0f;
			//ジャンプしたことをキャラクタコントローラーに通知。
			characterController.Jump();
		}
	}

	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);
	//キャラクタコントローラーを実行。
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), addRot, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//パッドの更新
	pad.Update();
	//方向ベクトルを正規化する。
	//D3DXVec3Normalize(&SecondmoveSpeed, &moveSpeed);
	int edgeNo = -1;
	float nearLen = 1000.0f;		//一番近いエッジまでの距離を格納する変数。
	for (int i = 0; i < scenemanager->courcePath.GetNumEdge(); i++)
	{
		//コースパスのエッジの向き(始点から終点へ向かうエッジの向き)
		D3DXVECTOR3 CListDirection = scenemanager->courcePath.GetCourceEdigeList(i).direction;
		StartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
		NormalStartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
		EndToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).endPos;
		NormalEndToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).endPos;
		D3DXVec3Normalize(&NormalStartToPlayerDirection, &StartToPlayerDirection);
		D3DXVec3Normalize(&NormalEndToPlayerDirection, &EndToPlayerDirection);
		//内積
		if (D3DXVec3Dot(&NormalStartToPlayerDirection, &CListDirection) > 0 &&
			D3DXVec3Dot(&NormalEndToPlayerDirection, &-CListDirection) < 0) {
			//プレイヤーがいる可能性のあるエッジが見つかったので、
			//エッジ上に垂線を下ろして、一番近いエッジを調べる。
			//①　エッジの始点からプレイヤーに向かうベクトル、v1を求める。
			///StartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
			//②　①で求めたベクトルと、エッジの方向ベクトルとの内積を計算して、
			//    エッジ上に射影した長さのtを求める。
			t = D3DXVec3Dot(&StartToPlayerDirection, &CListDirection);
			//③　②で求めた長さｔとエッジの方向ベクトルを乗算してベクトル、v2を求める。
			v2 = t * CListDirection;
			//④　v1-v2を計算して、エッジに落ちるベクトルのv3を求める。
			v3 = StartToPlayerDirection - v2;
			//⑤　v3の長さを利用して、一番近いエッジを見つける。   射影(projection)
			float len = D3DXVec3Length(&v3);
			if (len < nearLen) {
				//このエッジのほうが近いので更新する。
				edgeNo = i;
				nearLen = len;
			}
		}
		if (edgeNo != -1) {
			//一番近いエッジの方向を取得する。
			D3DXVECTOR3 CListDirection = scenemanager->courcePath.GetCourceEdigeList(i).direction;
			D3DXVECTOR3 moveDir;
			D3DXVec3Normalize(&moveDir, &moveSpeed);
			if (D3DXVec3Dot(&CListDirection, &moveDir) < 0) {
				MessageBox(NULL, "逆走してます。", "通知", MB_OK);
			}
		}

	}
}

void Player::Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec)
{
	model.Draw(&ViewMatrix, &ProjectionMatrix, shadowmapD, shadowmapR, Pspec);
}