#pragma once
#include "Map.h"
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "ShadowMap.h"
#include "MainRenderTarget.h"
#include "RenderTarget.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "SceneSprite.h"
#include "GoalTexture.h"
#include "StartTexture.h"
#include "GameTimeTexture.h"
#include "StartCountTexture.h"
#include "Sprite.h"
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
	bool GetTitleFlag()
	{
		return Titleflag;
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
	//�^�C�g���\��
	TitleTexture titletexture;
	//�X�^�[�gNo�̕\���B
	StartCountTexture startcounttexture;
	//�S�[���\��
	GoalTexture  goaltexture;
	//�X�^�[�g�̕\��
	StartTexture starttexture;
	//�^�C�g���A�S�[���Ȃǂ̃X�v���C�g�B
	SceneSprite  scenesprite;

	//���ԕ\��
	Sprite             sprite;
	GameTimeTexture    gametimetexture;
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

private:
	//���_
	D3DXVECTOR3 toCameraPos;
	//�J�����̒����_�𒆐S�ɂ���B
	D3DXVECTOR3 eyePos;          
	//�X�y�L�������C�g�p�̎��_
	D3DXVECTOR3 eyeR;
	//int gameTime;
	bool Titleflag = false;
};
extern SceneManager*  scenemanager;
extern ShadowMap      g_shadowmap;
extern 	RenderTarget* renderTarget;
extern 	Primitive*    quadPrimitive;


