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

	//ゲームタイムのセッター
	void SetGameTimer(int setGametimer)
	{
		gametimer = setGametimer;
	}
	//ゲームの時間のゲッター
	int GetGameTimer()
	{
		return gametimer;
	}

	//セーブ用ゲームタイムのセッター
	int SetSaveGameTimer(int setSaveGametimer)
	{
		saveGametimer = setSaveGametimer;
	}
	//セーブ用ゲームタイムのゲッター
	int GetSaveGameTimer()
	{
		return saveGametimer;
	}

	//テクスチャの出力先
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

	//Noの配列のセッターとゲッター。
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
	//ゲームの時間。
	int gametimer = 0;
	int saveGametimer = 0;
	FILE* fp;
	char str[10];


	bool firstTitleFlag = false;

	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[10];
	LPDIRECT3DTEXTURE9 pTexture_dot;
	LPDIRECT3DTEXTURE9 pTexture_time;
	LPDIRECT3DTEXTURE9 pTexture_newRecord;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;

	//Noの配列。
	const char* timetexture[10];
	int gametime[4];
	int gametimeSave[4];
	int savegametime[4];

};