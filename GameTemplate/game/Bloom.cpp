#include "stdafx.h"
#include "Bloom.h"
#include "SceneManager.h"
#include "MainRenderTarget.h"

//-----------------------------------------------------------------------------
// �|����`��B
//-----------------------------------------------------------------------------
void Bloom::DrawQuadPrimitive()
{
	//quadPrimitive = new Primitive;
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
														//����͐擪����ǂݍ��ނ̂�0�ł����B
		quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
}

//-----------------------------------------------------------------------------
// Name: 18-3 �|���̏������B
//-----------------------------------------------------------------------------
void Bloom::InitQuadPrimitive()
{
	quadPrimitive = new Primitive;
	//���_�̍\���́B
	struct SVertex {
		float pos[4];	//���_���W�B
		float uv[2];		//UV���W�B
	};
	//���_�o�b�t�@�B
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//���_���C�A�E�g�B���_�o�b�t�@�̍\�����ǂ̂悤�ɂȂ��Ă��邩��GPU�ɋ����邽�߂̂��́B
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//���_�X�g���[����0�Ԗڂ�0�o�C�g�ڂ���float�^��4���̃f�[�^�͍��W(D3DDECLUSAGE_POSITION)�ł��邱�Ƃ������Ă���B
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//���_�X�g���[����0�Ԗڂ�16�o�C�g�ڂ���float�^��2���̃f�[�^��UV���W(D3DDECLUSAGE_TEXCOORD)�ł��邱�Ƃ������Ă���B
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//�C���f�b�N�X�o�b�t�@�B
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		Primitive::eTriangleStrip,	//����̓v���~�e�B�u�̎�ނ̓g���C�A���O���X�g���b�v�B
		4,							//���_�̐��B�l�p�`�̔|���Ńg���C�A���O���X�g���b�v�Ȃ̂łS�B
		sizeof(SVertex),			//���_�X�g���C�h�B��̒��_�̑傫���B�P�ʂ̓o�C�g�B
		scShapeVertex_PT_Element,	//���_���C�A�E�g�B
		vertexBuffer,				//���_�o�b�t�@�B
		4,							//�C���f�b�N�X�̐��B
		D3DFMT_INDEX16,				//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B�����16bit�t�H�[�}�b�g���w�肷��B
									//�C���f�b�N�X�̐���65536�ȉ��̏ꍇ��16bit�ł������A����𒴂���ꍇ��D3DFMT_INDEX32���w�肷��B
		indexBuffer					//�C���f�b�N�X�o�b�t�@�B
	);
}
void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] = expf(-0.5*(float)(i*i) / dispersion);
		total += 2.0f*weights[i];
	}
	//�K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] /= total;
	}
}
Bloom::Bloom()
{
	//�u���[���̃V�F�[�_�[�������[�h
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");

	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);
	//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	//���u���[�p�B
	downSamplingRenderTarget[0].Create(
		FRAME_BUFFER_WIDTH >> 1,  //���̉𑜓x�̃t���[���o�b�t�@�̔����ɂ���B
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
	);
	//�c�u���[�p�B
	downSamplingRenderTarget[1].Create(
		FRAME_BUFFER_WIDTH >> 1,	//�c�Ɖ��̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		FRAME_BUFFER_HEIGHT >> 1,
		1,
		D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
	);
	InitQuadPrimitive();
	//UpdateWeight(25.0f);
}

Bloom::~Bloom()
{
}
void Bloom::Render()
{
	//Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�܂��͋P�x�𒊏o����B
	{
		//���u�����h������Ȃ��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//�P�x���o�e�N�j�b�N���Z�b�g�B
		effect->SetTechnique("SamplingLuminance");

		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�V�[���e�N�X�`����ݒ肷��B
		effect->SetTexture("g_scene", scenemanager->GetRenderTarget().GetTexture());
		effect->CommitChanges();

		DrawQuadPrimitive();
		//�萔���W�X�^�ւ̍X�V���R�~�b�g�B
		effect->EndPass();
		effect->End();
		//�ύX���������_�����O�X�e�[�g�����Ƃɖ߂��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
	
	//�K�E�X�u���[�Ŏg���d�݃e�[�u�����X�V�B
	UpdateWeight(25.0f);
	//�P�x�𒊏o�����e�N�X�`����X�u���[
	{
		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g��ǉ��B
		g_pd3dDevice->SetRenderTarget(
			0,
			downSamplingRenderTarget[0].GetRenderTarget()
		);
		//g_pd3dDevice->SetDepthStencilSurface(downSamplingRenderTarget[0].GetDepthStencilBuffer());
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//���u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
		effect->SetTechnique("XBlur");

		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(luminanceRenderTarget.GetWidth()),
			(float)(luminanceRenderTarget.GetHeight())
		};
		float offset[] = {
			16.0f / (float)(luminanceRenderTarget.GetWidth()),
			0.0f
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", luminanceRenderTarget.GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}
	//�P�x�𒊏o�����e�N�X�`����Y�u���[
	{
		g_pd3dDevice->SetRenderTarget(
			0,
			downSamplingRenderTarget[1].GetRenderTarget()
		);
		//g_pd3dDevice->SetDepthStencilSurface(downSamplingRenderTarget[1].GetDepthStencilBuffer());

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(1, 1, 1), 1.0f, 0);
		effect->SetTechnique("YBlur");
		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g��ǉ��B
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(downSamplingRenderTarget[0].GetWidth()),
			(float)(downSamplingRenderTarget[0].GetHeight())
		};
		float offset[] = {
			0.0f ,
			16.0f / (float)(downSamplingRenderTarget[0].GetHeight())
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", downSamplingRenderTarget[0].GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}

	//���C���̃����_�����O�^�[�Q�b�g�ɖ߂��B
	g_pd3dDevice->SetRenderTarget(0, scenemanager->GetRenderTarget().GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(scenemanager->GetRenderTarget().GetDepthStencilBuffer());


	{
		//�ŏI�����B
		float offset[] = {
			0.5f / downSamplingRenderTarget[1].GetWidth() ,
			0.5f / downSamplingRenderTarget[1].GetHeight()
		};

		//���Z�����B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		effect->SetTechnique("Final");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		effect->SetTexture("g_blur", downSamplingRenderTarget[1].GetTexture());
		effect->SetValue("g_offset", offset, sizeof(offset));
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

