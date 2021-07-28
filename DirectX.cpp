/*=============================================================================

		DirectX�ݒ�[ DirectX.cpp ]

-------------------------------------------------------------------------------
	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "GameLoop.h"

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
D3DXCOLOR CDirectX::m_BackBufferColor = D3DCOLOR_RGBA(0, 177, 184, 255);//	�o�b�N�o�b�t�@�F
LPDIRECT3D9 CDirectX::m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9 CDirectX::m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g

#ifdef _DEBUG
LPD3DXFONT CDirectX::m_Font = NULL;	// �t�H���g�ւ̃|�C���^
#endif

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT CDirectX::Init(HWND Wnd, bool Window)
 ����:		HWND Wnd		�E�B���h�E�n���h��
			bool Window		�E�B���h�E���[�h
 �߂�l:	return S_OK;	����
			return E_FAIL;	���s
 ����:		������
-----------------------------------------------------------------------------*/
HRESULT CDirectX::Init(HWND Wnd, bool Window)
{
	HRESULT hr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	D3DDISPLAYMODE d3ddm = {};


	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_pD3D)
	{	//	�k���`�F�b�N

		MessageBox(NULL, "Direct3D�I�u�W�F�N�g�̍쐬�Ɏ��s", "DirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	hr = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	if (FAILED(hr))
	{
		MessageBox(NULL, "�f�B�X�v���C���[�h�̎擾�Ɏ��s", "DirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	SetUpDevice(d3dpp, d3ddm, Wnd, Window);	//	�f�o�C�X�̏�����

	SetRenderState();	//	�����_�[�X�e�[�g�̐ݒ�

	SetSamplerState();	//	�T���v���[�X�e�[�g�̐ݒ�

	SetTextureStageState();	//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�𐶐�
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
#endif

	return S_OK;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::Uninit(void)
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void CDirectX::Uninit(void)
{
#ifdef _DEBUG
	if (m_Font)
	{	// ���\���p�t�H���g
		m_Font->Release();	//	���
		m_Font = NULL;
	}

#endif

	if(m_pD3D)
	{	//	Direct3D�I�u�W�F�N�g�̔j��

		m_pD3D->Release();	//	���
		m_pD3D = NULL;
	}

	if(m_pD3DDevice)
	{	// �f�o�C�X�̔j��

		m_pD3DDevice->Release();	//	���
		m_pD3DDevice = NULL;
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::DrawBegin(void)
 ����:		
 �߂�l:	
 ����:		�`��̊J�n
-----------------------------------------------------------------------------*/
void CDirectX::DrawBegin(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), m_BackBufferColor, 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	m_pD3DDevice->BeginScene();
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::DrawEnd(void)
 ����:		
 �߂�l:	
 ����:		�`��̏I��
-----------------------------------------------------------------------------*/
void CDirectX::DrawEnd(void)
{
#ifdef _DEBUG

	DrawFPS();	// FPS�\��

#endif

	// Direct3D�ɂ��`��̏I��
	m_pD3DDevice->EndScene();

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
 ����:		D3DPRESENT_PARAMETERS d3dpp
			D3DDISPLAYMODE d3ddm
			HWND Wnd						�E�B���h�E�n���h��
			bool Window						�E�B���h�E���[�h
 �߂�l:	
 ����:		�f�o�C�X�̏�����
-----------------------------------------------------------------------------*/
void CDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
{
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = Window;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��


	HRESULT hr;


	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Wnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice);
	if (FAILED(hr))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			Wnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice);
		if (FAILED(hr))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, Wnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice);
			if (FAILED(hr))
			{

				MessageBox(NULL, "�f�o�C�X�̐����Ɏ��s", "DirectX.cpp", MB_OK | MB_ICONHAND);
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::SetRenderState(void)
 ����:		
 �߂�l:	
 ����:		�����_�[�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void CDirectX::SetRenderState(void)
{
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
}

/*-----------------------------------------------------------------------------
 �֐���:	void CDirectX::SetRenderState(void)
 ����:		
 �߂�l:	
 ����:		�T���v���[�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void CDirectX::SetSamplerState(void)
{
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�
}

/*-----------------------------------------------------------------------------
 �֐���:	void SetRenderState(void)
 ����:		
 �߂�l:	
 ����:		�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void CDirectX::SetTextureStageState(void)
{
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����(�����l��D3DTOP_SELECTARG1)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����(�����l��D3DTA_TEXTURE�A�e�N�X�`�����Ȃ��ꍇ��D3DTA_DIFFUSE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// �Q�Ԗڂ̃A���t�@����(�����l��D3DTA_CURRENT)
}

#ifdef _DEBUG
/*-----------------------------------------------------------------------------
�֐���:		void CDirectX::DrawFPS(void)
����:
�߂�l:
����:		FPS�\��
-----------------------------------------------------------------------------*/
void CDirectX::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS�擾
	nCountFPS = CGameLoop::GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_Font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif