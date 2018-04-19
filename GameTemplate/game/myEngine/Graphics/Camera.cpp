#include "stdafx.h"
#include "Camera.h"

//コンストラクタ。
Camera::Camera()
{
	Near = 0.1f;
	//Near = 700.0f;
	//どこまでカメラが映せるかの範囲。
	//Far = 100.0f;
	//Far = 700.0f;
	//Far = 1000.0f;
	Far = 5000.0f;
	aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}
//デストラクタ
Camera::~Camera()
{

}
//アスペクト比を設定。
void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
}
//アスペクト比を取得。
float Camera::GetAspect()
{
	return aspect;
}
//ファーを設定。
void Camera::SetFar(float _far)
{
	Far = _far;
}
//ニアーの取得。
float Camera::GetNear()
{
	return Near;
}
//ファーの取得。
float Camera::GetFar()
{
	return Far;
}
//ニアーを設定。
void Camera::SetNear(float _near)
{
	Near = _near;
}
//視点のセッター
void Camera::SetEyePt(D3DXVECTOR3 pt)
{
	vEyePt = pt;
}
//視点のゲッター
D3DXVECTOR3 Camera::GetEyePt()
{
	return vEyePt;
}
//注視点のセッター
void Camera::SetLookatPt(D3DXVECTOR3 pt)
{
	vLookatPt = pt;
}
//注視点のゲッター。
D3DXVECTOR3 Camera::GetLookatPt()
{
	return vLookatPt;
}
//上方向のセッター
void Camera::SetUpVec(D3DXVECTOR3 up)
{
	vUpVec = up;
}
//上方向のゲッター
D3DXVECTOR3 Camera::GetUpVec()
{
	return vUpVec;
}
//ビュー行列のセッター。
void Camera::SetViewMatrix(D3DXMATRIX mView)
{
	viewMatrix = mView;
}
//ビュー行列のゲッター
D3DXMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}
//プロジェクション行列のセッター
void Camera::SetProjectionMatrix(D3DXMATRIX mProj)
{
	projectionMatrix = mProj;
}
//プロジェクション行列のゲッター
D3DXMATRIX Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}
//カメラの更新処理。
void Camera::Update()
{
	//ビュー変換行列
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}

//カメラの初期化。
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 0.5f, 40.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);      //上下左右判定する所。

	Update();
}

D3DXMATRIX Camera::GetInvRotateMat()
{
	D3DXMATRIX Inv;
	//D3DXMatrixIdentity(&Inv);
	//D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0, 0, 0), &vLookatPt, &vUpVec);
	//D3DXMatrixInverse(&Inv, NULL, &Inv);
	D3DXMatrixInverse(&Inv, NULL, &viewMatrix);
	Inv.m[3][0] = 0;
	Inv.m[3][1] = 0;
	Inv.m[3][2] = 0;

	return Inv;
}