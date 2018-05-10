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
	//Noの配列のセッター。
	const char SetRoadAroundTexture(int i)
	{
		Roadaroundtexture[i];
	}
	//Noの配列のゲッター。
	const char** GetRoadAroundTexture()
	{
		return Roadaroundtexture;
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
		
	LPDIRECT3DTEXTURE9 GetpTexture_No3()
	{
		return pTexture_No3;
	}
		
	LPDIRECT3DTEXTURE9 GetpTexture_Around()
	{
		return pTexture_Around;
	}



private:
	//テクスチャの出力先
	LPDIRECT3DTEXTURE9 pTexture[3];
	LPDIRECT3DTEXTURE9 pTexture_No3;
	LPDIRECT3DTEXTURE9 pTexture_Around;

	//画像情報格納用構造体
	D3DXIMAGE_INFO imgInfo;

	//Noの配列。
	const char* Roadaroundtexture[3];
	//ゲームの時間。
	int aroundtexture = 0;
};

