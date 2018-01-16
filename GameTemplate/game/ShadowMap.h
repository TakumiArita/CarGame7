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
	//���C�g�r���[�̎��_
	void SetLightViewPosition(const D3DXVECTOR3& lightViewTarget)
	{
		viewPosition = lightViewTarget;
	}
	D3DXVECTOR3 GetLightViewPosition()
	{
		return viewPosition;
	}
	//���C�g�r���[�̒����_
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//���C�g�r���[�s��̎擾
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//���C�g�v���W�F�N�V�����s��̎擾
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjectionMatrix;
	}

	void Update();
	void Draw();
};

