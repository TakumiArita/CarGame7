#pragma once
class GameTimeTexture
{
public:
	GameTimeTexture();
	~GameTimeTexture();
	
	void Init();
	void Update();
	void Draw();

	//�Q�[���̎��Ԃ̃Q�b�^�[
	int GetGameTimer()
	{
		return gametimer;
	}

	//No�̔z��̃Q�b�^�[
	const char* GetTimetexture()
	{
		return timetexture[gametimer];
	}
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[10];
	LPDIRECT3DTEXTURE9 pTexture_dot;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;

	//No�̔z��B
    const char* timetexture[10];
	//const char* timetexture[10];
	int gametime[4];

private:
	//�Q�[���̎��ԁB
	int gametimer = 0;

};