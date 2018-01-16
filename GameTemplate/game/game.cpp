/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"


/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	delete g_physicsWorld;
	g_physicsWorld = NULL;
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//物理ワールドを初期化。
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{	
}
/*!
* @brief	描画。
 */
void Game::Draw()
{
}
