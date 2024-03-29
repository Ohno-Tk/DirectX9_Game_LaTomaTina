/*=============================================================================

		�Q�[�����[�v[ GameLoop.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <Windows.h>

/*-----------------------------------------------------------------------------
	�O���錾
-----------------------------------------------------------------------------*/
class CManager;	//	�}�l�[�W��

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CGameLoop
{
public:
	static void Init(HINSTANCE hInstance, HWND hWnd);	//	������
	static void ClockFps(void);	//	FPS�v��
	static void Uninit(void);	//	�I��

	static const int GetFPS(void){ return m_nCountFPS; }	//	FPS�擾

private:
	static DWORD m_dwFrameCount;
	static DWORD m_dwCurrentTime;	//	���݂̎���
	static DWORD m_dwExecLastTime;	//	���݂̎������~���P�ʂŎ擾
	static DWORD m_dwFPSLastTime;
	static int m_nCountFPS;			//	FPS�J�E���^

	static CManager* m_Manager;		//	�}�l�[�W��
};
#endif
