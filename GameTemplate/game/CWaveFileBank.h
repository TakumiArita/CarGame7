#pragma once
#include <map>

class CWaveFile;
class NameKey;
class CUtil;
typedef std::shared_ptr<CWaveFile>	CWaveFilePtr;
typedef std::map<unsigned int, CWaveFilePtr>	CWaveFilePtrMap;
/*!
*@brief	波形データバンク。
*@details
* 一度ロードされた波形データをバンクに登録することが出来ます。
* 登録された波形データは再読み込みを行う必要がなく、バンクから再利用することが出来ます。
*/
class CWaveFileBank
{
public:
	CWaveFileBank();
	~CWaveFileBank();
	/*!
	*@brief	波形データを登録。
	*@param[in]	groupID		グループＩＤ。指定できるＩＤの最大値はMAX_GROUP-1。
	*@param[in]	waveFile	波形データ。
	*/
	void RegistWaveFile(int groupID, CWaveFilePtr waveFile);
	/*!
	*@brief	引数で指定したファイルパスの波形データがバンクに登録されているか検索する。
	*@param[in]	groupID		グループＩＤ。指定できるＩＤの最大値はMAX_GROUP-1。
	*@param[in]	filePath	ファイルパス。
	*@return 波形データ。登録されていない場合はNULLが返る。
	*/
	CWaveFilePtr FindWaveFile(int groupID, const char* filePath);
	/*!
	*@brief	引数で指定したファイルパスの波形データがバンクに登録されているか検索する。
	*@details
	*  こっちのほうが少しだけ早い。
	*@param[in]	groupID		グループＩＤ。指定できるＩＤの最大値はMAX_GROUP-1。
	*@param[in]	nameyKey	名前キー。。
	*@return 波形データ。登録されていない場合はNULLが返る。
	*/
	CWaveFilePtr FindWaveFile(int groupID, const NameKey& nameKey);
	/*!
	*@brief	グループ単位で解放。
	*/
	void Release(int groupID);
	/*!
	*@brief	全て解放。
	*/
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++) {
			Release(i);
		}
	}
private:
	static const int MAX_GROUP = 256;
	CWaveFilePtrMap	m_waveFileMap[MAX_GROUP];		//!<waveファイルのリスト。
};



/*!
* @brief	ユーティリティ関数。
*/
class CUtil {
public:
	/*!
	* @brief	文字列から32bitのハッシュ値を作成。
	*/
	static int MakeHash(const char* string)
	{
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}
};


class NameKey {
	std::string name;			//!<名前
	unsigned int hashCode = 0;	//!<ハッシュ値。
public:
	NameKey() {}
	NameKey(const char* name)
	{
		Init(name);
	}
	//初期化。
	void Init(const char* name)
	{
		if (name != nullptr) {
			this->name = name;
			//名前をハッシュ値に変換。
			hashCode = CUtil::MakeHash(name);
		}
	}
	//ハッシュコードを取得。
	unsigned int GetHashCode() const
	{
		return hashCode;
	}
	//名前を取得。
	const char* GetName() const
	{
		return name.c_str();
	}
};
