#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//マップ初期化。
	map.Init();
	//カメラ初期化。
	camera.Init();
	//視点設定
	//toCameraPos = { 15.0f,7.0f,0.0f };  //縦画面
	//toCameraPos = { 25.0f,7.0f,0.0f };  //縦画面幅広
	toCameraPos = { 25.0f,7.0f,0.0f };  //縦画面幅広
	//プレイヤー初期化。
	player.Init();
	//シャドウマップ初期化。
	g_shadowmap.Init();
	//スプライトの初期化。
	scenesprite.Init();
	//ゲーム時間の初期化。
	sprite.Init();
	//コースパス初期化。
	courcePath.Init(edge);
	//mainRenderTarget.InitMainRenderTarget();
	//mainRenderTarget.InitQuadPrimitive();
	//gameTime = -100;
	//背景初期化。
	skybox.Init();
	//サウンドエンジン初期化。
	soundEngine.Init();
	ss = new CSoundSource;

}
void SceneManager::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		Titleflag = true;
	}
	//マップ更新
	map.Update();
	//タイトルのテクスチャの更新。
	titletexture.Update();
	//スタートのNoテクスチャの更新。
	startcounttexture.Update();
	//スタートのテクスチャの表示。
	starttexture.Update();
	//ゴールのテクスチャの更新。
	goaltexture.Update();
	//ゲーム時間の更新
	gametimetexture.Update();
	//周回回数の更新
	roadaroundfrequencytexture.Update();
	//プレイヤーの更新
	player.Update();
	//soundSource.Update();
	//if (Titleflag == true)
	//{
	//	if (soundtime <= 0)
	//	{
	//		ss = new CSoundSource;
	//		ss->Init("Assets/sound/se_maoudamashii_effect08.wav");
	//		ss->SetVolume(0.1f);
	//		ss->Play(false);
	//	}
	//	soundtime += 1;
	//	if(soundtime >= 80)
	//	{
	//		soundtime = 0;
	//	}

	//}

	//if (ss != NULL)
	//{
	//	ss->Update();
	//}

	soundSource.Update();

	D3DXVECTOR3 targetPos = player.GetPosition();
	eyePos = targetPos;                         //カメラの注視点を中心にする。
	camera.SetLookatPt(targetPos);
	//カメラを原点に左右を向く。
	//camera.SetLookatPt(targetPos + D3DXVECTOR3( 0.0f,0.0f,player.GetLookCamera()));
	//注視点に合わせたカメラの位置
	//camera.SetEyePt(eyePos);
	//注視点を原点に左右を向く。
	//D3DXToRadian == sin,cos,tanなど三角関数に渡すときはこの関数をつかう。
	//上下なし。高い位置からの視点。	
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 70.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	
	//本来のカメラ。
	camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 10.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	
	eyeR = (camera.GetEyePt());
	//カメラの更新
	camera.Update();

	//シャドウマップ更新。
	g_shadowmap.SetLightViewPosition(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y + 25.0f, player.GetPosition().z));
	g_shadowmap.SetLightViewTarget(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y, player.GetPosition().z));
	g_shadowmap.Update();
	/*
	mainrendertarget.InitMainRenderTarget();
	mainrendertarget.InitQuadPrimitive();
	mainrendertarget.LoadShaders();
	mainrendertarget.CopyMainRTToCurrentRT();
	*/
	//gameTime++;
	skybox.Update();
}

void SceneManager::Draw()
{
	if (Titleflag == false)
	{
		scenesprite.TitleDraw();
		titletexture.TitleSound();

	}
	else if (Titleflag == true)
	{

		//アルファブレンディングOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//マップの描画
		map.Draw();
		//スプライトの描画
		sprite.Draw();
		//アルファブレンディングON
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//加算合成
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//プレイヤーの描画
		player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
		player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
		//アルファブレンディングOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);

		//シャドウマップ描画。
		g_shadowmap.Draw();

		//ゴールのテクスチャの描画。
		if (player.GetCirclingTimes() > 2)
		{
			scenesprite.GoalDraw();
		}
		//スタートのテクスチャの描画。
		if (gametimetexture.GetGameTimer() > 0 && gametimetexture.GetGameTimer() <= 100)
		{
			scenesprite.StartDraw();
		}
		skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, false);
	}
}