#pragma once
#include "RenderTarget.h"
class ShadowMap
{
	RenderTarget renderTarget;
	D3DXMATRIX  lightViewMatrix;
	D3DXMATRIX  lightProjectionMatrix;
	D3DXVECTOR3 viewPosition;
	D3DXVECTOR3 viewTarget;
public:
	ShadowMap();
	~ShadowMap();

	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
	RenderTarget GetRenderTarget()
	{
		return renderTarget;
	}

	void Init();
	//ライトビューの視点
	void SetLightViewPosition(const D3DXVECTOR3& lightViewTarget)
	{
		viewPosition = lightViewTarget;
	}
	D3DXVECTOR3 GetLightViewPosition()
	{
		return viewPosition;
	}
	//ライトビューの注視点
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//ライトビュー行列の取得
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//ライトプロジェクション行列の取得
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjectionMatrix;
	}

	void Update();
	void Draw();
};

