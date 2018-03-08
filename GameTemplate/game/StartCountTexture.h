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

	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[3];
	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;
	//Noの配列。
	const char* timetexture[3];
	int starttime = 2;
	//スタートまでの時間。
	int starttimer = 300;
private:

};