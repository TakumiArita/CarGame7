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

	//No�̔z��̃Q�b�^�[
	const char* GetTimetexture()
	{
		return Roadaroundtexture[aroundtexture];
	}
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[3];
	LPDIRECT3DTEXTURE9 pTexture_No3;
	LPDIRECT3DTEXTURE9 pTexture_Around;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;

	//No�̔z��B
	const char* Roadaroundtexture[3];
	//const char* timetexture[10];
private:
	//�Q�[���̎��ԁB
	int aroundtexture = 0;
};

