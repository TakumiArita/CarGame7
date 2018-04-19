#pragma once
#include "Map.h"
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Item.h"
#include "ShadowMap.h"
#include "MainRenderTarget.h"
#include "RenderTarget.h"
#include "Primitive.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "CCourcePath.h"
#include "SceneSprite.h"
#include "GoalTexture.h"
#include "StartTexture.h"
#include "GameTimeTexture.h"
#include "StartCountTexture.h"
#include "RoadAroundFrequencyTexture.h"
#include "Sprite.h"
#include "SkyBox.h"
#include "CSoundSource.h"
#include "CSoundEngine.h"
#include "myEngine\HID\Pad.h"
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
	//�Q�[�����̉�
	void GameSound();
	//�Q�[�����̉��̃����[�X
	void GameSoundRelease();
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
	//�A�C�e��
	Item              item;
	//�}�b�v
	Map               map;
	//�w�i
	SkyBox            skybox;
	//�^�C�g���\���B
	TitleTexture titletexture;
	//�X�^�[�gNo�̕\���B
	StartCountTexture startcounttexture;
	//�S�[���\���B
	GoalTexture  goaltexture;
	//�X�^�[�g�̕\���B
	StartTexture starttexture;
	//����񐔂̕\���B
	RoadAroundFrequencyTexture roadaroundfrequencytexture;
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
	//�p�[�e�B�N��
	Particle particle;
	//�p�[�e�B�N���G�~�b�^
	ParticleEmitter particleemitter;
	SParticleEmitParameter param;
	//�R�[�X�p�X
	CCourcePath        courcePath;
	CCourcePath::SCourceEdge  edge;

	//�T�E���h
	CSoundEngine soundEngine;
	CSoundSource soundSource;
	CSoundSource* gamess = NULL;     //�T�E���h

private:
	//���_
	D3DXVECTOR3 toCameraPos;
	//�J�����̒����_�𒆐S�ɂ���B
	D3DXVECTOR3 eyePos;          
	//�X�y�L�������C�g�p�̎��_
	D3DXVECTOR3 eyeR;
	//int gameTime;
	bool Titleflag = false;
	bool S_flag = false;
	int soundtime = 0;
	int GoalBetweenTitle = 0;
};
extern SceneManager*  scenemanager;
extern ShadowMap      g_shadowmap;
extern RenderTarget*  renderTarget;
extern Primitive*     quadPrimitive;
extern Pad*           pad;