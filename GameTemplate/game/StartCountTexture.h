#pragma once
class StartCountTexture
{
public:
	StartCountTexture();
	~StartCountTexture();

	void Init();
	void Update();
	void Draw();

	int GetStartCountTimer()
	{
		return starttimer;
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

	//No�̔z��̃Z�b�^�[�ƃQ�b�^�[�B
	const char Settimetexture(int i)
	{
		timetexture[i];
	}
	const char** Gettimetexture()
	{
		return timetexture;
	}
	int GetStarttime()
	{
		return starttime;
	}
private:
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[3];
	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;
	//No�̔z��B
	const char* timetexture[3];
	int starttime = 2;
	//�X�^�[�g�܂ł̎��ԁB
	int starttimer = 300;

};