#include "stdafx.h"
#include "Model.h"


Model::Model()
{
	mesh = NULL;
	textures = NULL;
	numMaterial = 0;
	effect = NULL;
}


Model::~Model()
{
	Release();
}

//������
void Model::Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName)
{
	Release();
	//X�t�@�C�������[�h
	LPD3DXBUFFER pD3DXMtrlBuffer;
	//X�t�@�C�������[�h
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	//�@�������݂��邩���ׂ�B
	if ((mesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		//�@�����Ȃ��̂ō쐬����B
		ID3DXMesh* pTempMesh = NULL;

		mesh->CloneMeshFVF(mesh->GetOptions(),
			mesh->GetFVF() | D3DFVF_NORMAL, g_pd3dDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		mesh->Release();
		mesh = pTempMesh;
	}

	//�}�e���A���o�b�t�@���擾�B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	//�e�N�X�`�������[�h
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		textures[i] = NULL;
		//�e�N�X�`�����쐬����B
		D3DXCreateTextureFromFileA(pd3dDevice,
			d3dxMaterials[i].pTextureFilename,
			&textures[i]);
		//�}�e���A���o�b�t�@������B
		pD3DXMtrlBuffer->Release();

		//�V�F�[�_�[���R���p�C���B
		LPD3DXBUFFER compileErrorBuffer = NULL;
		//�V�F�[�_�[���R���p�C���B
		HRESULT ht = D3DXCreateEffectFromFile(
			pd3dDevice,
			"basic.fx",
			NULL,
			NULL,
			D3DXSHADER_SKIPVALIDATION,
			NULL,
			&effect,
			&compileErrorBuffer
			);
		if (ht != S_OK) {
			MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			std::abort();
		}

	}

}

//�`��B
void Model::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX worldMatrix,
	D3DXMATRIX rotationMatrix,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4 ambentLight,
	int numDiffuseLight
)
{
	effect->SetTechnique("SkinModel");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);

	//�萔���W�X�^�ɐݒ肷��J���[�B
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//���[���h�s��̓]���B
	effect->SetMatrix("g_worldMatrix", &worldMatrix);
	//�r���[�s��̓]���B
	effect->SetMatrix("g_viewMatrix", &viewMatrix);           //�r���[�s���]���B

	effect->SetMatrix("g_projectionMatrix",&projMatrix);      //�v���W�F�N�V�����s��̓]���B

	effect->SetMatrix("g_rotationMatrix", &rotationMatrix);   //��]�s���]���B
	                                                          //���C�g�̌�����]���B
	effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//���C�g�J���[��]���B
	effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//������ݒ�B
	effect->SetVector("g_ambientLight", &ambentLight);

	effect->CommitChanges();                              //�f�[�^�̓]�����m��B

	for (DWORD i = 0; i < numMaterial; i++)
	{
		effect->SetTexture("g_diffuseTexture", textures[i]);
		mesh->DrawSubset(i);
	}
	effect->EndPass();
	effect->End();
}
//�J��
void Model::Release()
{
	//���b�V�����J��
	if (mesh != NULL){
		mesh->Release();
		mesh = NULL;
	}
	//�e�N�X�`�����J��
	if (textures != NULL) {
		for (unsigned int i = 0; i < numMaterial; i++) {
			if (textures[i] != NULL) {
				textures[i]->Release();
				textures[i] = NULL;
			}
		}delete[] textures;
		textures = NULL;
	}
	//�G�t�F�N�g���J��
	if (effect != NULL) {
		effect->Release();
		effect = NULL;
	}
}
//���b�V�����擾
LPD3DXMESH Model::GetMesh()
{
	return mesh;
}
//���[�t�B���O�������s
//morphTarget   ���[�t�^�[�Q�b�g
//rate    ���[�t�B���O���[�g
void Model::Morphing(Model* morphTargetA, Model*morphTargetB, float rate)
{
	//���[�t�^�[�Q�b�gA�̃��b�V�����擾�B
	LPD3DXMESH targetMesh_A = morphTargetA->GetMesh();
	//���[�t�^�[�Q�b�gA�̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_A;
	targetMesh_A->GetVertexBuffer(&targetVertexBuffer_A);
	//���_�o�b�t�@�̒�`���擾����B
	D3DVERTEXBUFFER_DESC desc;
	targetVertexBuffer_A->GetDesc(&desc);
	//���_�X���C�h���v�Z����B
	int stride = desc.Size / targetMesh_A->GetNumVertices();

	//���[�t�^�[�Q�b�gB�̃��b�V�����擾����B
	LPD3DXMESH targetMesh_B = morphTargetB->GetMesh();
	//���[�t�^�[�Q�b�gB�̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 targetVertexBuffer_B;
	targetMesh_B->GetVertexBuffer(&targetVertexBuffer_B);

	//�����̒��_�o�b�t�@���擾����B
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	mesh->GetVertexBuffer(&vertexBuffer);
	D3DXVECTOR3* vertexPos;
	D3DXVECTOR3* targetVertexPos_A;
	D3DXVECTOR3* targetVertexPos_B;
	//���_�o�b�t�@�����b�N
	vertexBuffer->Lock(0, desc.Size, (void**)&vertexPos, D3DLOCK_DISCARD);
	targetVertexBuffer_A->Lock(0, desc.Size,(void**)&targetVertexPos_A, D3DLOCK_DISCARD);
	targetVertexBuffer_A->Lock(0, desc.Size,(void**)&targetVertexPos_B, D3DLOCK_DISCARD);
	for (int vertNo = 0; vertNo < targetMesh_A->GetNumVertices(); vertNo++) {
		///////////////////////////////////////////////////////////////////
		//���_���[�t�̏���
		*vertexPos = (*targetVertexPos_A) * (1.0f - rate)
			+ (*targetVertexPos_B) * rate;
		/*
		vertexPos->x = targetVertexPos_A->x * (1.0f - rate)
		+ targetVertexPos_B->x * rate;
		vertexPos->y = targetVertexPos_A->y * (1.0f - rate)
		+ targetVertexPos_B->y * rate;
		vertexPos->z = targetVertexPos_A->z * (1.0f - rate)
		+ targetVertexPos_B->z * rate;
		*/
		///////////////////////////////////////////////////////////////////
		//���̒��_�ցB
		char* p = (char*)vertexPos;
		p += stride;
		vertexPos = (D3DXVECTOR3*)p;
		p = (char*)targetVertexPos_A;
		p += stride;
		targetVertexPos_A = (D3DXVECTOR3*)p;
		p = (char*)targetVertexPos_B;
		p += stride;
		targetVertexPos_B = (D3DXVECTOR3*)p;
	}
	//���_�o�b�t�@���A�����b�N
	vertexBuffer->Unlock();
	targetVertexBuffer_A->Unlock();
	targetVertexBuffer_B->Unlock();
	vertexBuffer->Release();
	targetVertexBuffer_A->Release();
	targetVertexBuffer_B->Release();
}