/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

#include "LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4	g_worldMatrix;			//!<���[���h�s��B
float4x4	g_rotationMatrix;		//!<��]�s��B
float4x4	g_viewMatrixRotInv;		//!<�J�����̉�]�s��̋t�s��B

//�V���h�E�}�b�v�p�̕ϐ�
float4x4    g_viewMatrix;
float4x4    g_projectionMatrix;

bool        shadowmapR;
float4x4    g_lightViewMatrix;
float4x4    g_lightPrjetionMatrix;
float4x4    g_lightViewProj;

//�X�y�L�������C�g�p�̕ϐ�
float3      eyePos;                 //�v���C���[�̌����Ă�����B
float4      PSetDiffuseLight;       //�v���C���[�̃f�B�t���[�Y���C�g�B
bool        Pspec;                  //�v���C���[�̃X�y�L�������C�g�̃t���O�B

int g_isHasNormalMap;			//�@���}�b�v�ێ����Ă���H

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
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

texture g_shadowMapTexture;    //�V���h�E�}�b�v�e�N�X�`��
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
//�@���}�b�v
texture g_normalTexture;		//�@���}�b�v�B
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
 * @brief	���͒��_
 */
struct VS_INPUT
{
	float4  Pos             : POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float3  Normal          : NORMAL;
	float3	Tangent			: TANGENT;		//�ڃx�N�g��
	float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	�o�͒��_�B
 */
struct VS_OUTPUT
{
	float4  Pos     		: POSITION;
	float3  Normal			: NORMAL;
	float2  Tex0   			: TEXCOORD0;
	float3	Tangent			: TEXCOORD1;	//�ڃx�N�g��
	float4  lightViewPos    : TEXCOORD2;
	float4  PosInProj       : TEXCOORD3;
	float4 worldPos         : TEXCOORD4;
};
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
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
 *@brief	���[���h���W�ƃ��[���h�@�����v�Z�B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	���_�V�F�[�_�[�B
 *@param[in]	In			���͒��_�B
 *@param[in]	hasSkin		�X�L������H
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );
	}else{
		//�X�L���Ȃ��B
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
  *@brief	�V���h�E�p�̒��_�V�F�[�_�[�B
  */
VS_OUTPUT VSShadowMain(VS_INPUT In, uniform bool hasSkin)
{
	float3 Pos, Normal, Tangent;
	//�X�L������B
	if (hasSkin)
	{
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	//�X�L���Ȃ�
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
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;

	//�@���}�b�v�̏����B
	if (g_isHasNormalMap == 1) {
		//�@���}�b�v������B
		//�@���}�b�v����A
		//�^���W�F���g�X�y�[�X�@�����擾�B
		float3 localNormal = tex2D(
			g_normalMapSampler,
			In.Tex0
		);
		//-1.0�`1.0�͈̔͂Ƀ}�b�s���O����B
		localNormal = (localNormal * 2.0f) - 1.0f;
		//�@���ƃ^���W�F���g����]�@�������߂�B
		float3 tangent = normalize(In.Tangent);
		float3 biNormal = cross(
			tangent,
			normal
		);
		//�]�@���𐳋K������B
		biNormal = normalize(biNormal);
		//���[���h��Ԃ̖@�������߂�B
		normal = tangent * localNormal.x
			   + biNormal * localNormal.y
			   + normal * localNormal.z;
	}

	for (float i = 0; i < 4; i++)
	{
		//�X�y�L�������C�g�p�̏����B
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

	//�f�v�X�V���h�E�ǉ�
	//X����Y�̒l��0�ȏ�1�ȉ��ɂ���B
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
*@brief �V���h�E�}�b�v�V�F�[�_�[
*/
float4 PSShadowMain(VS_OUTPUT In) : COLOR
{
	float z = In.PosInProj.z / In.PosInProj.w;
	return float4(z, z, z, 1.0f);
}
/*!
 *@brief	�X�L�����胂�f���p�̃e�N�j�b�N�B
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
 *@brief	�X�L���Ȃ����f���p�̃e�N�j�b�N�B
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
*@brief	�V���h�E�}�b�v�`��p�̃e�N�j�b�N�B
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
*@brief	�V���h�E�}�b�v�Ȃ��̕`��p�̃e�N�j�b�N�B
*/
technique NoShadowSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSShadowMain(false);
		PixelShader = compile ps_3_0 PSShadowMain();
	}
};