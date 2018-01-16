#pragma once
struct CMapChipLocInfo { 
	const char*     modelName;     //���f���B
	D3DXVECTOR3     pos;           //���W�B
	D3DXQUATERNION  rotation;	   //��]�B
	D3DXVECTOR3     scale;         //�傫��

};
class CCourcePath
{
public:
	struct SCourceEdge {
		D3DXVECTOR3 startPos;		//�R�[�X�p�X�̃G�b�W�̎n�_�B
		D3DXVECTOR3 endPos;			//�R�[�X�p�X�̃G�b�W�̏I�_�B
		D3DXVECTOR3 startToEnd;		//�n�_����I�_�Ɍ������x�N�g���B
		D3DXVECTOR3 direction;		//�G�b�W�̌����B
	};
	CCourcePath();
	~CCourcePath();
	void Init(SCourceEdge& courcePath);
	void Update();
	void Draw();

	D3DXVECTOR3 GetStartPos()
	{
		return m_startPos;
	}
	D3DXVECTOR3 GetEndPos()
	{
		return m_endPos;
	}
	D3DXVECTOR3 GetStartToEnd()
	{
		return m_startToEnd;
	}
	D3DXVECTOR3 GetDirection()
	{
		return m_direction;
	}
	SCourceEdge GetCourceEdigeList(int i)
	{
		return courceEdigeList[i];
	}
	int GetNumObject()
	{
		return numObject;
	}

private:
	//�R�[�X�p�X�̃��X�g
	std::vector<SCourceEdge> courceEdigeList;	//�R�[�X�p�X�̃G�b�W�̃��X�g�B

	D3DXVECTOR3       m_startPos;         //�R�[�X�p�X�̃G�b�W�̎n�_�B
	D3DXVECTOR3       m_endPos;           //�R�[�X�p�X�̃G�b�W�̏I�_�B
	D3DXVECTOR3       m_startToEnd;		  //�n�_����I�_�Ɍ������x�N�g���B
	D3DXVECTOR3       m_direction;		  //�G�b�W�̌����B

	int numObject;	                      //�z�u���Ă�I�u�W�F�N�g�̐����v�Z����

};

