#pragma once
#include <list>
#include <d3d9.h>
#include <d3dx9effect.h>
class Particle;
/*
* @brief    パーティクル生成パラメータ。
*/
struct SParticleEmitParameter {
	//初期化。
	void Init()
	{
		memset(this, 0, sizeof(SParticleEmitParameter));
	}
	const char* texturePath;            //テクスチャのファイルパス。
	float w;                            //パーティクルの幅。
	float h;							//パーティクルの高さ。
	float intervalTime;                 //パーティクルの発生間隔。
	D3DXVECTOR3 initSpeed;				//初速度。
	D3DXVECTOR3 position;               //座標
};
/*
*  @brief    パーティクルの発生機
*/
class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	/*
	* @brief    初期化。
	*@param[in]     camera        パーティクルの描画で使用するカメラ。
	*@param[in]     param         パーティクル生成用のパラメータ
	*/

	void Init(const SParticleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParticleEmitParameter   param;            //パラメータ。
	std::list<Particle*>   particleList;       //パーティクルのリスト。
	float timer;                                //タイマー。

};

