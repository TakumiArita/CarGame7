#pragma once

#include "myEngine\Physics\CharacterController.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	//�������B
	void Init();

	//�X�V�B
	void Update();

	//�`��
	void Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);

	//�|�W�V�����擾
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture;
	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;
private:
	CharacterController characterController; //�L�����N�^�[�R���g���[��
	SkinModel           m_skinmodel;
	SkinModelData       m_skinmodelData;
	D3DXVECTOR3         m_position;
	D3DXQUATERNION      m_rotation;
	D3DXVECTOR3         m_scale;
	Animation           m_animation;
	Light               m_light;

};

