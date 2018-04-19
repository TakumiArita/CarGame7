/*
*  @brief    �p�[�e�B�N���B
*/

#include "stdafx.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "SceneManager.h"

//extern LPDIRECT3DDEVICE9 g_pd3dDevice;
/*!
*@brief	���W��UV���W
*/
struct SShapeVertex_PT {
	float		pos[4];
	float		uv[2];
};
static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
	{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
	{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
	D3DDECL_END()
};

Particle::Particle() :
	texture(nullptr),
	shaderEffect(nullptr)
{
}
Particle::~Particle()
{
	if (shaderEffect != nullptr) {
		shaderEffect->Release();
	}
	if (texture != nullptr) {
		texture->Release();
	}
}
void Particle::Init(const SParticleEmitParameter& param)
{
	float halfW = param.w * 0.5f;
	float halfH = param.h * 0.5f;

	D3DXVECTOR4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	moveSpeed = param.initSpeed;

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float add = ((rand() % 255) - 128) / 128.0f;
	//moveSpeed.x += add * 0.3f;
	//moveSpeed.y += add * 0.3f;
	//moveSpeed.z += add * 0.3f;
	moveSpeed.x += add * 2.0f;
	moveSpeed.y += add * 2.0f;
	moveSpeed.z += add * 2.0f;

	SShapeVertex_PT vb[] = {
		{
			-halfW, halfH, 0.0f, 1.0f,
			uv.x, uv.y
		},
		{
			halfW, halfH, 0.0f, 1.0f,
			uv.z, uv.y
		},
		{
			-halfW, -halfH, 0.0f, 1.0f,
			uv.x, uv.w
		},
		{
			halfW, -halfH, 0.0f, 1.0f,
			uv.z, uv.w
		},

	};
	short index[]{
		0,1,2,3
	};
	primitive.Create(
		Primitive::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vb,
		4,
		D3DFMT_INDEX16,
		index
	);
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, param.texturePath, &texture);

	LPD3DXBUFFER  compileErrorBuffer = NULL;
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/ColorTexPrim.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&shaderEffect,
		NULL
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}


void Particle::Update()
{
	auto deltaTime = 1.0f / 60.0f;
	//moveSpeed.y -= 0.1f;
	auto add = moveSpeed * deltaTime;
	position += add;

	//position.Add(addPos);
	D3DXVECTOR3 addPos;
	position += addPos;
	//position += position;

	D3DXMATRIX mTrans;
	//mTrans.MakeTranslation(position);
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
	if (isBillboard) {
		//�r���{�[�h�������s���B
		const D3DXMATRIX mCameraRot = scenemanager->camera.GetInvRotateMat();
		D3DXQUATERNION qRot;
		//qRot.SetRotation(D3DXVECTOR3(mCameraRot.m[2][0], mCameraRot.m[2][1], mCameraRot.m[2][2]), rotateZ);
		D3DXQuaternionRotationAxis(&qRot,&scenemanager->player.GetPosition(), D3DXToRadian(scenemanager->player.GetLookCamera()));
		D3DXMATRIX rot;
		//rot.MakeRotationFromQuaternion(qRot);
		D3DXMatrixRotationQuaternion(&rot,&qRot);

		//mWorld.Mul(mCameraRot, rot);
		D3DXMatrixMultiply(&mWorld, &mCameraRot, &rot);
		
		//mWorld.Mul(mWorld, mTrans);
		D3DXMatrixMultiply(&mWorld, &mWorld, &mTrans);
	}
	else {
		mWorld = mTrans;
	}
	timer += deltaTime;
	switch (state) {
	case eStateRun:
		if (timer >= life) {
			if (isFade) {
				state = eStateFadeOut;
				timer = 0.0f;
			}
			else {
				state = eStateDead;
			}
		}
		break;
	case eStateFadeOut: {
		float t = timer / fadeTIme;
		timer += deltaTime;
		alpha = initAlpha + (-initAlpha)*t;
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			state = eStateDead;	//���S�B
		}
	}break;
	case eStateDead:
		//GameObjectManager().DeleteGameObject(this);
		break;
	}

}
void Particle::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	D3DXMATRIX m, mTrans;
	D3DXMATRIX viewRotMatrix;
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
	//1.�J�����̉�]�s������߂�B
	D3DXMatrixInverse(&viewRotMatrix, NULL, &viewMatrix);
	//D3DXMatrixInverse(&viewRotMatrix, NULL, &viewRotMatrix);
	//2.1�ŋ��߂���]�s������[���h�s��ɏ�Z����B
	viewRotMatrix.m[3][0] = 0.0f;
	viewRotMatrix.m[3][1] = 0.0f;
	viewRotMatrix.m[3][2] = 0.0f;
	viewRotMatrix.m[3][3] = 1.0f;

	m = viewRotMatrix * mTrans * viewMatrix * projMatrix;

	/*	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
	//�A���t�@�u�����f�B���O��L���ɂ���B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	shaderEffect->SetTechnique("ColorTexPrimAdd");

	shaderEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shaderEffect->BeginPass(0);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	shaderEffect->SetValue("g_mWVP", &m, sizeof(m));
	shaderEffect->SetTexture("g_texture", texture);
	shaderEffect->CommitChanges();

	g_pd3dDevice->SetStreamSource(0, primitive.GetVertexBuffer()->GetBody(), 0, primitive.GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(primitive.GetIndexBuffer()->GetBody());
	g_pd3dDevice->SetVertexDeclaration(primitive.GetVertexDecl());
	g_pd3dDevice->DrawIndexedPrimitive(primitive.GetD3DPrimitiveType(), 0, 0, primitive.GetNumVertex(), 0, primitive.GetNumPolygon());
	shaderEffect->EndPass();
	shaderEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
