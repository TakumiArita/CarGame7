#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//�}�b�v�������B
	map.Init();
	//�J�����������B
	camera.Init();
	//���_�ݒ�
	//toCameraPos = { 15.0f,7.0f,0.0f };  //�c���
	//toCameraPos = { 25.0f,7.0f,0.0f };  //�c��ʕ��L
	toCameraPos = { 25.0f,7.0f,0.0f };  //�c��ʕ��L
	//�v���C���[�������B
	player.Init();
	//�V���h�E�}�b�v�������B
	g_shadowmap.Init();
	//�X�v���C�g�̏������B
	scenesprite.Init();
	//�Q�[�����Ԃ̏������B
	sprite.Init();
	//�R�[�X�p�X�������B
	courcePath.Init(edge);
	//mainRenderTarget.InitMainRenderTarget();
	//mainRenderTarget.InitQuadPrimitive();
	//gameTime = -100;
	//�w�i�������B
	skybox.Init();
	//�T�E���h�G���W���������B
	soundEngine.Init();
	ss = new CSoundSource;

}
void SceneManager::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		Titleflag = true;
	}
	//�}�b�v�X�V
	map.Update();
	//�^�C�g���̃e�N�X�`���̍X�V�B
	titletexture.Update();
	//�X�^�[�g��No�e�N�X�`���̍X�V�B
	startcounttexture.Update();
	//�X�^�[�g�̃e�N�X�`���̕\���B
	starttexture.Update();
	//�S�[���̃e�N�X�`���̍X�V�B
	goaltexture.Update();
	//�Q�[�����Ԃ̍X�V
	gametimetexture.Update();
	//����񐔂̍X�V
	roadaroundfrequencytexture.Update();
	//�v���C���[�̍X�V
	player.Update();
	//soundSource.Update();
	//if (Titleflag == true)
	//{
	//	if (soundtime <= 0)
	//	{
	//		ss = new CSoundSource;
	//		ss->Init("Assets/sound/se_maoudamashii_effect08.wav");
	//		ss->SetVolume(0.1f);
	//		ss->Play(false);
	//	}
	//	soundtime += 1;
	//	if(soundtime >= 80)
	//	{
	//		soundtime = 0;
	//	}

	//}

	//if (ss != NULL)
	//{
	//	ss->Update();
	//}

	soundSource.Update();

	D3DXVECTOR3 targetPos = player.GetPosition();
	eyePos = targetPos;                         //�J�����̒����_�𒆐S�ɂ���B
	camera.SetLookatPt(targetPos);
	//�J���������_�ɍ��E�������B
	//camera.SetLookatPt(targetPos + D3DXVECTOR3( 0.0f,0.0f,player.GetLookCamera()));
	//�����_�ɍ��킹���J�����̈ʒu
	//camera.SetEyePt(eyePos);
	//�����_�����_�ɍ��E�������B
	//D3DXToRadian == sin,cos,tan�ȂǎO�p�֐��ɓn���Ƃ��͂��̊֐��������B
	//�㉺�Ȃ��B�����ʒu����̎��_�B	
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 70.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	
	//�{���̃J�����B
	camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 10.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	
	eyeR = (camera.GetEyePt());
	//�J�����̍X�V
	camera.Update();

	//�V���h�E�}�b�v�X�V�B
	g_shadowmap.SetLightViewPosition(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y + 25.0f, player.GetPosition().z));
	g_shadowmap.SetLightViewTarget(D3DXVECTOR3(player.GetPosition().x, player.GetPosition().y, player.GetPosition().z));
	g_shadowmap.Update();
	/*
	mainrendertarget.InitMainRenderTarget();
	mainrendertarget.InitQuadPrimitive();
	mainrendertarget.LoadShaders();
	mainrendertarget.CopyMainRTToCurrentRT();
	*/
	//gameTime++;
	skybox.Update();
}

void SceneManager::Draw()
{
	if (Titleflag == false)
	{
		scenesprite.TitleDraw();
		titletexture.TitleSound();

	}
	else if (Titleflag == true)
	{

		//�A���t�@�u�����f�B���OOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//�}�b�v�̕`��
		map.Draw();
		//�X�v���C�g�̕`��
		sprite.Draw();
		//�A���t�@�u�����f�B���OON
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//���Z����
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//�v���C���[�̕`��
		player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
		player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
		//�A���t�@�u�����f�B���OOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);

		//�V���h�E�}�b�v�`��B
		g_shadowmap.Draw();

		//�S�[���̃e�N�X�`���̕`��B
		if (player.GetCirclingTimes() > 2)
		{
			scenesprite.GoalDraw();
		}
		//�X�^�[�g�̃e�N�X�`���̕`��B
		if (gametimetexture.GetGameTimer() > 0 && gametimetexture.GetGameTimer() <= 100)
		{
			scenesprite.StartDraw();
		}
		skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, false);
	}
}