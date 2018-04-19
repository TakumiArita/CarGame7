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

	//ゲームの時間のゲッター
	int GetGameTimer()
	{
		return gametimer;
	}

	//ゲームタイムのセッター
	void SetGameTimer(int setGametimer)
	{
		gametimer = setGametimer;
	}
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

private:
	//ゲームの時間。
	int gametimer = 0;
	int saveGametimer = 0;
	FILE* fp;
	char str[10];

};