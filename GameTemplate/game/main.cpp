/*!
 *@brief	�Q�[���e���v���[�g�B
 */
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Primitive.h"
#include "CCourcePath.h"
#include "game.h"
#include "myEngine\HID\Pad.h"
#include "CSoundEngine.h"
#include "Bloom.h"

Game* game;
SceneManager* scenemanager;
//RenderTarget* renderTarget;
ShadowMap*    g_shadowmap;
Pad*          pad;
CSoundEngine* soundEngine;
//Primitive*    quadPrimitive = new Primitive;
Primitive*    quadPrimitive;

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 ���C�������_�����O�^�[�Q�b�g���쐬����B
	//scenemanager->mainRenderTarget.InitMainRenderTarget();
	//18-3 �l�p�`�̔|���v���~�e�B�u���쐬�B
	//scenemanager->mainRenderTarget.InitQuadPrimitive();
	//18-3�A18-4 �V�F�[�_�[�����[�h�B
	//scenemanager->scenemanager->mainRenderTarget.LoadShaders();
	game = new Game;
	game->Start();

	scenemanager = new SceneManager;
	scenemanager->Init();
	//quadPrimitive = new Primitive;
	
	pad = new Pad;
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
	pad->Update();

	//OutputDebugString("Test");
	//MessageBox(NULL, "Test", "�ʒm", MB_OK);
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	//delete game;
	//delete scenemanager;
	//delete pad;
	//delete g_effectManager;
	//soundEngine->Release();
	//g_pd3dDevice->Release();
	//g_pD3D->Release();
}
