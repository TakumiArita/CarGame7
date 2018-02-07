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
	//クリア初期化。
	clear.Init();
	//コースパス初期化。
	courcePath.Init(edge);
	//mainRenderTarget.InitMainRenderTarget();
	//mainRenderTarget.InitQuadPrimitive();
}
void SceneManager::Update()
{
	//マップ更新
	map.Update();
	//クリアテクスチャの更新。
	clearTexture.Update();
	//プレイヤーの更新
	player.Update();
	//カメラの視点の更新
    //toCameraPos = { 25.0f,7.0f,player.GetLookCamera() };  //縦画面幅広
	D3DXVECTOR3 targetPos = player.GetPosition();
	eyePos = targetPos;                         //カメラの注視点を中心にする。
	camera.SetLookatPt(targetPos);

	//カメラを原点に左右を向く。
	//camera.SetLookatPt(targetPos + D3DXVECTOR3( 0.0f,0.0f,player.GetLookCamera()));
	//注視点に合わせたカメラの位置
	//camera.SetEyePt(eyePos);
	//注視点を原点に左右を向く。
	//D3DXToRadian == sin,cos,tanなど三角関数に渡すときはこの関数をつかう。
	camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 70.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//上下も追加。
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, player.GetUpLookCamera(), sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//上下なし。高い位置からの視点。
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 700.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//本来のカメラ。
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 5.0f, 7.0f, sin(D3DXToRadian(player.GetLookCamera())) * 5.0f));

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

}

void SceneManager::Draw()
{
	//アルファブレンディングOFF
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//マップの描画
	map.Draw();
	//アルファブレンディングON
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//加算合成
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	
	//プレイヤーの描画
	player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
	player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(),false,false,true);
	//アルファブレンディングOFF
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);

	//シャドウマップ描画。
	g_shadowmap.Draw();
	if (player.GetCirclingTimes() > 2)
	{
		clear.Draw();
	}
}


