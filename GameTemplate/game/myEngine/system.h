#pragma once

#include "myEngine/Graphics/EffectManager.h"
extern LPDIRECT3D9				g_pD3D;		
extern LPDIRECT3DDEVICE9		g_pd3dDevice;
extern EffectManager*			g_effectManager;

//��ʃT�C�Y
//const int FRAME_BUFFER_WIDTH = 1280;
//const int FRAME_BUFFER_HEIGHT = 720;

//��ʃT�C�Y1/2
const int FRAME_BUFFER_WIDTH = 640;
const int FRAME_BUFFER_HEIGHT = 360;

const int CFRAME_BUFFER_WIDTH = 1;
const int CFRAME_BUFFER_HEIGHT = 1;