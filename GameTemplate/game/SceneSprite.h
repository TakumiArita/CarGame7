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

	LPD3DXSPRITE ppSprite;
	GoalTexture  goaltexture;
	TitleTexture titletexture;
	StartTexture starttexture;
};

