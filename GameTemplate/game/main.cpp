/*!
 *@brief	�Q�[���e���v���[�g�B
 */
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "game.h"

Game* game;
SceneManager* scenemanager;
RenderTarget* renderTarget;
ShadowMap     g_shadowmap;

/*
//-----------------------------------------------------------------------------
// �|����`��B
//-----------------------------------------------------------------------------
void DrawQuadPrimitive()
{
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
														//����͐擪����ǂݍ��ނ̂�0�ł����B
		quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
}
*/
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 ���C�������_�����O�^�[�Q�b�g���쐬����B
	//scenemanager->mainRenderTarget.InitMainRenderTarget();
	//18-3 �l�p�`�̔|���v���~�e�B�u���쐬�B
	//scenemanager->scenemanager->mainRenderTarget.InitQuadPrimitive();
	//18-3�A18-4 �V�F�[�_�[�����[�h�B
	//scenemanager->scenemanager->mainRenderTarget.LoadShaders();

	game = new Game;
	game->Start();

	scenemanager = new SceneManager;
	scenemanager->Init();
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	game->Draw();
	scenemanager->Draw();

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	game->Update();
	scenemanager->Update();
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	delete game;
	delete scenemanager;
	delete g_effectManager;
	//scenemanager->mainrendertarget.GetTerminate();
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
