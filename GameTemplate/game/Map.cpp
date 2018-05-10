#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

static SMapChipLocInfo mapChipInfo[] = {
#include "locationInfo.h"
};
Map::Map()
{
}


Map::~Map()
{
}

void Map::Init()
{
	//配置してるオブジェクトの数を計算する
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	for (int i = 0; i < numObject; i ++ ) {
		//一個ずつオブジェクトをロードする
		//MapChipのインスタンスを動的に生成する
		MapChip* mapChip = new MapChip;
		//マップチップの情報を渡して初期化
		mapChip->Init(mapChipInfo[i]);
		//動的にプッシュ
		mapChipList.push_back(mapChip);
	}

}

void Map::Update()
{
	//一個ずつマップチップを更新
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
}

void Map::Draw()
{
	//一個ずつマップチップを更新
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}
}