#pragma once
#include "SceneManager.h"
class SpringCamera
{
public:
	/*
	* @brief コンストラクタ。
	*/
	SpringCamera();
	/*
	* @brief デストラクタ。
	*/
	~SpringCamera();

	/*
	* @brief 初期化。
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*
	* @brief 目標となる注視点を設定。
	*/
	void SetPosition(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*
	* @brief 目標となる視点を設定。
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*
	* @brief 注視点を設定。
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		//エラー
		//m_camera.SetTarget(target);
		m_camera.SetLookatPt(target);
	}
	/*
	* @brief 視点を設定。
	*/
	void SetPosition(const D3DXVECTOR3 position)
	{
		//エラー
		//m_camera.SetPosition(position);
		m_camera.SetEyePt(position);
	}
	/*
	* @brief 遠平面を設定。
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*
	* @brief カメラの回転行列を取得。
	*/
	const D3DXMATRIX& GetCameraRotation() const
	{
		//return m_camera.GetCameraRotation();
	}
	/*
	* @brief 注視点を取得。
	*/
	const D3DXVECTOR3& GetTarget() const
	{
		//return m_camera.GetTarget();
		//return scenemanager->GetTargetPos();
		return scenemanager->GetCamera().GetLookatPt();
	}
	/*
	* @brief 視点を取得。
	*/
	const D3DXVECTOR3& GetPoswition() const
	{
		//エラー
		//return m_camera.GetPosition();
		return scenemanager->GetCamera().GetEyePt();
	}
	/*
	* @brief 更新。
	*/
	void Update();
	/*
	* @brief カメラを取得。
	*/
	const Camera* GetCamera() const
	{
		return &m_camera;
	}
	/*
	* @brief ばねの減衰率を設定。
	* 値が大きいほどカメラが遅れて付いてくる。
	*/
	void SetdampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*
	* @brief カメラを取得。
	*/
	Camera* GetCamera()
	{
		return &m_camera;
	}
	void SetViewAngle(float angle)
	{
		//エラー
		//m_camera.SetViewAngle(angle);
	}
	float GetViewAngle()
	{
		//エラー
		//return m_camera.GetViewAngle();
	}
	/*
	* @brief 目標となる注視点を取得。
	*/
	//const D3DXVECTOR3& GetTarget() const
	//{
	//	return m_target;
	//}
	/*
	* @brief 目標となる視点を取得。
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*
	* @brief ばねカメラ用のパラメータをクリア。
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
		m_positionMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
	}
	/*
	* @brief ばねカメラの更新処理。
	* Update関数から呼ばれている。
	* ばねカメラの更新処理だけ個別で呼びたいなどの特殊なケースのときだけ使用する。
	*/
	void UpdateSpringCamera();
	/*
	* @brief カメラの更新。
	* Update関数から呼ばれている。
	* カメラの更新処理だけ個別で呼びたいなどの特殊なケースのときだけ使用する。
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}
private:
	Camera       m_camera;                                                  //カメラ
	D3DXVECTOR3  m_target = D3DXVECTOR3(NULL, NULL, NULL);                  //目標となる注視点
	D3DXVECTOR3  m_position = D3DXVECTOR3(NULL, NULL, NULL);                //目標となる視点
	D3DXVECTOR3  m_targetMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);          //注視点の移動速度
	D3DXVECTOR3  m_positionMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);        //視点の移動速度
	float        m_maxMoveSpeed = 0.0f;                                      //最高移動速度
	float        m_targetDampingRate = 1.0f;                                 //減衰率。　値が大きいほどカメラが遅れてくる
	float        m_dampingRate = 1.0f;                                       //減衰率
	float        m_dampingRateVel = 0.0f;
};
//D3DXVECTOR3(NULL,NULL,NULL) == CVector3::Zero;
