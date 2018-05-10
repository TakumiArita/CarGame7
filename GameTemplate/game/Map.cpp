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
	//�z�u���Ă�I�u�W�F�N�g�̐����v�Z����
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	for (int i = 0; i < numObject; i ++ ) {
		//����I�u�W�F�N�g�����[�h����
		//MapChip�̃C���X�^���X�𓮓I�ɐ�������
		MapChip* mapChip = new MapChip;
		//�}�b�v�`�b�v�̏���n���ď�����
		mapChip->Init(mapChipInfo[i]);
		//���I�Ƀv�b�V��
		mapChipList.push_back(mapChip);
	}

}

void Map::Update()
{
	//����}�b�v�`�b�v���X�V
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
}

void Map::Draw()
{
	//����}�b�v�`�b�v���X�V
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}
}