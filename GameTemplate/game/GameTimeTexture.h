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

	//�Q�[���^�C���̃Z�b�^�[
	void SetGameTimer(int setGametimer)
	{
		gametimer = setGametimer;
	}
	//�Q�[���̎��Ԃ̃Q�b�^�[
	int GetGameTimer()
	{
		return gametimer;
	}

	//�Z�[�u�p�Q�[���^�C���̃Z�b�^�[
	int SetSaveGameTimer(int setSaveGametimer)
	{
		saveGametimer = setSaveGametimer;
	}
	//�Z�[�u�p�Q�[���^�C���̃Q�b�^�[
	int GetSaveGameTimer()
	{
		return saveGametimer;
	}

	//�e�N�X�`���̏o�͐�
	LPDIRECT3DTEXTURE9 SetpTexture(int i)
	{
		pTexture[i];
		return pTexture[i];
	}
	LPDIRECT3DTEXTURE9 GetpTexture_dot()
	{
		return pTexture_dot;
	}
	LPDIRECT3DTEXTURE9 GetpTexture_time()
	{
		return pTexture_time;
	}
	LPDIRECT3DTEXTURE9 GetpTexture_newRecord()
	{
		return pTexture_newRecord;
	}

	//No�̔z��̃Z�b�^�[�ƃQ�b�^�[�B
	const char SetTimeTexture(int i)
	{
		timetexture[i];
	}
	const char** GetTimeTexture()
	{
		return timetexture;
	}

	int SetGameTime(int i)
	{
		gametime[i];
		return gametime[i];
	}
	int* GetGameTime()
	{
		return gametime;
	}

	int SetGameTimeSave(int i)
	{
	    gametimeSave[i];
		return gametimeSave[i];
	}
	int* GetGameTimeSave()
	{
		return gametimeSave;
	}

	int SetSaveGameTime(int i)
	{
		savegametime[i];
		return savegametime[i];
	}
	int* GetSaveGameTime()
	{
		return savegametime;
	}



private:
	//�Q�[���̎��ԁB
	int gametimer = 0;
	int saveGametimer = 0;
	FILE* fp;
	char str[10];


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

};