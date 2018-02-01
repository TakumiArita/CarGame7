/*!
 *@brief	ゲームテンプレート。
 */
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "game.h"

Game* game;
SceneManager* scenemanager;
RenderTarget* renderTarget;
ShadowMap     g_shadowmap;

/*
//-----------------------------------------------------------------------------
// 板ポリを描画。
//-----------------------------------------------------------------------------
void DrawQuadPrimitive()
{
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
	);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		quadPrimitive->GetNumPolygon()			//プリミティブの数。
	);
}
*/
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 メインレンダリングターゲットを作成する。
	//scenemanager->mainRenderTarget.InitMainRenderTarget();
	//18-3 四角形の板ポリプリミティブを作成。
	//scenemanager->scenemanager->mainRenderTarget.InitQuadPrimitive();
	//18-3、18-4 シェーダーをロード。
	//scenemanager->scenemanager->mainRenderTarget.LoadShaders();

	game = new Game;
	game->Start();

	scenemanager = new SceneManager;
	scenemanager->Init();
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
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete game;
	delete scenemanager;
	delete g_effectManager;
	//scenemanager->mainrendertarget.GetTerminate();
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
