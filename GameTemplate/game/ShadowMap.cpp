#include "stdafx.h"
#include "ShadowMap.h"
#include "myEngine\Graphics\SkinModel.h"
#include "SceneManager.h"

ShadowMap::ShadowMap()
{
	D3DXMatrixIdentity(&lightViewMatrix);
	D3DXMatrixIdentity(&lightProjectionMatrix);
	viewPosition.x = 0.0f;
	viewPosition.y = 0.0f;
	viewPosition.z = 0.0f;
	viewTarget.x = 0.0f;
	viewTarget.y = 0.0f;
	viewTarget.z = 0.0f;
}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Init()
{
	//レンダリングターゲットの初期化
	renderTarget.Create(
		512,
		512,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);
}

void ShadowMap::Update()
{
	D3DXVECTOR3 tmp = viewTarget - viewPosition;
	D3DXVec3Normalize(&tmp, &tmp);
	if (fabsf(tmp.y) > 0.9999f) {
		//カメラが真上か真下を向いている
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
	else {
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&lightProjectionMatrix, D3DXToRadian(60.0f), 1.0f, 1.1f, 100.0f);
	D3DXMatrixOrthoLH(&lightProjectionMatrix, 100, 100, 0, 100);
}

void ShadowMap::Draw()
{
	//保存変数
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);
	g_pd3dDevice->SetRenderTarget(0, renderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(renderTarget.GetDepthStencilBuffer());
	g_pd3dDevice->BeginScene();
	//書き込み先を変更したのでクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	scenemanager->player.Draw(lightViewMatrix, lightProjectionMatrix, true, false,false);
	g_pd3dDevice->EndScene();
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//戻す。
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//戻す。
}