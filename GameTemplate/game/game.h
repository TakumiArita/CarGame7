/*!
* @brief	�Q�[���N���X�B
*/

#pragma once
#include "Map.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"

/*!
* @brief	�Q�[���N���X�B
*/
class Game {
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Game();
	/*!
	* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	*/
	void Start();
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�`��B
	*/
	void Draw();
private:
	
	D3DXVECTOR3 toCameraPos;

};

extern Game* game;