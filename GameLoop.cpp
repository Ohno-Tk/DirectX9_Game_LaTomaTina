/*=============================================================================

		�Q�[�����[�v[ GameLoop.cpp ]

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
#include "GameLoop.h"
#include "Manager.h"

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
DWORD CGameLoop::m_dwFrameCount = 0;
DWORD CGameLoop::m_dwCurrentTime = 0;	//	���݂̎���
DWORD CGameLoop::m_dwExecLastTime = 0;	//	���݂̎������~���P�ʂŎ擾
DWORD CGameLoop::m_dwFPSLastTime = 0;
int CGameLoop::m_nCountFPS = 0;			//	FPS�J�E���^
CManager* CGameLoop::m_Manager = NULL;	//	�}�l�[�W��

/*-----------------------------------------------------------------------------
 �֐���:	
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void CGameLoop::Init(HINSTANCE hInstance, HWND hWnd)
{
	//	����\�̐ݒ�i�^�C�}�[�̐��x��ǂ�����j
	timeBeginPeriod(1);

	//	�e�J�E���^�[�̏�����
	m_dwFrameCount = 0;
	m_dwCurrentTime = 0;				//	���݂̎���
	m_dwExecLastTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾
	m_dwFPSLastTime = m_dwExecLastTime;

	m_Manager = new CManager;
	m_Manager->Init(hInstance, hWnd);
}

/*-----------------------------------------------------------------------------
�֐���:		void CGameLoop::ClockFps(void)
����:
�߂�l:
����:		FPS�v��
-----------------------------------------------------------------------------*/
void CGameLoop::ClockFps(void)
{
	m_dwCurrentTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾

	if ((m_dwCurrentTime - m_dwFPSLastTime) >= 500)
	{

		m_nCountFPS = (m_dwFrameCount * 1000) / (m_dwCurrentTime - m_dwFPSLastTime);
		m_dwFPSLastTime = m_dwCurrentTime;
		m_dwFrameCount = 0;

	}

	if ((m_dwCurrentTime - m_dwExecLastTime) >= (1000 / 60))
	{	//	���݂̃t���[������ǂ�ʂ������̂�( �����v�Z )	�f�o�b�O�Ōv���������Ƃ���if���R�����g�A�E�g

		m_dwExecLastTime = m_dwCurrentTime;	//	�����������Ԃ�ۑ�

		//	DirectX�̏����i�Q�[�������j

		// �X�V����
		m_Manager->Update();

		// �`�揈��
		m_Manager->Draw();

		m_dwFrameCount++;

	}
}

/*-----------------------------------------------------------------------------
�֐���:		void CGameLoop::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CGameLoop::Uninit(void)
{
	if(m_Manager)
	{		
		m_Manager->Uninit();	//	�I������
		delete m_Manager;		//	���
		m_Manager = NULL;
	}
}