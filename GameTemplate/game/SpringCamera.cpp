#include "stdafx.h"
#include "SpringCamera.h"


//namespace M_SpringCamera {
	namespace {
		float dampingK = 35.0f;
		float CalcSpringScalar(
			float positionNow,
			float positionTarget,
			float& moveSpeed)
		{
			//float deltaTime = min(1.0f / 30.0f, GameTime(), GameFrameDeltaTime());
			float deltaTime = min(1.0f / 30.0f, 1.0f / 60.0f);


			float dampingRate = 0.2f;
			float distance;
			distance = positionTarget - positionNow;
			if (fabsf(distance) < FLT_EPSILON) {
				moveSpeed = 0.0f;
				return positionTarget;
			}
			float originalDir = distance;
			originalDir /= fabsf(distance);
			float springAccel;
			springAccel = distance;

			float t = dampingK / (2.0f * dampingRate);
			float springK = t * t;
			springAccel *= springK;
			//加速度を決定。
			float vt = moveSpeed;
			vt *= dampingK;
			springAccel -= vt;
			springAccel *= deltaTime;
			moveSpeed += springAccel;

			float newPos = positionNow;
			float addPos = moveSpeed;
			addPos *= deltaTime;
			newPos += addPos;
			vt = positionTarget - newPos;
			if (fabsf(vt) < FLT_EPSILON) {
				//目標座標まで移動完了した。
				newPos = positionTarget;
				moveSpeed = 0.0f;
			}
			else {
				vt /= fabsf(vt);
				if (vt * originalDir < 0.0f) {
					//目標座標を超えた。
					newPos = positionTarget;
					moveSpeed = 0.0f;
				}
			}
			return newPos;

		}
		/*!
		* @brief  ばね減衰を利用して、現在の位置、目標となる位置、速度、加速度から新しい位置を計算する。
		*/
		D3DXVECTOR3 CaloSpringVector(
			const D3DXVECTOR3& positionNow,
			const D3DXVECTOR3& positionTarget,
			D3DXVECTOR3& moveSpeed,
			float maxMoveSpeed,
			float dampingRate
		)
		{
			float deltaTime = min(1.0f / 30.0f, 1.0f / 60.0f);   //?
			//現在の位置と目標の位置の差分を求める。
			D3DXVECTOR3 distance;
			///distance.Subtract(positionTarget, positionNow);
			D3DXVec3Subtract(&distance, &positionTarget, &positionNow);

			D3DXVECTOR3 originalDir = distance;
			///originalDir.Normalize();
			D3DXVec3Normalize(&originalDir,&originalDir);
			D3DXVECTOR3 springAccel;
			springAccel = distance;

			float t = dampingK / (2.0f * dampingRate);
			float springK = t * t;
			///springAccel.Scale(springK);
			D3DXVec3Scale(&springAccel, &D3DXVECTOR3(springK, springK, springK),NULL);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//加速度を決定。
			D3DXVECTOR3 vt = moveSpeed;
			///vt.Scale(dampingK);
			D3DXVec3Scale(&vt, &D3DXVECTOR3(dampingK, dampingK, dampingK), NULL);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///springAccel.Subtract(vt);
			D3DXVec3Subtract(&springAccel, &vt, NULL);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////


			///springAccel.Scale(deltaTime);
			D3DXVec3Scale(&springAccel, &D3DXVECTOR3(deltaTime, deltaTime, deltaTime), NULL);
			///moveSpeed.Add(springAccel);
			D3DXVec3Add(&moveSpeed, &springAccel, NULL);
			
			if (D3DXVec3LengthSq(&moveSpeed) > maxMoveSpeed * maxMoveSpeed)
			{
				//最高速度より速くなってしまった。
				///moveSpeed.Normalize();
				D3DXVec3Normalize(&moveSpeed, &moveSpeed);
				///moveSpeed.Scale(maxMoveSpeed);
				D3DXVec3Scale(&moveSpeed, &D3DXVECTOR3(maxMoveSpeed, maxMoveSpeed, maxMoveSpeed), NULL);
			}
			
			D3DXVECTOR3 newPos = positionNow;
			D3DXVECTOR3 addPos = moveSpeed;
			///addPos.Scale(deltaTime);
			D3DXVec3Scale(&addPos, &D3DXVECTOR3(deltaTime, deltaTime, deltaTime), NULL);
			///newpos.Add(addPos);
			D3DXVec3Add(&newPos, &addPos, NULL);
			///vt.Subtract(positionTarget, newPos);
			D3DXVec3Subtract(&vt, &positionTarget, &positionNow);
			///vt.Normalize();
			D3DXVec3Normalize(&vt, &vt);
			if (/*vt.Dot(originalDir)*/D3DXVec3Dot(&vt, &originalDir) < 0.0f) {
				//目標座標を超えた。
				newPos = positionTarget;
				moveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
			}
			return newPos;
		}
	}
	/*!
	* @brief  コンストラクタ
	*/
	SpringCamera::SpringCamera()
	{
	}

	/*!
	* @brief  デストラクタ
	*/
	SpringCamera::~SpringCamera()
	{
	}
	/*!
	* @brief 初期化。
	*/
	void SpringCamera::Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed)
	{
		
		m_camera.SetLookatPt(target);
		//カメラの座標。
		//m_camera.SetPosition(position);
		m_target = target;
		m_position = position;
		m_targetMoveSpeed = D3DXVECTOR3(NULL,NULL,NULL);
		m_positionMoveSpeed = D3DXVECTOR3(NULL, NULL, NULL);
		m_maxMoveSpeed = maxMoveSpeed;
		
	}
	void SpringCamera::UpdateSpringCamera()
	{
		/*
		m_dampingRate = CalcSpringScalar(m_targetDampingRate, m_dampingRate, m_dampingRateVel);
		D3DXVECTOR3 target = CalcSpringVector(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed, m_dampingRate);
		D3DXVECTOR3 position = CalcSpringVector(m_camera.GetPosition(), m_position, m_positionMoveSpeed, m_maxMoveSpeed, m_dampingRate);
		m_camera.SetTarget(target);
		m_camera.SetPosition(position);
		*/
	}
	/*!
	* @brief	更新。
	*/
	void SpringCamera::Update()
	{
		/*
		UpdateSpringCamera();
		UpdateCamera();
		*/
	}
//}