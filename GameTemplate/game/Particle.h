#pragma once

#include "Primitive.h"
#include <d3dx9effect.h>

struct SParticleEmitParameter;
/*
* @brief   パーティクル。
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
	Primitive          primitive;    //プリミティブ。
	LPDIRECT3DTEXTURE9 texture;      //テクスチャ。
	ID3DXEffect*       shaderEffect; //シェーダーエフェクト。
	D3DXVECTOR3        moveSpeed;    //速度。
	D3DXVECTOR3        position;     //座標。


	float timer;
	bool isBillboard;
	D3DXMATRIX mWorld;

	eState state;    //状態
	float life;      //ライフ
	float fadeTIme;  //フェードの時間
	float initAlpha; //初期アルファ
	float alpha;     //アルファ
	bool isFade;     //死亡時にフェードアウト？


};

