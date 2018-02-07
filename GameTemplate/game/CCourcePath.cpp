#include "stdafx.h"
#include "CCourcePath.h"
#include "SceneManager.h"
//#include "MapChip.h"
#include <iostream>
#include <vector>

static CMapChipLocInfo mapChipInfo[] = {
#include "courcePath.h"
};

CCourcePath::CCourcePath()
{
}

CCourcePath::~CCourcePath()
{
}

void CCourcePath::Init(SCourceEdge& courcePath)
{
	//配置してるオブジェクトの数を計算する
	numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	//名前でソートする。
	std::vector<CMapChipLocInfo*> sortMapChipLocInfo;
	sortMapChipLocInfo.resize(numObject);
	for (int i = 0; i < numObject; i++) {
		int pointNo = atoi(&mapChipInfo[i].modelName[4]);
		sortMapChipLocInfo[pointNo] = &mapChipInfo[i];
	}

	D3DXVECTOR3 courceDir;
	for (int i = 0; i < numObject-1; i++) {
		//エッジの情報を作る。
		SCourceEdge edge;
		edge.startPos = sortMapChipLocInfo[i]->pos;		//始点
		edge.endPos = sortMapChipLocInfo[i + 1]->pos;	//終点
		edge.startToEnd = edge.endPos - edge.startPos;	//始点から終点に向かうベクトル。
		D3DXVec3Normalize(&edge.direction, &edge.startToEnd);	//始点から終点への方向ベクトル。
		courceEdigeList.push_back(edge);                 //リストをプッシュバック。
	}
	//エッジの情報を作る。
	SCourceEdge edge;
	edge.endPos = sortMapChipLocInfo[0]->pos;
	edge.startPos = sortMapChipLocInfo[numObject - 1]->pos;
	edge.startToEnd = edge.endPos - edge.startPos;	//始点から終点に向かうベクトル。
	D3DXVec3Normalize(&edge.direction, &edge.startToEnd);	//始点から終点への方向ベクトル。

	courceEdigeList.push_back(edge);                 //リストをプッシュバック。


}	
void CCourcePath::Update()
{

}

void CCourcePath::Draw()
{

}

