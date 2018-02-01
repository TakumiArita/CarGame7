#pragma once
#include "ClearTexture.h"

class Clear
{
public:
	Clear();
	~Clear();

	void Init();
	void Draw();

	LPD3DXSPRITE ppSprite;


	ClearTexture cleartexture;
};