#pragma once

class Model {
public:
	//�R���X�g���N�^
	Model();
	//�f�X�g���N�^
	~Model();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice, const char* fileName);

	//�`��B
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX worldMatrix,
		D3DXMATRIX rotationMatrix,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
	);
	//�J���B
	void Release();
	//���[�t�B���O�����̎��s�B
	//morphTargetA	���[�t�^�[�Q�b�gA
	//morphTargetB  ���[�t�^�[�Q�b�gB
	//rate ���[�t�B���O���[�g�B
	void Morphing(Model* morphTargetA, Model* morphTargetB, float rate);
	//���b�V�����擾�B
	LPD3DXMESH GetMesh();
private:
	LPD3DXMESH				mesh;			//���b�V���B
	LPDIRECT3DTEXTURE9*		textures;		//�e�N�X�`���B
	DWORD					numMaterial;	//�}�e���A���̐��B
	ID3DXEffect*			effect;			//�G�t�F�N�g�B

};
