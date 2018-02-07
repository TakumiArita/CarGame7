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
	//�N���A�������B
	clear.Init();
	//�R�[�X�p�X�������B
	courcePath.Init(edge);
	//mainRenderTarget.InitMainRenderTarget();
	//mainRenderTarget.InitQuadPrimitive();
}
void SceneManager::Update()
{
	//�}�b�v�X�V
	map.Update();
	//�N���A�e�N�X�`���̍X�V�B
	clearTexture.Update();
	//�v���C���[�̍X�V
	player.Update();
	//�J�����̎��_�̍X�V
    //toCameraPos = { 25.0f,7.0f,player.GetLookCamera() };  //�c��ʕ��L
	D3DXVECTOR3 targetPos = player.GetPosition();
	eyePos = targetPos;                         //�J�����̒����_�𒆐S�ɂ���B
	camera.SetLookatPt(targetPos);

	//�J���������_�ɍ��E�������B
	//camera.SetLookatPt(targetPos + D3DXVECTOR3( 0.0f,0.0f,player.GetLookCamera()));
	//�����_�ɍ��킹���J�����̈ʒu
	//camera.SetEyePt(eyePos);
	//�����_�����_�ɍ��E�������B
	//D3DXToRadian == sin,cos,tan�ȂǎO�p�֐��ɓn���Ƃ��͂��̊֐��������B
	camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 70.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//�㉺���ǉ��B
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, player.GetUpLookCamera(), sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//�㉺�Ȃ��B�����ʒu����̎��_�B
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 25.0f, 700.0f, sin(D3DXToRadian(player.GetLookCamera())) * 25.0f));
	//�{���̃J�����B
	//camera.SetEyePt(eyePos + D3DXVECTOR3(cos(D3DXToRadian(player.GetLookCamera())) * 5.0f, 7.0f, sin(D3DXToRadian(player.GetLookCamera())) * 5.0f));

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

}

void SceneManager::Draw()
{
	//�A���t�@�u�����f�B���OOFF
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//�}�b�v�̕`��
	map.Draw();
	//�A���t�@�u�����f�B���OON
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//���Z����
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	
	//�v���C���[�̕`��
	player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);
	player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(),false,false,true);
	//�A���t�@�u�����f�B���OOFF
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//player.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, false, true);

	//�V���h�E�}�b�v�`��B
	g_shadowmap.Draw();
	if (player.GetCirclingTimes() > 2)
	{
		clear.Draw();
	}
}


