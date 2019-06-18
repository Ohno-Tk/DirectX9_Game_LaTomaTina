/*=============================================================================

		入力デバイス[ input.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/11/24
-------------------------------------------------------------------------------
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Input.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define	COUNT_WAIT_REPEAT	( 20 )	// リピート待ち時間
#define MOUSE_KEY_MAX ( 8 )	//	マウスキーの最大数
#define XBOX_STICK_MAXVALUE ( 20000 )	//	XBOXスティックの最大値

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
LPDIRECTINPUT8	CInput::m_pDInput = NULL;	// DirectInputオブジェクト

/*-----------------------------------------------------------------------------
 関数名:	HRESULT CInput::Init( HINSTANCE hInst )
 引数:		HINSTANCE hInst	インスタンス
 戻り値:	失敗	return E_FAIL;
 説明:		入力処理の初期化処理
-----------------------------------------------------------------------------*/
HRESULT CInput::Init( HINSTANCE hInst )
{

	HRESULT hr = E_FAIL;

	// DirectInputオブジェクトの作成
	if( !m_pDInput )
	{	//	デバイスが無かったら

		hr = DirectInput8Create( hInst , DIRECTINPUT_VERSION ,
									IID_IDirectInput8 , ( void** )&m_pDInput , NULL );
	}

	return hr;
}

/*-----------------------------------------------------------------------------
 関数名:	void CInput::Uninit( void )
 引数:		
 戻り値:	
 説明:		入力処理の終了処理
-----------------------------------------------------------------------------*/
void CInput::Uninit( void )
{

	if( m_pDIDevice != NULL )
	{	// デバイスオブジェクトの開放

		m_pDIDevice->Unacquire();	//	デバイスへのアクセス権を解放

		m_pDIDevice->Release();	// デバイスオブジェクトの開放
		m_pDIDevice = NULL;			// デバイスオブジェクトにNULLを入れる

	}

	if( m_pDInput != NULL )
	{	// DirectInputオブジェクトの開放

		m_pDInput->Release();	// デバイスオブジェクトの開放
		m_pDInput = NULL;		// デバイスオブジェクトにNULLを入れる

	}
}



/*-----------------------------------------------------------------------------
 関数名:	CInputKeyboard::CInputKeyboard()
 引数:		
 戻り値:	
 説明:		CInputKeyboardのコンストラクタ
-----------------------------------------------------------------------------*/
CInputKeyboard::CInputKeyboard()
{

	// 各ワークのクリア
	ZeroMemory( m_aKeyState          , sizeof m_aKeyState );
	ZeroMemory( m_aKeyStateTrigger   , sizeof m_aKeyStateTrigger );
	ZeroMemory( m_aKeyStateRelease   , sizeof m_aKeyStateRelease );
	ZeroMemory( m_aKeyStateRepeat    , sizeof m_aKeyStateRepeat );
	ZeroMemory( m_aKeyStateRepeatCnt , sizeof m_aKeyStateRepeatCnt );

}

/*-----------------------------------------------------------------------------
 関数名:	HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
 引数:		HINSTANCE hInst
			HWND hWnd
 戻り値:	成功	return S_OK;
			失敗	return E_FAIL;
 説明:		キーボードの初期化処理
-----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
{

	HRESULT hr;

	// 入力処理の初期化
	CInput::Init( hInst );

	// デバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice( GUID_SysKeyboard , &m_pDIDevice , NULL );
	if (FAILED( hr ) || m_pDIDevice == NULL )
	{

		MessageBox( hWnd , "キーボードがねぇ！" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}

	// データフォーマットを設定
	hr = m_pDIDevice->SetDataFormat( &c_dfDIKeyboard );
	if( FAILED( hr ) )
	{

		MessageBox( hWnd , "キーボードのデータフォーマットを設定できませんでした。" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) )
	{

		MessageBox( hWnd , "キーボードの協調モードを設定できませんでした。" , "Input.cpp" , MB_ICONWARNING );
		return hr;
	}


	// m_pDIDeviceアクセス権を獲得( 入力制御開始 )
	m_pDIDevice->Acquire();

	return hr;
}

/*-----------------------------------------------------------------------------
 関数名:	void CInputKeyboard::Update( void )
 引数:		
 戻り値:	
 説明:		キーボードの更新処理
-----------------------------------------------------------------------------*/
void CInputKeyboard::Update( void )
{

	HRESULT hr;
	BYTE aKeyState[ NUM_KEY_MAX ];

	if( !m_pDIDevice ) return;

	// デバイスからデータを取得
	hr = m_pDIDevice->GetDeviceState( sizeof( aKeyState ) , aKeyState );
	if( SUCCEEDED( hr ) )
	{

		for( int nCntKey = 0 ; nCntKey < NUM_KEY_MAX ; nCntKey++ )
		{

			// キートリガー リリース情報の作成
			// 1フレーム前のキー状況と今のキー状況をXORしたものを今のキー状況とANDをとる
			m_aKeyStateTrigger[ nCntKey ] = ( m_aKeyState[ nCntKey ] ^ aKeyState[ nCntKey ] ) & aKeyState[ nCntKey ];
			m_aKeyStateRelease[ nCntKey ] = ( m_aKeyState[ nCntKey ] ^ aKeyState[ nCntKey ] ) & ~aKeyState[ nCntKey ];
			m_aKeyStateRepeat[ nCntKey ] = m_aKeyStateTrigger[ nCntKey ];

			// キーリピート情報の生成
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

			// キー情報を保存
			m_aKeyState[ nCntKey ] = aKeyState[ nCntKey ];

		}
	}

	else
	{
		m_pDIDevice->Acquire();	// m_pDIDeviceアクセス権を獲得( 入力制御開始 )
	}
}


/*-----------------------------------------------------------------------------
 関数名:	HRESULT CInputKeyboard::Init( HINSTANCE hInst , HWND hWnd )
 引数:		HINSTANCE hInst
			HWND hWnd
 戻り値:	成功	return S_OK;
			失敗	return E_FAIL;
 説明:		マウスの初期化
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Init( HINSTANCE hInst, HWND hWnd )
{

	HRESULT hr;

	// 入力処理の初期化
	CInput::Init( hInst );

	// デバイスオブジェクトを生成
	hr = m_pDInput->CreateDevice( GUID_SysMouse ,&m_pDIDevice , NULL );
	if( FAILED( hr ) || m_pDIDevice == NULL )
	{
		MessageBox( hWnd, "マウスがねぇ", "Input.cpp", MB_OK );
		return hr;
	}

	// データフォーマットを指定
	hr = m_pDIDevice->SetDataFormat( &c_dfDIMouse2 );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "マウスのデータフォーマット", "Input.cpp", MB_OK );
		return hr;
	}

	// 協調モードを設定(フォアグランド＆非排他
	hr = m_pDIDevice->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "マウスの協調モードを設定", "Input.cpp", MB_OK );
		return hr;
	}

	// デバイスの設定
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof( dipdw );
	dipdw.diph.dwHeaderSize = sizeof( dipdw.diph );
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_pDIDevice->SetProperty( DIPROP_AXISMODE, &dipdw.diph );

	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "マウスのデバイス設定に失敗", "Input.cpp", MB_OK );
		return hr;
	}

	// キーボードへアクセス権を獲得(入力制御開始)
	m_pDIDevice->Acquire();

	//	マウスの軸の初期化
	m_MouseState.lX = ( LONG )0.0f;
	m_MouseState.lY = ( LONG )0.0f;
	m_MouseState.lZ = ( LONG )0.0f;

	return hr;
}

/*-----------------------------------------------------------------------------
 関数名:	void CInputMouse::Update( void )
 引数:		
 戻り値:	
 説明:		マウスの更新
-----------------------------------------------------------------------------*/
void  CInputMouse::Update( void )
{

	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if(!m_pDIDevice) return;

	// デバイスからデータを取得
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

		// スクリーン座標を取得
		GetCursorPos( &m_PosMouseWorld );

	}
	else
	{
		m_pDIDevice->Acquire();	// m_pDIDeviceアクセス権を獲得( 入力制御開始 )
	}
}



/*-----------------------------------------------------------------------------
 関数名:	CXInput::CXInput()
 引数:		
 戻り値:	
 説明:		CXInputのコンストラスタ
-----------------------------------------------------------------------------*/
CXInput::CXInput()
{

	// m_stateのクリア
	ZeroMemory( &m_state , sizeof( XINPUT_STATE ) );

	// m_Vibrationのクリア
	ZeroMemory( &m_Vibration , sizeof( XINPUT_VIBRATION ) );

	//	バイブレーションの初期化( 範囲は0～65535まで )
	m_Vibration.wLeftMotorSpeed = 32000;
	m_Vibration.wRightMotorSpeed = 16000;

	m_ControllerNumber = 0;	//	コントローラーの番号

}

/*-----------------------------------------------------------------------------
 関数名:	void CXInput::Update( void )
 引数:		
 戻り値:	
 説明:		ゲームパッド( XBOX )の更新
-----------------------------------------------------------------------------*/
void CXInput::Update( void )
{

	//	ゲームパッド取得
	XInputGetState(m_ControllerNumber, &m_state );

	//	2つのアナログスティックが触っていないときや、ステックが中央にある場合

	//	左スティック
	if( ( m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		  m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) && 
		( m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
	{

		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;

	}

	//	右スティック
	if( ( m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) && 
		( m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
		  m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) ) 
	{

		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;

	}


	WORD aPadState;

	//	ボタンの取得
	aPadState = m_state.Gamepad.wButtons;

	// キートリガー リリース情報の作成
	// 1フレーム前のキー状況と今のキー状況をXORしたものを今のキー状況とANDをとる
	m_aKeyStateTrigger = ( ( m_aKeyState ^ aPadState ) & aPadState );
	m_aKeyStateRelease = ( ( m_aKeyState ^ aPadState ) & m_aKeyState );

	// キーリピート情報の生成
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

	// キープレス情報を保存
	m_aKeyState = aPadState;

	//	スティックの値を-1~1にする

	m_ThumbLX = m_state.Gamepad.sThumbLX;
	m_state.Gamepad.sThumbLX = ( m_ThumbLX / XBOX_STICK_MAXVALUE ) * -1;

	m_ThumbLY = m_state.Gamepad.sThumbLY;
	m_state.Gamepad.sThumbLY = m_ThumbLY / XBOX_STICK_MAXVALUE;

	m_ThumbRX = m_state.Gamepad.sThumbRX;
	m_state.Gamepad.sThumbRX = ( m_ThumbRX / XBOX_STICK_MAXVALUE ) * -1;

	m_ThumbRY = m_state.Gamepad.sThumbRY;
	m_state.Gamepad.sThumbRY = m_ThumbRY / XBOX_STICK_MAXVALUE;

}