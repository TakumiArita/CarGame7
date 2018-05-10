/*!
 *@brief	ゲームテンプレート。
 */
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "game.h"
#include "myEngine\HID\Pad.h"
#include "CSoundEngine.h"
#include "Bloom.h"

Game* game;
SceneManager* scenemanager;
//RenderTarget* renderTarget;
ShadowMap*    g_shadowmap;
Pad*          pad;
CSoundEngine* soundEngine;
//Primitive*    quadPrimitive = new Primitive;
Primitive*    quadPrimitive;

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 メインレンダリングターゲットを作成する。
	//scenemanager->mainRenderTarget.InitMainRenderTarget();
	//18-3 四角形の板ポリプリミティブを作成。
	//scenemanager->mainRenderTarget.InitQuadPrimitive();
	//18-3、18-4 シェーダーをロード。
	//scenemanager->scenemanager->mainRenderTarget.LoadShaders();
	game = new Game;
	game->Start();

	scenemanager = new SceneManager;
	scenemanager->Init();
	//quadPrimitive = new Primitive;
	
	pad = new Pad;
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	game->Draw();
	scenemanager->Draw();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	game->Update();
	scenemanager->Update();
	pad->Update();

	//OutputDebugString("Test");
	//MessageBox(NULL, "Test", "通知", MB_OK);
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	//delete game;
	//delete scenemanager;
	//delete pad;
	//delete g_effectManager;
	//soundEngine->Release();
	//g_pd3dDevice->Release();
	//g_pD3D->Release();
}
