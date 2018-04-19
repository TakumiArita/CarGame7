#pragma once
#include "GameTimeTexture.h"
#include "StartCountTexture.h"
#include "RoadAroundFrequencyTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init();
	void Draw();
	void SaveGameTimeDraw();

	LPD3DXSPRITE ppSprite;

	//GameTimeTexture gametimetexture;
	//StartCountTexture    startcounttexture;
	//RoadAroundFrequencyTexture roadaroundfrequencytexture;
};

