#pragma once

#include "myEngine\Physics\CharacterController.h"
#include "CSoundSource.h"
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
	void PlayerRelease();

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
	//�����
	int GetCirclingTimes()
	{
		return CirclingTimes;
	}
	int GetGameTimer()
	{
		return gameTime0;
	}
	void SetSoundflag(bool flg)
	{
		Soundflag = flg;
	}
	void SetSound2flag(bool flg)
	{
		Sound2flag = flg;
	}
private:
	SkinModel           model;
	SkinModelData       modelData;
	Animation           animation;
	Light               light;               //���C�g
	D3DXQUATERNION      rotation;            //��]
	CharacterController characterController; //�L�����N�^�[�R���g���[��


	D3DXVECTOR3 StartToPlayerDirection;      //�m�[�h(�n�_)����v���C���[�̃x�N�g���B
	D3DXVECTOR3 NormalStartToPlayerDirection;//�m�[�h(�n�_)����v���C���[�̕����x�N�g���B
	D3DXVECTOR3 EndToPlayerDirection;        //�m�[�h(�I�_)����v���C���[�̃x�N�g���B
	D3DXVECTOR3 NormalEndToPlayerDirection;  //�m�[�h(�I�_)����v���C���[�̕����x�N�g���B
	//D3DXVECTOR3 FirstStartToPlayerDirection;        //�Ō�̃m�[�h����v���C���[�Ɍ������x�N�g���B
	//D3DXVECTOR3 NormalFirstStartToPlayerDirection;  //�Ō�̃m�[�h����v���C���[�Ɍ������x�N�g���B
	//D3DXVECTOR3 LastEndToPlayerDirection;          //�Ō�̃m�[�h����v���C���[�Ɍ������x�N�g���B
	//D3DXVECTOR3 NormalLastEndToPlayerDirection;    //�Ō�̃m�[�h����v���C���[�Ɍ������x�N�g���B

	D3DXVECTOR3 v2;          //���ƃG�b�W�̕����x�N�g������Z�B
	D3DXVECTOR3 v3;                  //�G�b�W�ɗ�����x�N�g���B
	float t;                           //v1�ƁA�G�b�W�̕����x�N�g���Ƃ̓��ς��v�Z���āA�G�b�W��Ɏˉe���������B

	float               movedirz = 0.0f;
	D3DXVECTOR3			moveDir = {-1.0f, 0.0f, 0.0f};	//�Ԃ̐i�s�����B
	//�~�܂��Ă���^�C�}�[
	int stoptimer;
	//�Q�[���̃^�C�}�[
	float gameTime0;
	//�����^�C�}�[
	int accelerationtimer;
	//���s�����^�C�}�[
	int failuretimer;
	//�J�����̌���
	float lookcamera;
	//�v���C���[�̉�]
	float qcamera;
	//�����
	int CirclingTimes = 0;
	//�G�b�W�̃t���O�ŏ��B
	bool firstEdgeNoFlag = false;
	//�G�b�W�̃t���O�Ō�B
	bool lastEdgeNoFlag = false;
	//�@���}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;

	bool Soundflag = false;
	bool Sound2flag = false;
	bool keyflag = false;
	bool fallflag = false;
	int playerKeyflag = 0;

	CSoundSource* ss = NULL;     //�T�E���h
};
