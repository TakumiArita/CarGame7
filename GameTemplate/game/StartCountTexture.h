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

	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[3];
	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;
	//No�̔z��B
	const char* timetexture[3];
	int starttime = 2;
	//�X�^�[�g�܂ł̎��ԁB
	int starttimer = 300;
private:

};