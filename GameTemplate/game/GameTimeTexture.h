#pragma once
//#include <stdio.h>

class GameTimeTexture
{
public:
	GameTimeTexture();
	~GameTimeTexture();
	
	void Init();
	void Update();
	void SaveUpdate();
	void Draw();

	//�Q�[���̎��Ԃ̃Q�b�^�[
	int GetGameTimer()
	{
		return gametimer;
	}

	//�Q�[���^�C���̃Z�b�^�[
	void SetGameTimer(int setGametimer)
	{
		gametimer = setGametimer;
	}
	bool firstTitleFlag = false;
	
	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 pTexture[10];
	LPDIRECT3DTEXTURE9 pTexture_dot;
	LPDIRECT3DTEXTURE9 pTexture_time;
	LPDIRECT3DTEXTURE9 pTexture_newRecord;

	//�摜���i�[�p�\����
	D3DXIMAGE_INFO imgInfo;

	//No�̔z��B
    const char* timetexture[10];
	int gametime[4];
	int gametimeSave[4];
	int savegametime[4];

private:
	//�Q�[���̎��ԁB
	int gametimer = 0;
	int saveGametimer = 0;
	FILE* fp;
	char str[10];

};