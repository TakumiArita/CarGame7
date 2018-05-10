#include "stdafx.h"
#include "Item.h"
#include "SceneManager.h"


Item::Item()
{
}

Item::~Item()
{
}

void Item::Init()
{
	//���C�g�̏������B
	//D3DXVECTOR4 v = D3DXVECTOR4(0.707f, -100.0f, -0.707f, 1.0f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);   //���K�����đ傫���P�̃x�N�g���ɕϊ����āA���������̃x�N�g���ɂ���B													 //w�v�f���܂ނ�4�v�f�̃x�N�g���Ő��K�����Ă��܂��̂ŁAD3DXVECTOR3�ɃL���X�g�B
	//light.SetDiffuseLightDirection(0, v);

	//v = { -0.707f, 100.707f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(1, v);

	//v = { -0.707f, -100.0f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(2, v);

	//v = { 0.707f, -100.707f, -0.707f, 1.0f };
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//light.SetDiffuseLightDirection(3, v);

	//light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	//light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	//light.SetDiffuseLightColor(2, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	//light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));

	//���f���̃��[�h�B
	modelData.LoadModelData("Assets/modelData/potion2.X", &animation);
	//modelData.LoadModelData("Assets/modelData/Ringo1.X", &animation);

	model.Init(&modelData);
	model.SetLight(&light);

	//�L�����N�^�[�R���g���[���[�̏������B
	characterController.Init(0.3f, 1.0f, D3DXVECTOR3(0.0f, 5.0f, 50.0f));
	//�d��
	characterController.SetGravity(-50.0f);

	playerToItem.x = scenemanager->GetPlayer().GetPosition().x - GetPosition().x;
	playerToItem.z = scenemanager->GetPlayer().GetPosition().z - GetPosition().z;
	//playerToItem = GetPosition() - scenemanager->player.GetPosition();


}

void Item::Update()
{
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	//�L�����N�^���������x��ݒ�B
	characterController.SetMoveSpeed(moveSpeed);
	
	playerToItem.x = scenemanager->GetPlayer().GetPosition().x - GetPosition().x;
	playerToItem.z = scenemanager->GetPlayer().GetPosition().z - GetPosition().z;
	//playerToItem = GetPosition() - scenemanager->player.GetPosition();
	if (itemEffectTime > 0)
	{
		itemEffectTime--;
	}
	//�L�����N�^�[�R���g���[���[�����s�B
	characterController.Execute();
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Item::Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec)
{
	if (itemEffectTime <= 0)
	{
		itemFlag = false;
		model.Draw(&ViewMatrix, &ProjectionMatrix, shadowmapD, shadowmapR, Pspec);
		if ((playerToItem.x <= 1.5f && playerToItem.x >= -1.5f)  )
		{
			if ((playerToItem.z <= 1.5f && playerToItem.z >= -1.5f))
			{
				itemEffectTime = 50;
				itemFlag = true;
			}
		}
	}
}