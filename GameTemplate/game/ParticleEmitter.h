#pragma once
#include <list>
#include <d3d9.h>
#include <d3dx9effect.h>
class Particle;
/*
* @brief    �p�[�e�B�N�������p�����[�^�B
*/
struct SParticleEmitParameter {
	//�������B
	void Init()
	{
		memset(this, 0, sizeof(SParticleEmitParameter));
	}
	const char* texturePath;            //�e�N�X�`���̃t�@�C���p�X�B
	float w;                            //�p�[�e�B�N���̕��B
	float h;							//�p�[�e�B�N���̍����B
	float intervalTime;                 //�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3 initSpeed;				//�����x�B
	D3DXVECTOR3 position;               //���W
};
/*
*  @brief    �p�[�e�B�N���̔����@
*/
class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	/*
	* @brief    �������B
	*@param[in]     camera        �p�[�e�B�N���̕`��Ŏg�p����J�����B
	*@param[in]     param         �p�[�e�B�N�������p�̃p�����[�^
	*/

	void Init(const SParticleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParticleEmitParameter   param;            //�p�����[�^�B
	std::list<Particle*>   particleList;       //�p�[�e�B�N���̃��X�g�B
	float timer;                                //�^�C�}�[�B

};

