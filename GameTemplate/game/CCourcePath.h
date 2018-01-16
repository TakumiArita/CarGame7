#pragma once
struct CMapChipLocInfo { 
	const char*     modelName;     //モデル。
	D3DXVECTOR3     pos;           //座標。
	D3DXQUATERNION  rotation;	   //回転。
	D3DXVECTOR3     scale;         //大きさ

};
class CCourcePath
{
public:
	struct SCourceEdge {
		D3DXVECTOR3 startPos;		//コースパスのエッジの始点。
		D3DXVECTOR3 endPos;			//コースパスのエッジの終点。
		D3DXVECTOR3 startToEnd;		//始点から終点に向かうベクトル。
		D3DXVECTOR3 direction;		//エッジの向き。
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
	//コースパスのリスト
	std::vector<SCourceEdge> courceEdigeList;	//コースパスのエッジのリスト。

	D3DXVECTOR3       m_startPos;         //コースパスのエッジの始点。
	D3DXVECTOR3       m_endPos;           //コースパスのエッジの終点。
	D3DXVECTOR3       m_startToEnd;		  //始点から終点に向かうベクトル。
	D3DXVECTOR3       m_direction;		  //エッジの向き。

	int numObject;	                      //配置してるオブジェクトの数を計算する

};

