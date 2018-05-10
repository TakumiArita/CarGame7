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

	//テクスチャの出力先のセッターとゲッター。
	LPDIRECT3DTEXTURE9 SetpTexture(int i)
	{
		return pTexture[i];
	}
	LPDIRECT3DTEXTURE9* GetpTexture()
	{
		return pTexture;
	}

	//Noの配列のセッターとゲッター。
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
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[3];
	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;
	//Noの配列。
	const char* timetexture[3];
	int starttime = 2;
	//スタートまでの時間。
	int starttimer = 300;

};