#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine\HID\Pad.h"
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	if (titleBgm != NULL)
	{
		delete titleBgm;
	}
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
	//アイテム初期化。
	item.Init();
	//シャドウマップ初期化。
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();
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
	//gamess = new CSoundSource;
	

	param.texturePath = "Mahouzin.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	particleemitter.Init(param);
	//レンダリングターゲットを作成する。
	GetRenderTarget().Create(
		FRAME_BUFFER_WIDTH,  //レンダリングターゲットの横の解像度。
		FRAME_BUFFER_HEIGHT, //レンダリングターゲットの縦の解像度。
		1,                   //1でいい。
		D3DFMT_A16B16G16R16F,//DirectX3のテキストを読んで調べる。16ビットの浮動小数点バッファを使う。
		D3DFMT_D16,          //16bitの深度バッファのフォーマットを指定する。
		D3DMULTISAMPLE_NONE, //D3DMULTISAMPLE_NONEでいい。
		0                    //0でいい。
	);
	D3DXCreateSprite(
		g_pd3dDevice,
		&bloomSprite
	);
}
void SceneManager::Update()
{
	if (GetAsyncKeyState(VK_SPACE) || pad->IsPress(pad->enButtonStart))
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
	//アイテムの更新
	item.Update();
	//プレイヤーの更新
	player.Update();

	//particle.Update();
	//particleemitter.Render(camera.GetViewMatrix(),camera.GetProjectionMatrix());

	//particleemitter.Update();
	//particle.Update();


	GameSound();
	if (titleBgm != NULL)
	{
		titleBgm->Update();
	}

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
	g_shadowmap->SetLightViewPosition(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y + 25.0f, player.GetPosition().z));
	g_shadowmap->SetLightViewTarget(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y, player.GetPosition().z));
	g_shadowmap->Update();
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
	//タイトル。
	if (Titleflag == false)
	{
		titletexture.TitleSound();
		scenesprite.TitleDraw();
		player.PlayerRelease();
		sprite.SaveGameTimeDraw();
	}
	//タイトルから遷移。
	else if (Titleflag == true)
	{
		titletexture.TitleRelease();
		//アルファブレンディングOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		{

			
			//後で戻すためにフレームバッファのレンダリングターゲットとデプスステンシルバッファのバックアップを取る。
			LPDIRECT3DSURFACE9 frameBufferRT;
			LPDIRECT3DSURFACE9 frameBufferDS;
			g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
			g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

			//レンダリングターゲットをオフスクリーンにする。
			g_pd3dDevice->SetRenderTarget(
				0,
				renderTarget.GetRenderTarget()
			);
			g_pd3dDevice->SetDepthStencilSurface(renderTarget.GetDepthStencilBuffer());
			g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
			
			//不透明物の描画。
			skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, false);
			//マップの描画
			map.Draw();

			//半透明物の描画。
			//アルファブレンディングON
			g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			//半透明合成
			//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			//加算合成
			g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			//プレイヤーの描画
			player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
			//アイテムの描画
			item.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
			//アルファブレンディングOFF
			g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			
			particleemitter.Render(camera.GetViewMatrix(), camera.GetProjectionMatrix());

			//ブルームの描画。
			bloom.Render();
			//シーンの描画が完了したのでレンダリングターゲットをフレームバッファに戻す。
			g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
			g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
			//参照カウンタが増えているので開放。
			frameBufferRT->Release();
			frameBufferDS->Release();

			//スプライトの作成。
			g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
			bloomSprite->Begin(D3DXSPRITE_DONOTSAVESTATE);
			bloomSprite->Draw(
				renderTarget.GetTexture(),
				NULL,
				&(D3DXVECTOR3(10.0f, 0.0f, 0.0f)),
				&(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
				(D3DCOLOR_ARGB(255, 255, 255, 255))
			);
			bloomSprite->End();
		}

		//シャドウマップ描画。
		g_shadowmap->Draw();

		//スプライトの描画
		sprite.Draw();
		//ゴールのテクスチャの描画。
		if (player.GetCirclingTimes() > 2)
		{
			scenesprite.GoalDraw();
			GoalBetweenTitle++;
		}
		if (GoalBetweenTitle >= 100)
		{
			gametimetexture.SaveUpdate();
			Titleflag = false;
			GoalBetweenTitle = 0;
			GameSoundRelease();
		}
		//スタートのテクスチャの描画。
		if (gametimetexture.GetGameTimer() > 0 && gametimetexture.GetGameTimer() <= 100)
		{
			scenesprite.StartDraw();
		}
		
	}
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

}

void SceneManager::GameSound()
{

	if (Titleflag == true)
	{
		if (titleBgm == NULL)
		{
			titleBgm = new CSoundSource;
			titleBgm->Init("Assets/sound/holidays.wav");
			titleBgm->SetVolume(0.5f);
			titleBgm->Play(true);
		}
	}
}

void SceneManager::GameSoundRelease()
{
	if (titleBgm != NULL)
	{
		delete titleBgm;
		titleBgm = NULL;
	}
}


