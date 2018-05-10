#pragma once

#include "Primitive.h"
#include <d3dx9effect.h>

struct SParticleEmitParameter;
/*
* @brief   �p�[�e�B�N���B
*/
class Particle
{
	enum eState {
		eStateRun,
		eStateFadeOut,
		eStateDead,
	};

public:
	Particle();
	~Particle();
	void Init(const SParticleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);

private:
	Primitive          primitive;    //�v���~�e�B�u�B
	LPDIRECT3DTEXTURE9 texture;      //�e�N�X�`���B
	ID3DXEffect*       shaderEffect; //�V�F�[�_�[�G�t�F�N�g�B
	D3DXVECTOR3        moveSpeed;    //���x�B
	D3DXVECTOR3        position;     //���W�B


	float timer;
	bool isBillboard;
	D3DXMATRIX mWorld;

	eState state;    //���
	float life;      //���C�t
	float fadeTIme;  //�t�F�[�h�̎���
	float initAlpha; //�����A���t�@
	float alpha;     //�A���t�@
	bool isFade;     //���S���Ƀt�F�[�h�A�E�g�H


};

