#include "stdafx.h"
#include "game.h"
#include "MapChip.h"
#include "SceneManager.h"

MapChip::MapChip() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f,0.0f,0.0f,1.0f)
{
}

MapChip::~MapChip()
{
}

void MapChip::Init(SMapChipLocInfo& locInfo)
{
	//読み込むモデルのファイルパスを作成する
	char modelPath[265];
	sprintf(modelPath, "Assets/modelData/%s.x", locInfo.modelName);
	//モデルをロード
	modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinmodelを初期化
	model.Init(&modelData);

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	
	model.SetLight(&light);
	position = locInfo.pos;
	rotation = locInfo.rotation;

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	//衝突判定絡みの初期化
	//スキンモデルからメッシュコライダーを作成する
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//剛体作成
	//剛体を作成するための情報を設定する
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;    //剛体のコリジョンを設定
	rbInfo.mass = 0.0f;                 //質量を0にすると剛体が動かない
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成する
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void MapChip::Update()
{
}

void MapChip::Draw()
{
	model.Draw(&scenemanager->GetCamera()->GetViewMatrix(), &scenemanager->GetCamera()->GetProjectionMatrix(),false,true,false);
}