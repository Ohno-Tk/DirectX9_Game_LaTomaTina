/*=============================================================================

		�}�l�[�W��[ Manager.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Input.h"
#include "Sound.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "FileManager.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"
#include "Manager.h"
#include "Mode.h"
#include "TitleScene.h"
#include "Fade.h"
#include "DebugFont.h"
#include "DebugConsole.h"

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
CMode* CManager::m_Mode = new CTitleScene;		//	��ʑJ��
CInputKeyboard* CManager::m_Keyboard = NULL;	//	�L�[�{�[�h
CInputMouse* CManager::m_Mouse = NULL;
#ifdef ENABLE_PEOC_SOUND
	CSound* CManager::m_Sound = NULL;			//	�T�E���h
#endif
CTextureManager* CManager::m_TextureManager = NULL;	//	�e�N�X�`���Ǘ�
CModelManager* CManager::m_ModelManager = NULL;		//	���f���Ǘ�
CFileManager* CManager::m_FileManager = NULL;		//	�t�@�C���Ǘ�
CCamera* CManager::m_Camera = NULL;	//	�J����
CLight* CManager::m_Light = NULL;	//	���C�g
CFade* CManager::m_Fade = NULL;		//	�t�F�[�h

#ifdef ENABLE_PEOC_DEBUGCONSOLE
	CDebugConsole* CManager::m_DebugConsole = NULL;	//	�f�o�b�O�R���\�[��
#endif

int CManager::m_TomatoCont = 0;

/*-----------------------------------------------------------------------------
 �֐���:	void CManager::Init(HINSTANCE hInstance, HWND hWnd)
 ����:		HINSTANCE hInstance		�C���X�^���X
			HWND hWnd				�E�B���h�E�n���h��
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;


	//	DirectX
	hr = CDirectX::Init(hWnd, true);	//	������

	if (FAILED(hr))
	{	//	�G���[�`�F�b�N
		MessageBox(NULL, "DirectX�N���X�̐����Ɏ��s", "Manager.cpp", MB_OK | MB_ICONHAND);
	}

	//	�L�[�{�[�h�̐���
	m_Keyboard = new CInputKeyboard;

	hr = m_Keyboard->Init(hInstance, hWnd);	//	������

	if (FAILED(hr))
	{	//	�G���[�`�F�b�N
		MessageBox(NULL, "�L�[�{�[�h�N���X�̐����Ɏ��s", "Manager.cpp", MB_OK | MB_ICONHAND);
	}

	m_Mouse = new CInputMouse;

	hr = m_Mouse->Init(hInstance, hWnd);
	
#ifdef ENABLE_PEOC_SOUND
	//	�T�E���h�̐���
	m_Sound = new CSound;

	hr = m_Sound->Init();	//	������

	if (FAILED(hr))
	{	//	�G���[�`�F�b�N
		MessageBox(NULL, "�L�[�{�[�h�N���X�̐����Ɏ��s", "Manager.cpp", MB_OK | MB_ICONHAND);
	}
#endif

	//	�e�N�X�`���N���X�̐���
	m_TextureManager = new CTextureManager;

	//	���f���N���X�̐���
	m_ModelManager = new CModelManager;
	m_ModelManager->Init();

	//	�t�@�C���Ǘ��N���X�̐���
	m_FileManager = new CFileManager;

	//	�J�����N���X�̐���
	m_Camera = new CCamera;

	//	���C�g�N���X�̐���
	m_Light = new CLight;
	m_Light->Init();	//	������

	//	�t�F�[�h�N���X�̐���
	m_Fade = CFade::Create();

	CDebugFont::Init();	//	�f�o�b�O�t�H���g�̏�����

	m_Mode->Init();	//	��ʑJ�ڂ̏�����

#ifdef ENABLE_PEOC_DEBUGCONSOLE

	//	�f�o�b�O�R���\�[���N���X�̐���
	m_DebugConsole = new CDebugConsole;
	m_DebugConsole->Init();
#endif
}

/*-----------------------------------------------------------------------------
�֐���:		void CManager::Uninit(void)
����:		
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CManager::Uninit(void)
{
	CDebugFont::Uninit();	//	�f�o�b�O�t�H���g�̏I��

#ifdef ENABLE_PEOC_DEBUGCONSOLE
	if (m_DebugConsole)
	{	//	�f�o�b�O�R���\�[��

		m_DebugConsole->Uninit();	//	�I��
		delete m_DebugConsole;		//	���
		m_DebugConsole = NULL;
	}
#endif

	if (m_Mode)
	{	//	��ʑJ��

		m_Mode->Uninit();	//	�I��
		delete m_Mode;		//	���
		m_Mode = NULL;
	}

	if (m_Fade)
	{	//	�t�F�[�h

		m_Fade->Uninit();	//	�I��
		delete m_Fade;		//	���
		m_Fade = NULL;
	}

	if (m_Light)
	{	//	���C�g

		delete m_Light;
		m_Light = NULL;
	}

	if (m_Camera)
	{	//	�J����

		delete m_Camera;	//	���
		m_Camera = NULL;
	}

	if (m_FileManager)
	{
		delete m_FileManager;
		m_FileManager = NULL;
	}

	if (m_ModelManager)
	{	//	���f��

		m_ModelManager->UnloadAll();
		delete m_ModelManager;	//	���
		m_ModelManager = NULL;
	}

	if (m_TextureManager)
	{	//	�e�N�X�`��

		m_TextureManager->UnloadAll();	//	�S�e�N�X�`���̔j��
		delete m_TextureManager;		//	���
		m_TextureManager = NULL;
	}

	if (m_Sound)
	{	//	�T�E���h

		m_Sound->Uninit();
		delete m_Sound;		//	�I��
		m_Sound = NULL;		//	���
	}

	if (m_Mouse)
	{
		m_Mouse->Uninit();
		delete m_Mouse;
		m_Mouse = NULL;
	}

	if (m_Keyboard)
	{	//	�L�[�{�[�h

		m_Keyboard->Uninit();	//	�I��
		delete m_Keyboard;		//	���
		m_Keyboard = NULL;
	}

	CDirectX::Uninit();	//	DirectX�̏I��
}

/*-----------------------------------------------------------------------------
�֐���:		void CManager::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CManager::Update(void)
{
	m_Keyboard->Update();	//	�L�[�{�[�h�̍X�V

	m_Mouse->Update();

	m_Camera->Update();		//	�J�����̍X�V

	m_Fade->Update();		//	�t�F�[�h�̍X�V

	m_Mode->Update();		//	��ʑJ�ڂ̍X�V
}

/*-----------------------------------------------------------------------------
�֐���:		void CManager::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CManager::Draw(void)
{
	CDirectX::DrawBegin();		//	�`��̊J�n

	m_Mode->Draw();				//	��ʑJ�ڂ̕`��

	m_Fade->Draw();				//	�t�F�[�h�̕`��

	CDebugFont::Draw();			//	�f�o�b�O�t�H���g�̕`��

	CDirectX::DrawEnd();		//	�`��̏I��
}

/*-----------------------------------------------------------------------------
�֐���:		void CManager::SetMode(CMode *Mode)
����:
�߂�l:
����:		��ʑJ�ڂ̐؂�ւ�
-----------------------------------------------------------------------------*/
void CManager::SetMode(CMode *Mode)
{
	if (!m_Mode) return;

	m_Mode->Uninit();	//	�I��

	delete m_Mode;		//	���
	m_Mode = NULL;

	//	�V�������[�h�̐ݒ�
	m_Mode = Mode;

	m_Mode->Init();		//	������
}