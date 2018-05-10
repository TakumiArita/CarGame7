#pragma once
#include "GoalTexture.h"
#include "TitleTexture.h"
#include "StartTexture.h"
class SceneSprite
{
public:
	SceneSprite();
	~SceneSprite();

	void Init();
	void TitleDraw();
	void GoalDraw();
	void StartDraw();

private:
	LPD3DXSPRITE ppSprite;
};

