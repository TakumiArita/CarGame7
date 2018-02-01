#include "stdafx.h"
#include "Player.h"
#include "SceneManager.h"
#include "myEngine/HID/Pad.h"
#include "CCourcePath.h"
//#include <math.h>

//#define ENABLE_ACCEL_SAMPLE		//���̒�`��L���ɂ���Ɖ����x�̃T���v�����L���ɂȂ�B

//////////////////////////////////////////////////////////////      ifndef�̎g�����B
////End��\������B
//#define End
////�L���ɂ���ƕ\���������́B
//#ifndef End
////�͈͂̏I���ɒ�`������́B
//#endif
//////////////////////////////////////////////////////////////

Player::Player()
{              
}

Player::~Player()
{
	if (normalMap != NULL) {
		//normalMap��NULL����Ȃ��Ȃ烍�[�h����Ă���̂ŉ������B
		normalMap->Release();
	}
}
	
void Player::Init()
{
	/*
	//���C�g�̏�����
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(2.707f, 50.0f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-2.707f, -50.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(-2.0f, 50.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(2.0f, -50.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	*/
	//���C�g�̏�����
	D3DXVECTOR4 v = D3DXVECTOR4(0.707f, -100.0f, -0.707f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);	//���K�����đ傫���P�̃x�N�g���ɕϊ����āA���������̃x�N�g���ɂ���B
															//w�v�f���܂ނ�4�v�f�̃x�N�g���Ő��K�����Ă��܂��̂ŁAD3DXVECTOR3�ɃL���X�g�A
	light.SetDiffuseLightDirection(0, v);

	v = { -0.707f, 100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(1, v);

	v = { -0.707f, -100.0f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(2, v);

	v = { 0.707f, -100.707f, -0.707f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	light.SetDiffuseLightDirection(3, v);

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	light.SetAmbientLight(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	
	//���f���̃��[�h
	modelData.LoadModelData("Assets/modelData/Car1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/Ringo1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/potion1.X", &animation);
	//modelData.LoadModelData("Assets/modelData/potion2.X", &animation);

	model.Init(&modelData);
	model.SetLight(&light);

	//�@���}�b�v�̃��[�h�B
	D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		//�@���}�b�v�p�̃e�N�X�`���B                                             //���͂Ȃ��B
		"Assets/model/C3.tga",
		&normalMap
	);
	//�L�����N�^�[�R���g���[���[�̏�����
	//characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 20.0f, 0.0f));

	//�R�[�X�p�X�̍��W�m�F�Ƀv���C���[�̍��W���g���B
	characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	//�d�͂̐ݒ�

	//characterController.SetGravity(-35.0f);
	characterController.SetGravity(-50.0f);
	//�Ԃ��~�܂��Ă鎞��
	stoptimer = 0;
	//�Ԃ̏�������
	accelerationtimer = 0;
	//�Ԃ̏����������s�̃^�C�}�[
	failuretimer = 0;
	//�J�����̌���������
	lookcamera = 0.0f;
	//�v���C���[�̏�����
	qcamera = 0.0f;

	//scenemanager->ccourcepath.SCourceEdge.startToEnd
	//scenemanager->ccourcepath.SCourceEdge scourceedge;
}

void Player::Update()
{
	//�p�b�h�̓��͂œ������B
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	D3DXVECTOR3 direction = GetPosition();
	D3DXVECTOR3 CCPListdirection;
	//�v���C���[��]�̏�����
	D3DXQUATERNION addRot;
	D3DXQuaternionIdentity(&addRot);

	//�J�����̉�]
	if (GetAsyncKeyState(VK_RIGHT)/* && lookcamera >= -10.0f  && lookcamera < 10.0f*/)
	{
		lookcamera -= 1.0f;
		if (GetAsyncKeyState('S'))
		{
			lookcamera -= 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) /*&& lookcamera > -10.0f && lookcamera <= 10.0f*/)
	{
		lookcamera += 1.0f;
		if (GetAsyncKeyState('S'))
		{
			lookcamera += 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_UP)/* && lookcamera >= -10.0f  && lookcamera < 10.0f*/)
	{
		uplookcamera += 1.0f;
		if (GetAsyncKeyState('S'))
		{
			uplookcamera += 1.5f;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) /*&& lookcamera > -10.0f && lookcamera <= 10.0f*/)
	{
		uplookcamera -= 1.0f;
		if (GetAsyncKeyState('S'))
		{
			uplookcamera -= 1.5f;
		}
	}

#ifndef ENABLE_ACCEL_SAMPLE 
	float accel = 0.025f;
	//�v���C���[�̉�]�X�V�B
	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-GetLookCamera()));

	//��//
	if (GetAsyncKeyState('W') || pad.IsPress(pad.enButtonB))
	{
		//�v���C���[�̑��x�B
		moveSpeed = D3DXVECTOR3(-cos(D3DXToRadian(GetLookCamera())) * 100.0f, -10.0f, -sin(D3DXToRadian(GetLookCamera())) * 100.0f);
	}
	//���C��R
	moveSpeed *= 0.95f;
	//moveSpeed *= 0.93f;
#else
	float	accel = 0.0f;
	if (pad.IsPress(pad.enButtonRB2)) {
		accel += 0.3f;
	}
	moveSpeed += moveDir * accel;
	//���C��R�B
	moveSpeed *= 0.98f;
#endif
	//�Ԃ��~�܂��Ă��鎞�ɉ����{�^������������
	if ( GetAsyncKeyState(VK_UP) || pad.IsPress(pad.enButtonB))
	{
		if (moveSpeed == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			stoptimer += 1;
		}

		//�����{�^���������ꂽ�̂��Z��
		if (stoptimer < 50 &&( pad.GetLStickYF() == true || pad.GetLStickXF() == true))
		{
			stoptimer = 0;
		}
		//�����{�^���������ꂽ�̂��͈͓�
		else if (stoptimer >= 50 && stoptimer <= 100 &&( pad.GetLStickYF() == true || pad.GetLStickXF() == true))
		{
			//�������Ă���
			if (accelerationtimer < 100)
			{
				moveSpeed.x *= 5.0f;
				moveSpeed.z *= 5.0f;
				accelerationtimer += 1;
			}
			//�������I�����
			else
			{
				accelerationtimer = 0;
				stoptimer = 0;
			}
		}
		//�����{�^���������ꂽ�̂�����
		else if (stoptimer > 100 )
		{
			failuretimer += 1;
			//���i���s�̏����J�n�B
			if (failuretimer <= 100)
			{
				//��]������
				if (GetIsOnGround() == true)
				{
					//�W�����v
					moveSpeed.y = 50.0f;
					//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
					characterController.Jump();
				}
				moveSpeed.x = 0.0f;
				moveSpeed.z = 0.0f;
			}
			//���i���s�̏����I���B
			else
			{
				failuretimer = 0;
				accelerationtimer = 0;
				stoptimer = 0;
			}
		}
	}
	if (!pad.IsPress(pad.enButtonB))
	{
		failuretimer = 0;
		accelerationtimer = 0;
		stoptimer = 0;
	}

	//�W�����v
	if (GetAsyncKeyState('P'))
	{
		if (GetIsOnGround() == true)
		{
			//�W�����v
			moveSpeed.y = 50.0f;
			//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
			characterController.Jump();
		}
	}

	//�����ʒu�ɖ߂�
	if (GetAsyncKeyState('O'))
	{
		characterController.SetPosition(D3DXVECTOR3(10.0f, 20.0f, 0.0f));
		lookcamera = 0.0f;
	}

	if (GetAsyncKeyState('J'))
	{
		if (GetIsOnGround() == true)
		{
			//�W�����v
			moveSpeed.y = 50.0f;
			//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
			characterController.Jump();
		}
	}

	//�L�����N�^���������x��ݒ�B
	characterController.SetMoveSpeed(moveSpeed);
	//�L�����N�^�R���g���[���[�����s�B
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), addRot, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//�p�b�h�̍X�V
	pad.Update();
	//�����x�N�g���𐳋K������B
	//D3DXVec3Normalize(&SecondmoveSpeed, &moveSpeed);
	int edgeNo = -1;
	float nearLen = 1000.0f;		//��ԋ߂��G�b�W�܂ł̋������i�[����ϐ��B
	for (int i = 0; i < scenemanager->courcePath.GetNumEdge(); i++)
	{
		//�R�[�X�p�X�̃G�b�W�̌���(�n�_����I�_�֌������G�b�W�̌���)
		D3DXVECTOR3 CListDirection = scenemanager->courcePath.GetCourceEdigeList(i).direction;
		StartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
		NormalStartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
		EndToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).endPos;
		NormalEndToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).endPos;
		D3DXVec3Normalize(&NormalStartToPlayerDirection, &StartToPlayerDirection);
		D3DXVec3Normalize(&NormalEndToPlayerDirection, &EndToPlayerDirection);
		//����
		if (D3DXVec3Dot(&NormalStartToPlayerDirection, &CListDirection) > 0 &&
			D3DXVec3Dot(&NormalEndToPlayerDirection, &-CListDirection) < 0) {
			//�v���C���[������\���̂���G�b�W�����������̂ŁA
			//�G�b�W��ɐ��������낵�āA��ԋ߂��G�b�W�𒲂ׂ�B
			//�@�@�G�b�W�̎n�_����v���C���[�Ɍ������x�N�g���Av1�����߂�B
			///StartToPlayerDirection = GetPosition() - scenemanager->courcePath.GetCourceEdigeList(i).startPos;
			//�A�@�@�ŋ��߂��x�N�g���ƁA�G�b�W�̕����x�N�g���Ƃ̓��ς��v�Z���āA
			//    �G�b�W��Ɏˉe����������t�����߂�B
			t = D3DXVec3Dot(&StartToPlayerDirection, &CListDirection);
			//�B�@�A�ŋ��߂��������ƃG�b�W�̕����x�N�g������Z���ăx�N�g���Av2�����߂�B
			v2 = t * CListDirection;
			//�C�@v1-v2���v�Z���āA�G�b�W�ɗ�����x�N�g����v3�����߂�B
			v3 = StartToPlayerDirection - v2;
			//�D�@v3�̒����𗘗p���āA��ԋ߂��G�b�W��������B   �ˉe(projection)
			float len = D3DXVec3Length(&v3);
			if (len < nearLen) {
				//���̃G�b�W�̂ق����߂��̂ōX�V����B
				edgeNo = i;
				nearLen = len;
			}
		}
		if (edgeNo != -1) {
			//��ԋ߂��G�b�W�̕������擾����B
			D3DXVECTOR3 CListDirection = scenemanager->courcePath.GetCourceEdigeList(i).direction;
			D3DXVECTOR3 moveDir;
			D3DXVec3Normalize(&moveDir, &moveSpeed);
			if (D3DXVec3Dot(&CListDirection, &moveDir) < 0) {
				MessageBox(NULL, "�t�����Ă܂��B", "�ʒm", MB_OK);
			}
		}

	}
}

void Player::Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec)
{
	model.Draw(&ViewMatrix, &ProjectionMatrix, shadowmapD, shadowmapR, Pspec);
}