/*=============================================================================

		���C���֐�[ main.cpp ]

-------------------------------------------------------------------------------
	���@�쐬��
		2017/08/24
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
						scanf ��warning�h�~ 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "GameLoop.h"
#include "resource.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define CLASS_NAME     "TGS"	//	�E�C���h�E�N���X�̖��O
#define WINDOW_NAME    "La TomaTina"	//	�E�C���h�E�̖��O

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

void Init(void);	//	������
bool Loop(void);	//	���[�v
int Uninit(void);	//	�I��

void SetupWindow(void);	//	�E�B���h�E������
void MakeWindow(void);	//	�E�B���h�E����

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
WNDCLASSEX g_Wcex = {};
MSG g_Msg = {};
HINSTANCE g_Instance = NULL;
HWND g_hWnd = NULL;	//	�E�C���h�E�n���h��( ���C���n���h�� )
int g_CmdShow = 0;

/*-----------------------------------------------------------------------------
	���C���֐�
-----------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{

	g_Instance = hInstance;
	g_CmdShow = nCmdShow;

	//  waring�̌x����������
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( IpCmdLine );

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Init();	//	������

	while(Loop());	//	���[�v

	int Param = Uninit();	//	�I��

	_CrtDumpMemoryLeaks();

	return Param;
}

/*-----------------------------------------------------------------------------
				�E�C���h�E�v���V�[�W��
		( CALLBACK:Win32API�֐����Ăяo���Ƃ��̋K�� )
		hWnd :   �E�C���h�E�̃n���h��
		uMsg :   ���b�Z�[�W�̎��ʎq
		wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
		lParam : ���b�Z�[�W�̂Q�Ԗڂ̃p�����[�^
-------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{

	UINT nSelect;

	static HDC hDC;
	static PAINTSTRUCT ps;	//	�`����i�[�p

	switch( uMsg )
	{

	case WM_DESTROY:										//	�E�C���h�E�j���̃��b�Z�[�W

		PostQuitMessage( 0 );								//	"WM_QUIT"���b�Z�[�W��Ԃ�

		break;

	case WM_KEYDOWN:	//	�L�[����

		switch( wParam )
		{

			case VK_ESCAPE:	//	ESCAPE�L�[

			nSelect = MessageBox( NULL , "�I�����܂����H" , "�I�����b�Z�[�W" , MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 );

			if( nSelect == IDYES )
			{

				DestroyWindow( hWnd );

			}

			break;

		}

	case WM_CLOSE:
		break;

	default:
		break;

	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );	//	����̏������

}

void Init(void)
{
	SetupWindow();	//	�E�B���h�E������

	MakeWindow();	//	�E�B���h�E����

	CGameLoop::Init(g_Instance, g_hWnd);	//	�Q�[�����[�v�̏�����
}

bool Loop(void)
{
	//	���b�Z�[�W���[�v
	//	��P�����F���b�Z�[�W���
	//	��Q�����F�E�C���h�E�̃n���h��
	//	��R�����F�ŏ��̃��b�Z�[�W
	//	��S�����F�Ō�̃��b�Z�[�W
	if(PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		//	Windows�̏���
		if(g_Msg.message == WM_QUIT) return false;

		else
		{
			//	�Ăяo�����X���b�h�̃��b�Z�[�W�L���[����
			//	���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&g_Msg);
			DispatchMessage(&g_Msg);
		}
	}
	else
	{
		CGameLoop::ClockFps();
	}

	return true;
}

int Uninit(void)
{
	CGameLoop::Uninit();	//	�Q�[�����[�v�̏I��

	//	�E�C���h�E�N���X�̓o�^������
	//	�������F���N���X��
	//	�������F�A�v���P�[�V�����C���X�^���X
	UnregisterClass( CLASS_NAME , g_Wcex.hInstance );

	return (int)g_Msg.wParam;
}

void SetupWindow(void)
{
	//	�E�C���h�E�̃p�[�c�o�^
	g_Wcex.cbSize = sizeof(WNDCLASSEX);					//	WNDCLASSEX�̃������T�C�Y���w��
	g_Wcex.style = CS_CLASSDC;							//	�\������E�C���h�E�̃X�^�C����ݒ�
	g_Wcex.lpfnWndProc = WndProc;						//	�E�B���h�E�v���V�[�W���̃A�h���X( �֐��� )���w��@�v���g�^�C�v�錾�����֐��������i�d�v�I�I�j
	g_Wcex.cbClsExtra = 0;								//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
	g_Wcex.cbWndExtra = 0;								//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
	g_Wcex.hInstance = g_Instance;						//	WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
	//g_Wcex.hIcon = NULL;								//	�g�p����A�C�R�����w��( Windows�������Ă���A�C�R�����g���Ȃ� )
	g_Wcex.hIcon = LoadIcon(g_Instance,MAKEINTRESOURCE(IDI_ICON1));
	g_Wcex.hCursor = LoadCursor(NULL, IDC_ARROW);		//	�}�E�X�J�[�\�����w��	�i���Ƃł͂��Ȃ��j
	g_Wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//	�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�	�i���Ƃł͂��Ȃ��j
	g_Wcex.lpszMenuName = NULL;							//	Windows�ɂ��郁�j���[��ݒ�
	g_Wcex.lpszClassName = CLASS_NAME;					//	�E�C���h�E�N���X�̖��O	�i�d�v�I�I�j
	g_Wcex.hIconSm = NULL;								//	�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q	�i���Ƃł͂��Ȃ��j

	//	�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&g_Wcex);	//	�I���W�i���̃E�C���h�E�p�[�c�̖��O������( �J�X�^���E�C���h�E�p�̐ݒ� )
}

void MakeWindow(void)
{
	const int Windowstyle = WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_THICKFRAME;

//	const int Windowstyle = WS_OVERLAPPEDWINDOW ^  WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME;

	//	�`��̈�̃T�C�Y����E�C���h�E�̋�`���擾
	RECT cr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect( &cr , Windowstyle , FALSE );

	RECT dr;
	GetWindowRect( GetDesktopWindow() , &dr );

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	int wx = ww > dw ? 0 : ( dw - ww ) / 2 ;
	int wy = wh > dh ? 0 : ( dh - wh ) / 2 ;

	//	�E�C���h�E�̍쐬
	g_hWnd = CreateWindowEx( 0 ,	//	�g���E�C���h�E�X�^�C���i�@������Ɛݒ肷��@�j
		CLASS_NAME ,				//	�E�C���h�E�N���X�̖��O
		WINDOW_NAME ,				//	�E�C���h�E�̖��O
		Windowstyle ,				//	�E�C���h�E�X�^�C��
		wx ,						//	�E�C���h�E�̍���w���W
		wy ,						//	�E�C���h�E�̍���x���W
		ww ,						//	�E�C���h�E�̕��i�@�t���[�������킹�����@�j
		wh ,						//	�E�C���h�E�̍����i�@�t���[�������킹�������@�j
		NULL ,						//	�e�E�C���h�E�̃n���h���i�@�|�C���^�@�j
		NULL ,						//	���j���[�n���h���܂��͎q�E�C���h�EID
		g_Instance ,					//	�C���X�^���X�n���h��
		NULL );						//	�E�C���h�E�쐬�f�[�^

	//	�E�C���h�E�̕\��
	ShowWindow( g_hWnd , g_CmdShow );	//	�w�肳�ꂽ�E�C���h�E�̕\��
	UpdateWindow( g_hWnd );				//	�E�C���h�E�̏�Ԃ𒼂��ɔ��f
}
