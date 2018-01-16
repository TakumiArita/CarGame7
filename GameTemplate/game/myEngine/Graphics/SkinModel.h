/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "myEngine/Graphics/Animation.h"
#include "ShadowMap.h"


class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	�X�L�����f��
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	������
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	�`��B
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);
	
	/*!
	*@brief	���[���h�s����X�V�B
	*@details
	* ���CMotion�N���X�Ɉړ������܂��B
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale,const D3DXVECTOR4& setambientlight);
	/*!
	*@brief	���C�g��ݒ�B
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	/*!
	*@brief	�I���W�i�����b�V���̐擪���擾����B
	*/
	LPD3DXMESH GetOrgMeshFirst();

	/*!
	*@brief  �@���}�b�v��ݒ�B
	*/
	void SetNormalMap(LPDIRECT3DTEXTURE9 normalMap)
	{
		this->normalMap = normalMap;
	}
private:
	D3DXMATRIX			worldMatrix;				//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;				//!<��]�s��B
	SkinModelData*		skinModelData = nullptr;	//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect = nullptr;			//!<�G�t�F�N�g�B
	Animation			animation;					//!<�A�j���[�V�����B
	Light*				light = nullptr;			//!<���C�g�B

	LPDIRECT3DTEXTURE9 normalMap = NULL;            //�@���}�b�v
};