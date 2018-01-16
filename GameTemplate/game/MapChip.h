#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"


//�}�b�v�`�b�v�̔z�u���
struct SMapChipLocInfo {
	const char* modelName;         //���f��
	D3DXVECTOR3 pos;               //���W
	D3DXQUATERNION rotation;       //��]
	D3DXVECTOR3 scale;             //�傫��
	D3DXVECTOR4 setambientlight;   //����

};
class MapChip
{
public:
	MapChip();
	~MapChip();
	void Init(SMapChipLocInfo& locInfo);
	void Update();
	void Draw();
private:
	SkinModel       model;
	SkinModelData   modelData;
	D3DXVECTOR3     position;
	D3DXQUATERNION  rotation;
	D3DXVECTOR3     scale;
	D3DXVECTOR4      setambientlight;
	Light            light;
	MeshCollider     meshCollider; //���b�V���R���C�_�[
	RigidBody        rigidBody;       //����
};

