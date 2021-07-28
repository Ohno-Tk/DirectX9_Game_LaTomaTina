/*=============================================================================

		�}�l�[�W��[ Manager.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _MANAGER_H_
#define _MANAGER_H_

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define ENABLE_PEOC_SOUND	//	Sound
//#undef ENABLE_PEOC_SOUND

#define ENABLE_PEOC_DEBUGCONSOLE	//	�f�o�b�O�R���\�[��
#undef ENABLE_PEOC_DEBUGCONSOLE

/*-----------------------------------------------------------------------------
	�O���錾
-----------------------------------------------------------------------------*/
class CMode;			//	��ʑJ��
class CInputKeyboard;	//	�L�[�{�[�h
class CInputMouse;
#ifdef ENABLE_PEOC_SOUND
	class CSound;		//	�T�E���h
#endif
class CTextureManager;	//	�e�N�X�`���Ǘ�
class CModelManager;	//	���f���Ǘ�
class CFileManager;		//	�t�@�C���Ǘ�
class CCamera;			//	�J����
class CLight;			//	���C�g
class CFade;			//	�t�F�[�h
#ifdef ENABLE_PEOC_DEBUGCONSOLE
	class CDebugConsole;	//	�f�o�b�O�R���\�[��
#endif

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CManager
{
public:
	void Init(HINSTANCE hInstance, HWND hWnd);	//	������
	void Uninit(void);	//	�I��
	void Update(void);	//	�X�V
	void Draw(void);	//	�`��

	static void SetMode(CMode *Mode);	//	��ʑJ�ڂ̐؂�ւ�

	//	Setter
	static void SetTomatoCount(const int count) { m_TomatoCont = count; }

	//	Getter
	static CInputKeyboard* GetKeyboard(void) { return m_Keyboard; }	//	�L�[�{�[�h
	static CInputMouse* GetMouse(void) { return m_Mouse; }
	static CSound* GetSound(void) { return m_Sound; }				//	�T�E���h
	static CTextureManager* GetTextureManager(void) { return m_TextureManager; }	//	�e�N�X�`���Ǘ�
	static CModelManager* GetModelManager(void) { return m_ModelManager; }	//	���f���Ǘ�
	static CFileManager* GetFileManager(void) { return m_FileManager; }		//	�t�@�C���Ǘ�
	static CCamera* GetCamera(void) { return m_Camera; }			//	�J����


	static int GetTomatoCount(void) { return m_TomatoCont; }

private:
	static CMode* m_Mode;				//	��ʑJ��	
	static CInputKeyboard* m_Keyboard;	//	�L�[�{�[�h
	static CInputMouse* m_Mouse;
#ifdef ENABLE_PEOC_SOUND
	static CSound* m_Sound;				//	�T�E���h
#endif
	static CTextureManager* m_TextureManager;	//	�e�N�X�`���Ǘ�
	static CModelManager* m_ModelManager;		//	���f���Ǘ�
	static CFileManager* m_FileManager;			//	�t�@�C���Ǘ�
	static CCamera* m_Camera;					//	�J����
	static CLight* m_Light;						//	���C�g
	static CFade* m_Fade;						//	�t�F�[�h
#ifdef ENABLE_PEOC_DEBUGCONSOLE
	static CDebugConsole* m_DebugConsole;		//	�f�o�b�O�R���\�[��
#endif

	static int m_TomatoCont;
};
#endif
