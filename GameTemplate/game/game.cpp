/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"


/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
	delete g_physicsWorld;
	g_physicsWorld = NULL;
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�������[���h���������B
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{	
}
/*!
* @brief	�`��B
 */
void Game::Draw()
{
}
