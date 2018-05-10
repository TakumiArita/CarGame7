#pragma once
class RoadAroundFrequencyTexture
{
public:
	RoadAroundFrequencyTexture();
	~RoadAroundFrequencyTexture();

	void Init();
	void Update();
	void Draw();

	//�Q�[���̎��Ԃ̃Q�b�^�[
	int GetAroundTexture()
	{
		return aroundtexture;
	}
	//No�̔z��̃Z�b�^�[�B
	const char SetRoadAroundTexture(int i)
	{
		Roadaroundtexture[i];
	}
	//No�̔z��̃Q�b�^�[�B
	const char** GetRoadAroundTexture()
	{
		return Roadaroundtexture;
	}

	//�e�N�X�`���̏o�͐�̃Z�b�^�[�ƃQ�b�^�[�B
	LPDIRECT3DTEXTURE9 SetpTexture(int i)
	{
		return pTexture[i];
	}
	LPDIRECT3DTEXTURE9* GetpTexture()
	{
		return pTexture;
	}
		
	LPDIRECT3DTEXTURE9 GetpTexture_No3()
	{
		return pTexture_No3;
	}
		
	LPDIRECT3DTEXTURE9 GetpTexture_Around()
	{
		return pTexture_Around;
	}



private:
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[3];
	LPDIRECT3DTEXTURE9 pTexture_No3;
	LPDIRECT3DTEXTURE9 pTexture_Around;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;

	//No�̔z��B
	const char* Roadaroundtexture[3];
	//�Q�[���̎��ԁB
	int aroundtexture = 0;
};

