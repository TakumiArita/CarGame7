#include "stdafx.h"
#include "SkyBox.h"


//SkyBox::SkyBox() :
//	m_skinModel(),
//	m_skinModelData(),
//	m_position(0.0f,0.0f,0.0f),
//	m_rotation(0.0f,0.0f,0.0f,1.0f),
//	m_scale(1.0f,1.0f,1.0f),
//	m_light()
//{
//
//}
SkyBox::SkyBox()
{

}

SkyBox::~SkyBox()
{

}

void SkyBox::Init()
{
	//ライトの初期化
	D3DXVECTOR4 v = D3DXVECTOR4(0.707f, -100.0f, -0.707f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);	//正規化して大きさ１のベクトルに変換して、向きだけのベクトルにする。
															//w要素を含むと4要素のベクトルで正規化してしまうので、D3DXVECTOR3にキャスト、
	m_light.SetDiffuseLightDirection(0, v);

	v = { -0.707f, 100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	m_light.SetDiffuseLightDirection(1, v);

	v = { -0.707f, -100.0f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	m_light.SetDiffuseLightDirection(2, v);

	v = { 0.707f, -100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);


	m_light.SetDiffuseLightDirection(3, v);

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//モデルのロード
	m_skinmodelData.LoadModelData("Assets/modelData/skybox6.X", &m_animation);


	m_skinmodel.Init(&m_skinmodelData);
	m_skinmodel.SetLight(&m_light);
	//characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

void SkyBox::Update()
{
	//D3DXQUATERNION addRot;
	//m_animation.Update(1.0f / 60.0f);
	m_skinmodel.UpdateWorldMatrix(D3DXVECTOR3(0.0f, -100.0f, 0.0f), /*addRot*/D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void SkyBox::Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec)
{
	DWORD backup;
	g_pd3dDevice->GetRenderState(D3DRS_CULLMODE, &backup);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, CullMode_CullCounterClockwiseFace);
	
	m_skinmodel.Draw(&ViewMatrix, &ProjectionMatrix, shadowmapD, shadowmapR, Pspec);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, backup);
}

