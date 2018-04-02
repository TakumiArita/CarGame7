#pragma once
class RoadAroundFrequencyTexture
{
public:
	RoadAroundFrequencyTexture();
	~RoadAroundFrequencyTexture();

	void Init();
	void Update();
	void Draw();

	//ゲームの時間のゲッター
	int GetAroundTexture()
	{
		return aroundtexture;
	}

	//Noの配列のゲッター
	const char* GetTimetexture()
	{
		return Roadaroundtexture[aroundtexture];
	}
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[3];
	LPDIRECT3DTEXTURE9 pTexture_No3;
	LPDIRECT3DTEXTURE9 pTexture_Around;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;

	//Noの配列。
	const char* Roadaroundtexture[3];
	//const char* timetexture[10];
private:
	//ゲームの時間。
	int aroundtexture = 0;
};

