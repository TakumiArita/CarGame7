#pragma once
class GoalTexture
{
public:
	GoalTexture();
	~GoalTexture();

	void Init();
	void Update();
	void Draw();
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture;
	//LPDIRECT3DTEXTURE9 pTexture;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;
};

