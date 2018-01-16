#pragma once

#include "myEngine\Physics\CharacterController.h"
#include "myEngine\HID\Pad.h"
using namespace std;
class Player
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix, bool shadowmapD, bool shadowmapR, bool Pspec);

	//�|�W�V�����擾
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
	//�J������]�p�x
	float GetLookCamera()
	{
		return lookcamera;
	}
	//�v���C���[�ƃJ�����̉�]
	float GetQCamera()
	{
		return qcamera;
	}
	//��
	bool GetIsOnGround()
	{
		return characterController.IsOnGround();
	}
	bool GetIsJump()
	{
		return characterController.IsJump();
	}
	Light GetLight()
	{
		return light;
	}
	int GetStartToGoal()
	{
		return startToGoal;
	}
private:
	SkinModel           model;
	SkinModelData       modelData;
	Animation           animation;
	Light               light;               //���C�g
	Pad                 pad;                 //�p�b�h
	D3DXQUATERNION      rotation;            //��]
	CharacterController characterController; //�L�����N�^�[�R���g���[��
	float               movedirz = 0.0f;
	D3DXVECTOR3			moveDir = {-1.0f, 0.0f, 0.0f};	//�Ԃ̐i�s�����B
	int startToGoal = 0;
	//�~�܂��Ă���^�C�}�[
	int stoptimer;
	//�����^�C�}�[
	int accelerationtimer;
	//���s�����^�C�}�[
	int failuretimer;
	//�J�����̌���
	float lookcamera;
	//�v���C���[�̉�]
	float qcamera;
	//�@���}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;
};
