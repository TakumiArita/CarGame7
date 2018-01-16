#pragma once
#include "RenderTarget.h"
class MainRenderTarget
{
public:
	MainRenderTarget();
	~MainRenderTarget();
	RenderTarget* mainRendertarget;

	void InitMainRenderTarget();
	void InitQuadPrimitive();
	void CopyMainRTToCurrentRT();
	void LoadShaders();
	void GetTerminate();

};

