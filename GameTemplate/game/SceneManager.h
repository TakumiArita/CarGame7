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

	//カメラ
	Camera            camera;
	//プレイヤー
	Player            player;
	//アイテム
	Item              item;
	//マップ
	Map               map;
	//背景
	SkyBox            skybox;
	//タイトル表示。
	TitleTexture titletexture;
	//スタートNoの表示。
	StartCountTexture startcounttexture;
	//ゴール表示。
	GoalTexture  goaltexture;
	//スタートの表示。
	StartTexture starttexture;
	//周回回数の表示。
	RoadAroundFrequencyTexture roadaroundfrequencytexture;
	//タイトル、ゴールなどのスプライト。
	SceneSprite  scenesprite;

	//時間表示
	Sprite             sprite;
	GameTimeTexture    gametimetexture;
	//シャドウマップ
	ShadowMap          shadowmap;
	//レンダーターゲット
	RenderTarget       renderTarget;
	//メインレンダーターゲット
	MainRenderTarget mainRenderTarget;
	//プリミティブ
	Primitive quadPrimitive;
	//パーティクル
	Particle particle;
	//パーティクルエミッタ
	ParticleEmitter particleemitter;
	SParticleEmitParameter param;
	//コースパス
	CCourcePath        courcePath;
	CCourcePath::SCourceEdge  edge;

	//サウンド
	CSoundEngine soundEngine;
	CSoundSource soundSource;
	CSoundSource* gamess = NULL;     //サウンド

private:
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
};
extern SceneManager*  scenemanager;
extern ShadowMap      g_shadowmap;
extern RenderTarget*  renderTarget;
extern Primitive*     quadPrimitive;
extern Pad*           pad;