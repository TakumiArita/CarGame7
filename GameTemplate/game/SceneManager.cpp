#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine\HID\Pad.h"
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	if (gamess != NULL)
	{
		delete gamess;
	}
	gamess = NULL;
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
	//�A�C�e���������B
	item.Init();
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
	//gamess = new CSoundSource;
	

	param.texturePath = "Mahouzin.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	particleemitter.Init(param);

}
void SceneManager::Update()
{
	if (GetAsyncKeyState(VK_SPACE) || pad->IsPress(pad->enButtonStart))
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
	//�A�C�e���̍X�V
	item.Update();
	//�v���C���[�̍X�V
	player.Update();

	//particle.Update();
	//particleemitter.Render(camera.GetViewMatrix(),camera.GetProjectionMatrix());

	//particleemitter.Update();
	//particle.Update();


	GameSound();
	if (gamess != NULL)
	{
		gamess->Update();
	}
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
	//�^�C�g���B
	if (Titleflag == false)
	{
		titletexture.TitleSound();
		scenesprite.TitleDraw();
		player.PlayerRelease();
		sprite.SaveGameTimeDraw();
	}
	//�^�C�g������J�ځB
	else if (Titleflag == true)
	{
		titletexture.TitleRelease();
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
		item.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
		//�A���t�@�u�����f�B���OOFF
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		particleemitter.Render(camera.GetViewMatrix(), camera.GetProjectionMatrix());
		//�V���h�E�}�b�v�`��B
		g_shadowmap.Draw();

		//�S�[���̃e�N�X�`���̕`��B
		if (player.GetCirclingTimes() > 2)
		{
			scenesprite.GoalDraw();
			GoalBetweenTitle++;
		}
		if (GoalBetweenTitle >= 100)
		{
			gametimetexture.SaveUpdate();
			Titleflag = false;
			GoalBetweenTitle = 0;
			GameSoundRelease();
		}
		//�X�^�[�g�̃e�N�X�`���̕`��B
		if (gametimetexture.GetGameTimer() > 0 && gametimetexture.GetGameTimer() <= 100)
		{
			scenesprite.StartDraw();
		}
		skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, false);
	}
}

void SceneManager::GameSound()
{

	if (Titleflag == true)
	{
		if (gamess == NULL)
		{
			gamess = new CSoundSource;
			gamess->Init("Assets/sound/holidays.wav");
			gamess->SetVolume(0.5f);
			gamess->Play(true);
		}
	}
}

void SceneManager::GameSoundRelease()
{
	if (gamess != NULL)
	{
		delete gamess;
	}
	gamess = NULL;
}
