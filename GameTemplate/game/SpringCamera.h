#pragma once
#include "SceneManager.h"
class SpringCamera
{
public:
	/*
	* @brief �R���X�g���N�^�B
	*/
	SpringCamera();
	/*
	* @brief �f�X�g���N�^�B
	*/
	~SpringCamera();

	/*
	* @brief �������B
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*
	* @brief �ڕW�ƂȂ钍���_��ݒ�B
	*/
	void SetPosition(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*
	* @brief �ڕW�ƂȂ鎋�_��ݒ�B
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*
	* @brief �����_��ݒ�B
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		//�G���[
		//m_camera.SetTarget(target);
		m_camera.SetLookatPt(target);
	}
	/*
	* @brief ���_��ݒ�B
	*/
	void SetPosition(const D3DXVECTOR3 position)
	{
		//�G���[
		//m_camera.SetPosition(position);
		m_camera.SetEyePt(position);
	}
	/*
	* @brief �����ʂ�ݒ�B
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*
	* @brief �J�����̉�]�s����擾�B
	*/
	const D3DXMATRIX& GetCameraRotation() const
	{
		//return m_camera.GetCameraRotation();
	}
	/*
	* @brief �����_���擾�B
	*/
	const D3DXVECTOR3& GetTarget() const
	{
		//return m_camera.GetTarget();
		//return scenemanager->GetTargetPos();
		return scenemanager->GetCamera().GetLookatPt();
	}
	/*
	* @brief ���_���擾�B
	*/
	const D3DXVECTOR3& GetPoswition() const
	{
		//�G���[
		//return m_camera.GetPosition();
		return scenemanager->GetCamera().GetEyePt();
	}
	/*
	* @brief �X�V�B
	*/
	void Update();
	/*
	* @brief �J�������擾�B
	*/
	const Camera* GetCamera() const
	{
		return &m_camera;
	}
	/*
	* @brief �΂˂̌�������ݒ�B
	* �l���傫���قǃJ�������x��ĕt���Ă���B
	*/
	void SetdampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*
	* @brief �J�������擾�B
	*/
	Camera* GetCamera()
	{
		return &m_camera;
	}
	void SetViewAngle(float angle)
	{
		//�G���[
		//m_camera.SetViewAngle(angle);
	}
	float GetViewAngle()
	{
		//�G���[
		//return m_camera.GetViewAngle();
	}
	/*
	* @brief �ڕW�ƂȂ钍���_���擾�B
	*/
	//const D3DXVECTOR3& GetTarget() const
	//{
	//	return m_target;
	//}
	/*
	* @brief �ڕW�ƂȂ鎋�_���擾�B
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*
	* @brief �΂˃J�����p�̃p�����[�^���N���A�B
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
		m_positionMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
	}
	/*
	* @brief �΂˃J�����̍X�V�����B
	* Update�֐�����Ă΂�Ă���B
	* �΂˃J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�̂Ƃ������g�p����B
	*/
	void UpdateSpringCamera();
	/*
	* @brief �J�����̍X�V�B
	* Update�֐�����Ă΂�Ă���B
	* �J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�̂Ƃ������g�p����B
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}
private:
	Camera       m_camera;                                                  //�J����
	D3DXVECTOR3  m_target = D3DXVECTOR3(NULL, NULL, NULL);                  //�ڕW�ƂȂ钍���_
	D3DXVECTOR3  m_position = D3DXVECTOR3(NULL, NULL, NULL);                //�ڕW�ƂȂ鎋�_
	D3DXVECTOR3  m_targetMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);          //�����_�̈ړ����x
	D3DXVECTOR3  m_positionMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);        //���_�̈ړ����x
	float        m_maxMoveSpeed = 0.0f;                                      //�ō��ړ����x
	float        m_targetDampingRate = 1.0f;                                 //�������B�@�l���傫���قǃJ�������x��Ă���
	float        m_dampingRate = 1.0f;                                       //������
	float        m_dampingRateVel = 0.0f;
};
//D3DXVECTOR3(NULL,NULL,NULL) == CVector3::Zero;
