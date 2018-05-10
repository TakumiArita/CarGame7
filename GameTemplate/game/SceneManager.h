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
#include "Bloom.h"
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



public:
	/*
	*@brief	�J�������擾�B
	 return �J�����̕ϐ�
	*/
	//Camera* GetCamera()
	//{
	//	return &camera;
	//}
	Camera& GetCamera()
	{
		return camera;
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

	//�v���C���[�̃Q�b�^�[�B
	Player& GetPlayer()
	{
		return player;
	}
	Item& GetItem()
	{
		return item;
	}
	//Map& GetMap()
	//{
	//	return map;
	//}

	//SkyBox& GetSkyBox()
	//{
	//	return skybox;
	//}


	//�^�C�g���\���̃Q�b�^�[�B
	TitleTexture& GetTitleTexture()
	{
		return titletexture;
	}
	//�X�^�[�g�̃J�E���g�_�E���̕\���̃Q�b�^�[�B
	StartCountTexture& GetStartCountTexture()
	{
		return startcounttexture;
	}
	//�S�[���̕\���̃Q�b�^�[�B
	GoalTexture& GetGoalTexture()
	{
		return goaltexture;
	}
	//�X�^�[�g�̕\���̃Q�b�^�[�B
	StartTexture GetStartTexture()
	{
		return starttexture;
	}
	//����񐔂̕\���̃Q�b�^�[�B
	RoadAroundFrequencyTexture& GetRoadAroundFrequencyTexture()
	{
		return roadaroundfrequencytexture;
	}
	//���Ԃ̕\���̃Q�b�^�[�B
	GameTimeTexture& GetGameTimeTexture()
	{
		return gametimetexture;
	}
	//�V���h�E�}�b�v�̃Q�b�^�[�B
	ShadowMap& GetShadowMap()
	{
		return shadowmap;
	}
	//�����_�[�^�[�Q�b�g�̃Q�b�^�[�B
	RenderTarget& GetRenderTarget()
	{
		return renderTarget;
	}
	//���C�������_�[�^�[�Q�b�g�̃Q�b�^�[�B
	//MainRenderTarget& GetMainRenderTarget()
	//{
	//	return mainRenderTarget;
	//}
	////�v���~�e�B�u�̃Q�b�^�[�B
	//Primitive& GetPrimitive()
	//{
	//	return quadPrimitive
	//}
	////�p�[�e�B�N���̃Q�b�^�[�B
	//Particle& GetParticle()
	//{
	//	return particle;
	//}

	////�p�[�e�B�N���G�~�b�^�̃Q�b�^�[�B
	//ParticleEmitter& GetParticleEmitter()
	//{
	//	return particleemitter;
	//}
	////�p�[�e�B�N���G�~�b�^�̃p�����[�^�̃Q�b�^�[�B

	//SParticleEmitParameter& GetSParticleEmitParameter()
	//{
	//	return param;
	//}
	//�R�[�X�p�X�̃Q�b�^�[�B
	CCourcePath& GetCCourcePath()
	{
		return courcePath;
	}
	////�R�[�X�p�X�̃G�b�W�̃Q�b�^�[�B
	//CCourcePath::SCourceEdge& GetEdge()
	//{
	//	return edge;
	//}

	//�u���[���̃Q�b�^�[�B
	Bloom& GetBloom()
	{
		return bloom;
	}

	//�T�E���h�̃G���W��
	CSoundEngine& GetCSoundEngine()
	{
		return soundEngine;
	}

	//�T�E���h�̃\�[�X�̃|�C���^�B
	CSoundSource* GetCSoundSourcePointer()
	{
		return titleBgm;
	}

private:
	/*�C���X�^���X*/
	Player                     player;	        			   //�v���C���[

	Item                       item;                           //�A�C�e��

	Map                        map;							   //�}�b�v
	
	SkyBox                     skybox;						   //�w�i

	TitleTexture               titletexture;	               //�^�C�g���\���B
	
	StartCountTexture          startcounttexture;              //�X�^�[�gNo�̕\���B

	GoalTexture                goaltexture;                    //�S�[���\���B
												
	StartTexture               starttexture;                   //�X�^�[�g�̕\���B
												 
	RoadAroundFrequencyTexture roadaroundfrequencytexture;     //����񐔂̕\���B

	GameTimeTexture            gametimetexture;                //���Ԃ̕\���B


	SceneSprite                scenesprite;		  			   //�V�[����p�̃X�v���C�g�B
	Sprite                     sprite;                         //�V�[���ȊO�̃X�v���C�g�B

	Camera                     camera;						   //�J����
	
	ShadowMap                  shadowmap;					   //�V���h�E�}�b�v
	
	RenderTarget               renderTarget;				   //�����_�[�^�[�Q�b�g

	MainRenderTarget           mainRenderTarget;			   //���C�������_�[�^�[�Q�b�g
	
	Primitive                  quadPrimitive;				   //�v���~�e�B�u
	
	Particle                   particle;     				   //�p�[�e�B�N��

	ParticleEmitter            particleemitter;				   //�p�[�e�B�N���G�~�b�^
	
	SParticleEmitParameter     param;                          //�p�[�e�B�N���G�~�b�^�̃p�����[�^�̃Q�b�^�[�B
															   
	CCourcePath                courcePath;					   //�R�[�X�p�X
	
	CCourcePath::SCourceEdge   edge;                           //�R�[�X�p�X�̃G�b�W�B

	Bloom                      bloom;                          //�u���[���B
	


	CSoundEngine               soundEngine;                    //�T�E���h�̃G���W���B
	CSoundSource*              titleBgm = NULL;                  //�T�E���h�̃\�[�X�̃|�C���^�B


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

	//�u���[���p�̃X�v���C�g�B
	LPD3DXSPRITE bloomSprite;

};
extern SceneManager*  scenemanager;
extern ShadowMap*     g_shadowmap;
//extern RenderTarget*  renderTarget;
extern Primitive*     quadPrimitive;
extern Pad*           pad;