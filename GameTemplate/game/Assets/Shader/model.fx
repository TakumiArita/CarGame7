/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

#include "LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4	g_rotationMatrix;		//!<回転行列。
float4x4	g_viewMatrixRotInv;		//!<カメラの回転行列の逆行列。

//シャドウマップ用の変数
float4x4    g_viewMatrix;
float4x4    g_projectionMatrix;

bool        shadowmapR;
float4x4    g_lightViewMatrix;
float4x4    g_lightPrjetionMatrix;
float4x4    g_lightViewProj;

//スペキュラライト用の変数
float3      eyePos;                 //プレイヤーの向いてる方向。
float4      PSetDiffuseLight;       //プレイヤーのディフューズライト。
bool        Pspec;                  //プレイヤーのスペキュラライトのフラグ。

int g_isHasNormalMap;			//法線マップ保持している？

texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture g_shadowMapTexture;    //シャドウマップテクスチャ
sampler g_shadowMapTextureSampler =
sampler_state
{
	Texture = <g_shadowMapTexture>;
	MipFilter = NONE;
	MipFilter = NONE;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};
//法線マップ
texture g_normalTexture;		//法線マップ。
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};


/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
	float4  Pos             : POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float3  Normal          : NORMAL;
	float3	Tangent			: TANGENT;		//接ベクトル
	float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     		: POSITION;
	float3  Normal			: NORMAL;
	float2  Tex0   			: TEXCOORD0;
	float3	Tangent			: TEXCOORD1;	//接ベクトル
	float4  lightViewPos    : TEXCOORD2;
	float4  PosInProj       : TEXCOORD3;
	float4 worldPos         : TEXCOORD4;
};
/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4]        = (int[4])IndexVector;
	float LastWeight = 0.0f;
	for (int iBone = 0; iBone < g_numBone-1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];
		
		Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight; 
	
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
	Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
	Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent );
	}
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	o.PosInProj = o.Pos;
	o.worldPos  = float4(Pos.xyz, 1.0f);
	o.Normal = normalize(Normal);
	o.Tangent = normalize(Tangent);
	o.Tex0 = In.Tex0;
	if (shadowmapR == true)
	{
		o.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_lightViewProj);
	}
	return o;
}

/*!
  *@brief	シャドウ用の頂点シェーダー。
  */
VS_OUTPUT VSShadowMain(VS_INPUT In, uniform bool hasSkin)
{
	float3 Pos, Normal, Tangent;
	//スキンあり。
	if (hasSkin)
	{
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	//スキンなし
	else
	{
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent);
	}
	VS_OUTPUT Out = (VS_OUTPUT)0;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.PosInProj = Out.Pos;
	if (shadowmapR == true)
	{
		Out.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_lightViewProj);
	}
	return Out;
}
/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;

	//法線マップの処理。
	if (g_isHasNormalMap == 1) {
		//法線マップがある。
		//法線マップから、
		//タンジェントスペース法線を取得。
		float3 localNormal = tex2D(
			g_normalMapSampler,
			In.Tex0
		);
		//-1.0～1.0の範囲にマッピングする。
		localNormal = (localNormal * 2.0f) - 1.0f;
		//法線とタンジェントから従法線を求める。
		float3 tangent = normalize(In.Tangent);
		float3 biNormal = cross(
			tangent,
			normal
		);
		//従法線を正規化する。
		biNormal = normalize(biNormal);
		//ワールド空間の法線を求める。
		normal = tangent * localNormal.x
			   + biNormal * localNormal.y
			   + normal * localNormal.z;
	}

	for (float i = 0; i < 4; i++)
	{
		//スペキュラライト用の処理。
		float3 eyePostwo = normalize(eyePos - In.worldPos.xyz);
		//float3 PSetDiffuseLighttwo = normalize(PSetDiffuseLight.xyz);
		float3 diffuseLightDirtwo = normalize(g_light.diffuseLightDir[i].xyz);
		float3 Reflection = -eyePostwo + 2.0f * (dot(normal, eyePostwo)) * normal;
		//float spec = max(0.0f, dot(normalize(Reflection), -PSetDiffuseLighttwo));
		float spec = max(0.0f, dot(normalize(Reflection), -diffuseLightDirtwo));
		spec = pow(spec, 2.0f);
		if (Pspec == true)
		{
			color.xyz += spec * g_light.diffuseLightColor[i].xyz *g_light.diffuseLightColor[i].w;
		}
	}
		float4 lig = DiffuseLight(normal);
		color *= lig;

	//デプスシャドウ追加
	//X且つYの値が0以上1以下にする。
	if (shadowmapR == true)
	{
		float2 shadowMapUV = (In.lightViewPos.xy / In.lightViewPos.w * float2(0.5f, -0.5f) + float2(0.5f, 0.5f));
		if (shadowMapUV.x >= 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y >= 0.0f && shadowMapUV.y < 1.0f )
		{
			float4 shadowVal = tex2D(g_shadowMapTextureSampler, shadowMapUV);
			if (shadowVal.r < In.lightViewPos.z / In.lightViewPos.w)
			{
				color *= 0.5f;
			}
			
		}
		
	}
	return color;
}
/*!
*@brief シャドウマップシェーダー
*/
float4 PSShadowMain(VS_OUTPUT In) : COLOR
{
	float z = In.PosInProj.z / In.PosInProj.w;
	return float4(z, z, z, 1.0f);
}
/*!
 *@brief	スキンありモデル用のテクニック。
 */
technique SkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
	}
}
/*!
 *@brief	スキンなしモデル用のテクニック。
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}
/*!
*@brief	シャドウマップ描画用のテクニック。
*/
technique ShadowSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSShadowMain(true);
		PixelShader = compile ps_3_0 PSShadowMain();
	}
};
/*!
*@brief	シャドウマップなしの描画用のテクニック。
*/
technique NoShadowSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSShadowMain(false);
		PixelShader = compile ps_3_0 PSShadowMain();
	}
};