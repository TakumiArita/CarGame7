#pragma once
#include "Map.h"
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Item.h"
#include "ShadowMap.h"
#include "MainRenderTarget.h"
#include "RenderTarget.h"
#include "Primitive.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "CCourcePath.h"
#include "SceneSprite.h"
#include "GoalTexture.h"
#include "StartTexture.h"
#include "GameTimeTexture.h"
#include "StartCountTexture.h"
#include "RoadAroundFrequencyTexture.h"
#include "Sprite.h"
#include "SkyBox.h"
#include "Bloom.h"
#include "CSoundSource.h"
#include "CSoundEngine.h"
#include "myEngine\HID\Pad.h"
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
	//ゲーム中の音
	void GameSound();
	//ゲーム中の音のリリース
	void GameSoundRelease();



public:
	/*
	*@brief	カメラを取得。
	 return カメラの変数
	*/
	//Camera* GetCamera()
	//{
	//	return &camera;
	//}
	Camera& GetCamera()
	{
		return camera;
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
	bool GetTitleFlag()
	{
		return Titleflag;
	}
	////カメラの視点のセッター。
	//D3DXVECTOR3 SetToCameraPos(D3DXVECTOR3 toCameraPos);
	////カメラの視点のゲッター。
	//D3DXVECTOR3 GetToCameraPos()
	//{
	//	return toCameraPos;
	//}

	//プレイヤーのゲッター。
	Player& GetPlayer()
	{
		return player;
	}
	Item& GetItem()
	{
		return item;
	}
	//Map& GetMap()
	//{
	//	return map;
	//}

	//SkyBox& GetSkyBox()
	//{
	//	return skybox;
	//}


	//タイトル表示のゲッター。
	TitleTexture& GetTitleTexture()
	{
		return titletexture;
	}
	//スタートのカウントダウンの表示のゲッター。
	StartCountTexture& GetStartCountTexture()
	{
		return startcounttexture;
	}
	//ゴールの表示のゲッター。
	GoalTexture& GetGoalTexture()
	{
		return goaltexture;
	}
	//スタートの表示のゲッター。
	StartTexture GetStartTexture()
	{
		return starttexture;
	}
	//周回回数の表示のゲッター。
	RoadAroundFrequencyTexture& GetRoadAroundFrequencyTexture()
	{
		return roadaroundfrequencytexture;
	}
	//時間の表示のゲッター。
	GameTimeTexture& GetGameTimeTexture()
	{
		return gametimetexture;
	}
	//シャドウマップのゲッター。
	ShadowMap& GetShadowMap()
	{
		return shadowmap;
	}
	//レンダーターゲットのゲッター。
	RenderTarget& GetRenderTarget()
	{
		return renderTarget;
	}
	//メインレンダーターゲットのゲッター。
	//MainRenderTarget& GetMainRenderTarget()
	//{
	//	return mainRenderTarget;
	//}
	////プリミティブのゲッター。
	//Primitive& GetPrimitive()
	//{
	//	return quadPrimitive
	//}
	////パーティクルのゲッター。
	//Particle& GetParticle()
	//{
	//	return particle;
	//}

	////パーティクルエミッタのゲッター。
	//ParticleEmitter& GetParticleEmitter()
	//{
	//	return particleemitter;
	//}
	////パーティクルエミッタのパラメータのゲッター。

	//SParticleEmitParameter& GetSParticleEmitParameter()
	//{
	//	return param;
	//}
	//コースパスのゲッター。
	CCourcePath& GetCCourcePath()
	{
		return courcePath;
	}
	////コースパスのエッジのゲッター。
	//CCourcePath::SCourceEdge& GetEdge()
	//{
	//	return edge;
	//}

	//ブルームのゲッター。
	Bloom& GetBloom()
	{
		return bloom;
	}

	//サウンドのエンジン
	CSoundEngine& GetCSoundEngine()
	{
		return soundEngine;
	}

	//サウンドのソースのポインタ。
	CSoundSource* GetCSoundSourcePointer()
	{
		return titleBgm;
	}

private:
	/*インスタンス*/
	Player                     player;	        			   //プレイヤー

	Item                       item;                           //アイテム

	Map                        map;							   //マップ
	
	SkyBox                     skybox;						   //背景

	TitleTexture               titletexture;	               //タイトル表示。
	
	StartCountTexture          startcounttexture;              //スタートNoの表示。

	GoalTexture                goaltexture;                    //ゴール表示。
												
	StartTexture               starttexture;                   //スタートの表示。
												 
	RoadAroundFrequencyTexture roadaroundfrequencytexture;     //周回回数の表示。

	GameTimeTexture            gametimetexture;                //時間の表示。


	SceneSprite                scenesprite;		  			   //シーン専用のスプライト。
	Sprite                     sprite;                         //シーン以外のスプライト。

	Camera                     camera;						   //カメラ
	
	ShadowMap                  shadowmap;					   //シャドウマップ
	
	RenderTarget               renderTarget;				   //レンダーターゲット

	MainRenderTarget           mainRenderTarget;			   //メインレンダーターゲット
	
	Primitive                  quadPrimitive;				   //プリミティブ
	
	Particle                   particle;     				   //パーティクル

	ParticleEmitter            particleemitter;				   //パーティクルエミッタ
	
	SParticleEmitParameter     param;                          //パーティクルエミッタのパラメータのゲッター。
															   
	CCourcePath                courcePath;					   //コースパス
	
	CCourcePath::SCourceEdge   edge;                           //コースパスのエッジ。

	Bloom                      bloom;                          //ブルーム。
	


	CSoundEngine               soundEngine;                    //サウンドのエンジン。
	CSoundSource*              titleBgm = NULL;                  //サウンドのソースのポインタ。


	//視点
	D3DXVECTOR3 toCameraPos;
	//カメラの注視点を中心にする。
	D3DXVECTOR3 eyePos;          
	//スペキュラライト用の視点
	D3DXVECTOR3 eyeR;
	//int gameTime;
	bool Titleflag = false;
	bool S_flag = false;
	int soundtime = 0;
	int GoalBetweenTitle = 0;

	//ブルーム用のスプライト。
	LPD3DXSPRITE bloomSprite;

};
extern SceneManager*  scenemanager;
extern ShadowMap*     g_shadowmap;
//extern RenderTarget*  renderTarget;
extern Primitive*     quadPrimitive;
extern Pad*           pad;