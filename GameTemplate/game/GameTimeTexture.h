#pragma once
class GameTimeTexture
{
public:
	GameTimeTexture();
	~GameTimeTexture();
	
	void Init();
	void Update();
	void Draw();

	//ゲームの時間のゲッター
	int GetGameTimer()
	{
		return gametimer;
	}

	//int GetGameTime()
	//{
	//	return gametime[3];
	//}
	//Noの配列のゲッター
	const char* GetTimetexture()
	{
		return timetexture[gametimer];
	}
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[10];
	LPDIRECT3DTEXTURE9 pTexture_dot;
	//LPDIRECT3DTEXTURE9 pTexture;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;

	//Noの配列。
    const char* timetexture[10];
	//const char* timetexture[10];
	int gametime[4];

private:
	//float gameTime = 0.0f;
	//int gametime[3];
	//ゲームの時間。
	int gametimer = 0;

};

//D3DXCreateCubeTextureFromFileExA