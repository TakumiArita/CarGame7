#pragma once
#include "Map.h"
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "ShadowMap.h"
#include "MainRenderTarget.h"
#include "RenderTarget.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "Clear.h"
#include "ClearTexture.h"
//#include "locationInfo.h"

class SceneManager
{
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	/*
	*@brief	カメラを取得。
	 return カメラの変数
	*/
	Camera* GetCamera()
	{
		return &camera;
	}
	/*
	*@brief カメラの注視点を取得。
	return  カメラの注視点
	*/
	D3DXVECTOR3 GetEyePos()
	{
		return eyePos;
	}
	D3DXVECTOR3 GetEyeR()
	{
		return eyeR;
	}
	////カメラの視点のセッター。
	//D3DXVECTOR3 SetToCameraPos(D3DXVECTOR3 toCameraPos);
	////カメラの視点のゲッター。
	//D3DXVECTOR3 GetToCameraPos()
	//{
	//	return toCameraPos;
	//}

	//カメラ
	Camera            camera;
	//プレイヤー
	Player            player;
	//マップ
	Map                map;
	Clear              clear;
	ClearTexture       clearTexture;
	//シャドウマップ
	ShadowMap          shadowmap;
	//レンダーターゲット
	RenderTarget       renderTarget;
	//メインレンダーターゲット
	MainRenderTarget mainRenderTarget;
	//プリミティブ
	Primitive quadPrimitive;
	//コースパス
	CCourcePath        courcePath;
	CCourcePath::SCourceEdge  edge;
	//SCourceEdge        scourceedge;
private:
	//視点
	D3DXVECTOR3 toCameraPos;
	//カメラの注視点を中心にする。
	D3DXVECTOR3 eyePos;          
	//スペキュラライト用の視点
	D3DXVECTOR3 eyeR;

};
extern SceneManager*  scenemanager;
extern ShadowMap      g_shadowmap;
extern 	RenderTarget* renderTarget;
extern 	Primitive*    quadPrimitive;


