/*!
* @brief	ゲームクラス。
*/

#pragma once
#include "Map.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"

/*!
* @brief	ゲームクラス。
*/
class Game {
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Game();
	/*!
	* @brief	デストラクタ。
	*/
	~Game();
	/*!
	* @brief	ゲームが起動してから一度だけ呼ばれる関数。
	*/
	void Start();
	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	* @brief	描画。
	*/
	void Draw();
private:
	
	D3DXVECTOR3 toCameraPos;

};

extern Game* game;