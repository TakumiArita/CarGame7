#pragma once

#include "RenderTarget.h"
class Bloom
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Bloom();
	/*!
	* @brief	デストラクタ。
	*/
	~Bloom();
	/*!
	* @brief  描画。
	*/
	void Render();
	//重みの更新。
	void UpdateWeight(float dispersion);
	//---------------------------------------------------------
	//ブルームで使用するプリミティブの初期化。
	//---------------------------------------------------------
	void InitQuadPrimitive();

	//---------------------------------------------------------
	// 板ポリを描画。
	//---------------------------------------------------------
	void DrawQuadPrimitive();
private:
	LPD3DXEFFECT effect;                       //シェーダーエフェクト
	RenderTarget luminanceRenderTarget;       //輝度を抽出するためのレンダリングターゲットを追加。
	RenderTarget downSamplingRenderTarget[2]; //!<ブラーをかけるためのダウンサンプリング用のレンダリングターゲット。
	static const int NUM_WEIGHTS = 8;          //!<ガウスブラーの重み。
	float weights[NUM_WEIGHTS];                //!<ガウスブラーで使う重みテーブル。

};

