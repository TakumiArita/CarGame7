#pragma once
#include "Map.h"
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "ShadowMap.h"
#include "MainRenderTarget.h"
#include "RenderTarget.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "Clear.h"
#include "ClearTexture.h"
//#include "locationInfo.h"

class SceneManager
{
public:
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	/*
	*@brief	�J�������擾�B
	 return �J�����̕ϐ�
	*/
	Camera* GetCamera()
	{
		return &camera;
	}
	/*
	*@brief �J�����̒����_���擾�B
	return  �J�����̒����_
	*/
	D3DXVECTOR3 GetEyePos()
	{
		return eyePos;
	}
	D3DXVECTOR3 GetEyeR()
	{
		return eyeR;
	}
	////�J�����̎��_�̃Z�b�^�[�B
	//D3DXVECTOR3 SetToCameraPos(D3DXVECTOR3 toCameraPos);
	////�J�����̎��_�̃Q�b�^�[�B
	//D3DXVECTOR3 GetToCameraPos()
	//{
	//	return toCameraPos;
	//}

	//�J����
	Camera            camera;
	//�v���C���[
	Player            player;
	//�}�b�v
	Map                map;
	Clear              clear;
	ClearTexture       clearTexture;
	//�V���h�E�}�b�v
	ShadowMap          shadowmap;
	//�����_�[�^�[�Q�b�g
	RenderTarget       renderTarget;
	//���C�������_�[�^�[�Q�b�g
	MainRenderTarget mainRenderTarget;
	//�v���~�e�B�u
	Primitive quadPrimitive;
	//�R�[�X�p�X
	CCourcePath        courcePath;
	CCourcePath::SCourceEdge  edge;
	//SCourceEdge        scourceedge;
private:
	//���_
	D3DXVECTOR3 toCameraPos;
	//�J�����̒����_�𒆐S�ɂ���B
	D3DXVECTOR3 eyePos;          
	//�X�y�L�������C�g�p�̎��_
	D3DXVECTOR3 eyeR;

};
extern SceneManager*  scenemanager;
extern ShadowMap      g_shadowmap;
extern 	RenderTarget* renderTarget;
extern 	Primitive*    quadPrimitive;


