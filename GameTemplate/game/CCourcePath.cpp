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
	//�z�u���Ă�I�u�W�F�N�g�̐����v�Z����
	numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	//���O�Ń\�[�g����B
	std::vector<CMapChipLocInfo*> sortMapChipLocInfo;
	sortMapChipLocInfo.resize(numObject);
	for (int i = 0; i < numObject; i++) {
		int pointNo = atoi(&mapChipInfo[i].modelName[4]);
		sortMapChipLocInfo[pointNo] = &mapChipInfo[i];
	}

	D3DXVECTOR3 courceDir;
	for (int i = 0; i < numObject-1; i++) {
		//�G�b�W�̏������B
		SCourceEdge edge;
		edge.startPos = sortMapChipLocInfo[i]->pos;		//�n�_
		edge.endPos = sortMapChipLocInfo[i + 1]->pos;	//�I�_
		edge.startToEnd = edge.endPos - edge.startPos;	//�n�_����I�_�Ɍ������x�N�g���B
		D3DXVec3Normalize(&edge.direction, &edge.startToEnd);	//�n�_����I�_�ւ̕����x�N�g���B
		courceEdigeList.push_back(edge);                 //���X�g���v�b�V���o�b�N�B
	}
	//�G�b�W�̏������B
	SCourceEdge edge;
	edge.endPos = sortMapChipLocInfo[0]->pos;
	edge.startPos = sortMapChipLocInfo[numObject - 1]->pos;
	edge.startToEnd = edge.endPos - edge.startPos;	//�n�_����I�_�Ɍ������x�N�g���B
	D3DXVec3Normalize(&edge.direction, &edge.startToEnd);	//�n�_����I�_�ւ̕����x�N�g���B

	courceEdigeList.push_back(edge);                 //���X�g���v�b�V���o�b�N�B


}	
void CCourcePath::Update()
{

}

void CCourcePath::Draw()
{

}

