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
	float GetUpLookCamera()
	{
		return uplookcamera;
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
	D3DXVECTOR3 StartToPlayerDirection;      //�m�[�h(�n�_)����v���C���[�̃x�N�g���B
	D3DXVECTOR3 NormalStartToPlayerDirection;//�m�[�h(�n�_)����v���C���[�̕����x�N�g���B
	D3DXVECTOR3 EndToPlayerDirection;        //�m�[�h(�I�_)����v���C���[�̃x�N�g���B
	D3DXVECTOR3 NormalEndToPlayerDirection;  //�m�[�h(�I�_)����v���C���[�̕����x�N�g���B
	D3DXVECTOR3 v2;          //���ƃG�b�W�̕����x�N�g������Z�B
	D3DXVECTOR3 v3;                  //�G�b�W�ɗ�����x�N�g���B
	float t;                           //v1�ƁA�G�b�W�̕����x�N�g���Ƃ̓��ς��v�Z���āA�G�b�W��Ɏˉe���������B

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
	float uplookcamera;
	//�v���C���[�̉�]
	float qcamera;
	//�@���}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;
};
