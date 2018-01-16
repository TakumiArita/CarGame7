#include "stdafx.h"
#include "game.h"
#include "MapChip.h"
#include "SceneManager.h"


MapChip::MapChip() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f,0.0f,0.0f,1.0f),
	scale(1.0f, 1.0f, 1.0f)
{
}
MapChip::~MapChip()
{
}

void MapChip::Init(SMapChipLocInfo& locInfo)
{
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬����
	char modelPath[265];
	sprintf(modelPath, "Assets/modelData/%s.x", locInfo.modelName);
	//���f�������[�h
	modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����Skinmodel��������
	model.Init(&modelData);

	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	//������Init�֐��Ō�ɒǉ��B
	//light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	//light.SetAmbientLight(setambientlight);


	model.SetLight(&light);
	position = locInfo.pos;
	rotation = locInfo.rotation;
	scale = locInfo.scale;
	setambientlight = locInfo.setambientlight;

	model.UpdateWorldMatrix(position, rotation, scale,setambientlight);
	//�Փ˔��藍�݂̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//���̍쐬
	//���̂��쐬���邽�߂̏���ݒ肷��
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;    //���̂̃R���W������ݒ�
	rbInfo.mass = 0.0f;                 //���ʂ�0�ɂ���ƍ��̂������Ȃ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rbInfo.scale = scale;
	rbInfo.setambientlight = setambientlight;
	//���̂��쐬����
	rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
	//����
	light.SetAmbientLight(setambientlight);

}

void MapChip::Update()
{
}

void MapChip::Draw()
{
	model.Draw(&scenemanager->GetCamera()->GetViewMatrix(), &scenemanager->GetCamera()->GetProjectionMatrix(),false,true,false);
}