#pragma once

/*!
*@brief	�����_�����O�^�[�Q�b�g�B
*/
class RenderTarget {
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	RenderTarget()
	{
		m_depthSurface = NULL;
		m_texture = NULL;
		m_surface = NULL;
	}
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~RenderTarget()
	{
		Release();
	}
	/*!
	*@brief	����B
	*/
	void Release()
	{
		if (m_texture != nullptr) {
			m_texture->Release();
			m_texture = NULL;
		}
		if (m_depthSurface != nullptr) {
			m_depthSurface->Release();
			m_depthSurface = NULL;
		}
		if (m_surface != NULL) {
			m_surface->Release();
			m_surface = NULL;
		}
	}

	void Create(
		int w, //�����_�����O�^�[�Q�b�g�̉��̉𑜓x�B
		int h, //�����_�����O�^�[�Q�b�g�̏c�̉𑜓x�B
		int mipLevel, //1�ł����B
		D3DFORMAT colorFormat, //DirectX3�̃e�L�X�g��ǂ�Œ��ׂ�B16�r�b�g�̕��������_�o�b�t�@���g���B
		D3DFORMAT depthStencilFormat, //16bit�̐[�x�o�b�t�@�̃t�H�[�}�b�g���w�肷��B
		D3DMULTISAMPLE_TYPE multiSampleType, //D3DMULTISAMPLE_NONE�ł����B
		int multiSampleQuality //0�ł����B
	)
	{
		m_width = w;
		m_height = h;
		//�f�v�X�X�e���V���o�b�t�@�̍쐬�B
		HRESULT hr = g_pd3dDevice->CreateDepthStencilSurface(
			w,
			h,
			static_cast<D3DFORMAT>(depthStencilFormat),
			static_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),
			multiSampleQuality,
			TRUE,
			&m_depthSurface,
			NULL
		);
		//�J���[�o�b�t�@���쐬�B
		hr = g_pd3dDevice->CreateTexture(
			w,
			h,
			mipLevel,
			D3DUSAGE_RENDERTARGET,
			static_cast<D3DFORMAT>(colorFormat),
			D3DPOOL_DEFAULT,
			&m_texture,
			NULL
		);
		m_texture->GetSurfaceLevel(0, &m_surface);
	}
	/*!
	*@brief	�����_�����O�^�[�Q�b�g���擾�B
	*/
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_surface;
	}
	/*!
	*@brief	�f�v�X�X�e���V���o�b�t�@���擾�B
	*/
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_depthSurface;
	}
	/*!
	*@brief	�e�N�X�`�����擾�B
	*/
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_texture;
	}
	/*!
	*@brief	�����擾�B
	*/
	int GetWidth() const
	{
		return m_width;
	}
	/*!
	*@brief	�������擾�B
	*/
	int GetHeight() const
	{
		return m_height;
	}
private:
	LPDIRECT3DSURFACE9		m_depthSurface;		//!<�[�x�o�b�t�@�p�̃T�[�t�F�C�X
	LPDIRECT3DTEXTURE9		m_texture;			//!<�������ݐ�̃e�N�X�`���B
	LPDIRECT3DSURFACE9		m_surface;			//!<�T�[�t�F�C�X
	int						m_width = 0;		//!<��
	int						m_height = 0;		//!<����
};