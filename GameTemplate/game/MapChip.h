#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"


//マップチップの配置情報
struct SMapChipLocInfo {
	const char* modelName;         //モデル
	D3DXVECTOR3 pos;               //座標
	D3DXQUATERNION rotation;       //回転
	D3DXVECTOR3 scale;             //大きさ
	D3DXVECTOR4 setambientlight;   //環境光

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
	MeshCollider     meshCollider; //メッシュコライダー
	RigidBody        rigidBody;       //剛体
};

