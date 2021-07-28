/*=============================================================================

		���̓f�o�C�X[ input.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/24
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Input.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define	COUNT_WAIT_REPEAT	( 20 )	// ���s�[�g�҂�����
#define MOUSE_KEY_MAX ( 8 )	//	�}�E�X�L�[�̍ő吔
#define XBOX_STICK_MAXVALUE ( 20000 )	//	XBOX�X�e�B�b�N�̍ő�l

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
LPDIRECTINPUT8	CInput::m_pDInput = NULL;	// DirectInput�I�u�W�F�N�g

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT CInput::Init( HINSTANCE hInst )
 ����:		HINSTANCE hInst	�C���X�^���X
 �߂�l:	���s	return E_FAIL;
 ����:		���͏����̏���������
-----------------------------------------------------------------------------*/
HRESULT CInput::Init( HINSTANCE hInst )
{

	HRESULT hr = E_FAIL;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if( !m_pDInput )
	{	//	�f�o�C�X������������

		hr = DirectInput8Create( hInst , DIRECTINPUT_VERSION ,
									IID_IDirectInput8 , ( void** )&m_pDInput , NULL );
	}

	return hr;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CInput::Uninit( void )
 ����:		
 �߂�l:	
 ����:		���͏����̏I������
-----------------------------------------------------------------------------*/
void CInput::Uninit( void )
{

	if( m_pDIDevice != NULL )
	{	// �f�o�C�X�I�u�W�F�N�g�̊J��

		m_pDIDevice->Unacquire();	//	�f�o�C�X�ւ̃A�N�Z�X�������

		m_pDIDevice->Release();	// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_pDIDevice = NULL;			// �f�o�C�X�I�u�W�F�N�g��NULL������

	}

	if( m_pDInput != NULL )
	{	// DirectInput�I�u�W�F�N�g�̊J��

		m_pDInput->Release();	// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_pDInput = NULL;		// �f�o�C�X�I�u�W�F�N�g��NULL������

	}
}



/*-----------------------------------------------------------------------------
 �֐���:	CInputKeyboard::CInputKeyboard()
 ����:		
 �߂�l:	
 ����:		CInputKeyboard�̃R���X�g���N�^
-----------------------------------------------------------------------------*/
CInputKeyboard::CInputKeyboard()
{

	// �e���[�N�̃N���A
	ZeroMemory( m_aKeyState          , sizeof m_aKeyState );
	ZeroMemory( m_aKeyStateTrigger   , sizeof m_aKeyStateTrigger );
	ZeroMemory( m_aKeyStateRelease   , sizeof m_aKeyStateRelease );
	ZeroMemory( m_aKeyStateRepeat    , sizeof m_aKeyStateRepeat );
	ZeroMemory( m_aKeyStateRepeatCnt , sizeof m_aKeyStateRepeatCnt );

}

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
 ����:		HINSTANCE hInst
			HWND hWnd
 �߂�l:	����	return S_OK;
			���s	return E_FAIL;
 ����:		�L�[�{�[�h�̏���������
-----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
{

	HRESULT hr;

	// ���͏����̏�����
	CInput::Init( hInst );

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice( GUID_SysKeyboard , &m_pDIDevice , NULL );
	if (FAILED( hr ) || m_pDIDevice == NULL )
	{

		MessageBox( hWnd , "�L�[�{�[�h���˂��I" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat( &c_dfDIKeyboard );
	if( FAILED( hr ) )
	{

		MessageBox( hWnd , "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) )
	{

		MessageBox( hWnd , "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}


	// m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	m_pDIDevice->Acquire();

	return hr;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CInputKeyboard::Update( void )
 ����:		
 �߂�l:	
 ����:		�L�[�{�[�h�̍X�V����
-----------------------------------------------------------------------------*/
void CInputKeyboard::Update( void )
{

	HRESULT hr;
	BYTE aKeyState[ NUM_KEY_MAX ];

	if( !m_pDIDevice ) return;

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState( sizeof( aKeyState ) , aKeyState );
	if( SUCCEEDED( hr ) )
	{

		for( int nCntKey = 0 ; nCntKey < NUM_KEY_MAX ; nCntKey++ )
		{

			// �L�[�g���K�[ �����[�X���̍쐬
			// 1�t���[���O�̃L�[�󋵂ƍ��̃L�[�󋵂�XOR�������̂����̃L�[�󋵂�AND���Ƃ�
			m_aKeyStateTrigger[ nCntKey ] = ( m_aKeyState[ nCntKey ] ^ aKeyState[ nCntKey ] ) & aKeyState[ nCntKey ];
			m_aKeyStateRelease[ nCntKey ] = ( m_aKeyState[ nCntKey ] ^ aKeyState[ nCntKey ] ) & ~aKeyState[ nCntKey ];
			m_aKeyStateRepeat[ nCntKey ] = m_aKeyStateTrigger[ nCntKey ];

			// �L�[���s�[�g���̐���
			if( aKeyState[ nCntKey ] )
			{

				m_aKeyStateRepeatCnt[ nCntKey ]++;

				if( m_aKeyStateRepeatCnt[ nCntKey ] >= COUNT_WAIT_REPEAT )
				{

					m_aKeyStateRepeat[ nCntKey ] = aKeyState[ nCntKey ];

				}
			}
			else
			{

				m_aKeyStateRepeatCnt[ nCntKey ] = 0;
				m_aKeyStateRepeat[ nCntKey ] = 0;

			}

			// �L�[����ۑ�
			m_aKeyState[ nCntKey ] = aKeyState[ nCntKey ];

		}
	}

	else
	{
		m_pDIDevice->Acquire();	// m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	}
}


/*-----------------------------------------------------------------------------
 �֐���:	HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
 ����:		HINSTANCE hInst
			HWND hWnd
 �߂�l:	����	return S_OK;
			���s	return E_FAIL;
 ����:		�}�E�X�̏�����
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Init( HINSTANCE hInst, HWND hWnd )
{

	HRESULT hr;

	// ���͏����̏�����
	CInput::Init( hInst );

	// �f�o�C�X�I�u�W�F�N�g�𐶐�
	hr = m_pDInput->CreateDevice( GUID_SysMouse ,&m_pDIDevice , NULL );
	if( FAILED( hr ) || m_pDIDevice == NULL )
	{
		MessageBox( hWnd, "�}�E�X���˂�", "Input.cpp", MB_OK );
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g���w��
	hr = m_pDIDevice->SetDataFormat( &c_dfDIMouse2 );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g", "Input.cpp", MB_OK );
		return hr;
	}

	// �������[�h��ݒ�(�t�H�A�O�����h����r��
	hr = m_pDIDevice->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�}�E�X�̋������[�h��ݒ�", "Input.cpp", MB_OK );
		return hr;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof( dipdw );
	dipdw.diph.dwHeaderSize = sizeof( dipdw.diph );
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_pDIDevice->SetProperty( DIPROP_AXISMODE, &dipdw.diph );

	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�}�E�X�̃f�o�C�X�ݒ�Ɏ��s", "Input.cpp", MB_OK );
		return hr;
	}

	// �L�[�{�[�h�փA�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	//	�}�E�X�̎��̏�����
	m_MouseState.lX = ( LONG )0.0f;
	m_MouseState.lY = ( LONG )0.0f;
	m_MouseState.lZ = ( LONG )0.0f;

	return hr;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CInputMouse::Update( void )
 ����:		
 �߂�l:	
 ����:		�}�E�X�̍X�V
-----------------------------------------------------------------------------*/
void  CInputMouse::Update( void )
{

	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if(!m_pDIDevice) return;

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState( sizeof( mouseState ) , &mouseState );

	if( SUCCEEDED( hr ) )
	{
		m_MouseStateTrigger.lX 
			= ( ( m_MouseState.lX ^ mouseState.lX ) & mouseState.lX );
		m_MouseStateTrigger.lY 
			= ( ( m_MouseState.lY ^ mouseState.lY ) & mouseState.lY );
		m_MouseStateTrigger.lZ 
			= ( ( m_MouseState.lZ ^ mouseState.lZ ) & mouseState.lZ );

		for( int nCntKey = 0 ; nCntKey < MOUSE_KEY_MAX ; nCntKey++ )
		{
			m_MouseStateTrigger.rgbButtons[ nCntKey ] 
				= ( ( m_MouseState.rgbButtons[ nCntKey ] ^ mouseState.rgbButtons[ nCntKey ] ) & mouseState.rgbButtons[ nCntKey ] );
		}

		m_MouseState = mouseState;

		// �X�N���[�����W���擾
		GetCursorPos( &m_PosMouseWorld );

	}
	else
	{
		m_pDIDevice->Acquire();	// m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	}
}



/*-----------------------------------------------------------------------------
 �֐���:	CXInput::CXInput()
 ����:		
 �߂�l:	
 ����:		CXInput�̃R���X�g���X�^
-----------------------------------------------------------------------------*/
CXInput::CXInput()
{

	// m_state�̃N���A
	ZeroMemory( &m_state , sizeof( XINPUT_STATE ) );

	// m_Vibration�̃N���A
	ZeroMemory( &m_Vibration , sizeof( XINPUT_VIBRATION ) );

	//	�o�C�u���[�V�����̏�����( �͈͂�0�`65535�܂� )
	m_Vibration.wLeftMotorSpeed = 32000;
	m_Vibration.wRightMotorSpeed = 16000;

	m_ControllerNumber = 0;	//	�R���g���[���[�̔ԍ�

}

/*-----------------------------------------------------------------------------
 �֐���:	void CXInput::Update( void )
 ����:		
 �߂�l:	
 ����:		�Q�[���p�b�h( XBOX )�̍X�V
-----------------------------------------------------------------------------*/
void CXInput::Update( void )
{

	//	�Q�[���p�b�h�擾
	XInputGetState(m_ControllerNumber, &m_state );

	//	2�̃A�i���O�X�e�B�b�N���G���Ă��Ȃ��Ƃ���A�X�e�b�N�������ɂ���ꍇ

	//	���X�e�B�b�N
	if( ( m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		  m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) && 
		( m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
	{

		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;

	}

	//	�E�X�e�B�b�N
	if( ( m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) && 
		( m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) ) 
	{

		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;

	}


	WORD aPadState;

	//	�{�^���̎擾
	aPadState = m_state.Gamepad.wButtons;

	// �L�[�g���K�[ �����[�X���̍쐬
	// 1�t���[���O�̃L�[�󋵂ƍ��̃L�[�󋵂�XOR�������̂����̃L�[�󋵂�AND���Ƃ�
	m_aKeyStateTrigger = ( ( m_aKeyState ^ aPadState ) & aPadState );
	m_aKeyStateRelease = ( ( m_aKeyState ^ aPadState ) & m_aKeyState );

	// �L�[���s�[�g���̐���
	if ( aPadState )
	{

		if ( m_aKeyStateRepeatCnt < COUNT_WAIT_REPEAT )
		{

			m_aKeyStateRepeatCnt++;

			if ( m_aKeyStateRepeatCnt == 1 || m_aKeyStateRepeatCnt > COUNT_WAIT_REPEAT )
			{

				m_aKeyStateRepeat = aPadState;

			}
			else
			{

				m_aKeyStateRepeat = 0;

			}
		}
	}
	else
	{

		m_aKeyStateRepeat = 0;
		m_aKeyStateRepeatCnt = 0;

	}

	// �L�[�v���X����ۑ�
	m_aKeyState = aPadState;

	//	�X�e�B�b�N�̒l��-1~1�ɂ���

	m_ThumbLX = m_state.Gamepad.sThumbLX;
	m_state.Gamepad.sThumbLX = ( m_ThumbLX / XBOX_STICK_MAXVALUE ) * -1;

	m_ThumbLY = m_state.Gamepad.sThumbLY;
	m_state.Gamepad.sThumbLY = m_ThumbLY / XBOX_STICK_MAXVALUE;

	m_ThumbRX = m_state.Gamepad.sThumbRX;
	m_state.Gamepad.sThumbRX = ( m_ThumbRX / XBOX_STICK_MAXVALUE ) * -1;

	m_ThumbRY = m_state.Gamepad.sThumbRY;
	m_state.Gamepad.sThumbRY = m_ThumbRY / XBOX_STICK_MAXVALUE;

}