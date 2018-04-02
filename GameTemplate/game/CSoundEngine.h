/*!
* @brief	�T�E���h�G���W��
*/
#include <xaudio2.h>
#pragma once

class CWaveFile;

class CSoundEngine
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/

	CSoundEngine();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CSoundEngine();
	/*!
	* @brief	�������B
	*/
	void Init();
	/*!
	* @brief	�J���B
	*/
	void Release();
	/*!
	* @brief	XAudio2�̃\�[�X�{�C�X���쐬�B
	*/
	//IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile);
	IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile);
private:
	IXAudio2* m_xAudio2 = NULL;
	IXAudio2MasteringVoice* m_masteringVoice = NULL;
};
