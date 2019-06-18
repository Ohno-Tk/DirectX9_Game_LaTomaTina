/*=============================================================================

		入力デバイス[ input.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/11/24
-------------------------------------------------------------------------------
	■　更新日
		2017/08/25
=============================================================================*/

#ifndef _INPUT_H_
#define _INPUT_H_

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX ( 256 )	//	キーの最大数

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CInput
{	//	入力デバイス
public:
	CInput() { m_pDIDevice = NULL; }//	コンストラクタ
	virtual ~CInput(){}	//	デスストラクタ

	virtual HRESULT Init(HINSTANCE hInstance);	//	初期化
	virtual void Uninit(void);		//	終了
	virtual void Update(void) = 0;	//	更新

protected:
	static LPDIRECTINPUT8 m_pDInput;	// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDIDevice;	// 入力デバイス(キーボード)へのポインタ
};

class CInputKeyboard : public CInput
{	//	キーボード
public:
	CInputKeyboard();	//	コンストラクタ
	~CInputKeyboard(){}	//	デスストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//	初期化
	void Uninit(void) { CInput::Uninit(); }			//	終了
	virtual void Update(void)override;				//	更新

	//	引数:DIK_WなどDIK_～
	//	キーボードデータ取得
	//	プレス
	BOOL GetKeyPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE; }

	//	トリガー
	BOOL GetKeyTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE; }

	//	リピート
	BOOL GetKeyRepeat(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE : FALSE; }

	//	リリース
	BOOL GetKeyRelease(int nKey) { return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE; }

	//	キーボードデータ削除( トリガー )
	void FlushKeyTrigger(int nKey) { m_aKeyStateTrigger[nKey] = 0; }

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];	// キーボードのリピート情報ワーク
	int	 m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
};

class CInputMouse : public CInput
{	//	マウス
public:
	typedef enum
	{
		MOUSE_LEFT = 0,	//	左クリック
		MOUSE_RIGHT,	//	右クリック
		MOUSE_WHEEL,	//	ホイール
	}MOUSEBUTTOM;

	CInputMouse() {}	//	コンストラクタ
	~CInputMouse() {}	//	デスストラクタ

	HRESULT Init(HINSTANCE hInst, HWND hWnd);	//	初期化
	void Uninit(void) { CInput::Uninit(); }		//	終了
	void Update(void) override;					//	更新

	//	引数 : MOUSEBUTTOM構造体を使う
	//	マウスデータ取得
	//	プレス
	BOOL GetKeyPress(int Key) { return (m_MouseState.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	//	トリガー
	BOOL GetKeyTrigger(int Key) { return (m_MouseStateTrigger.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	//	リピート
	BOOL GetKeyRelease(int Key) { return (m_MouseStateRepeat.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	// 前フレームからの差分座標
	LONG GetAxisX(void) { return m_MouseState.lX; }
	LONG GetAxisY(void) { return m_MouseState.lY; }
	LONG GetAxisZ(void) { return m_MouseState.lZ; }
	
	const POINT& GetPosWorld(void) { return m_PosMouseWorld; }// マウスのスクリーン座標取得
	
private:
	DIMOUSESTATE2 m_MouseState;				// マウスの状態を受けるワーク
	DIMOUSESTATE2 m_MouseStateTrigger;		// トリガーのワーク
	DIMOUSESTATE2 m_MouseStateRelease;		// リリースのワーク
	DIMOUSESTATE2 m_MouseStateRepeat;		// リピートのワーク
	POINT		  m_PosMouseWorld;			// マウスのスクリーン座標
};

class CXInput
{	//	ゲームパッド( XBOX )
public:
	typedef enum
	{
		XINPUT_DPAD_UP = 0x0001,		//	十字キー上
		XINPUT_DPAD_DOWN = 0x0002,		//	十字キー下
		XINPUT_DPAD_LEFT = 0x0004,		//	十字キー左
		XINPUT_DPAD_RIGHT = 0x0008,		//	十字キー右
		XINPUT_START = 0x0010,			//	スタートキー
		XINPUT_BACK = 0x0020,			//	セレクトキー
		XINPUT_LEFT_THUMB = 0x0040,		//	左スティック押し込み
		XINPUT_RIGHT_THUMB = 0x0080,	//	右スティック押し込み
		XINPUT_LEFT_SHOULDER = 0x0100,	//	L1キー
		XINPUT_RIGHT_SHOULDER = 0x0200,	//	R1キー
		XINPUT_A = 0x1000,				//	Aボタン
		XINPUT_B = 0x2000,				//	Bボタン
		XINPUT_X = 0x4000,				//	Xボタン
		XINPUT_Y = 0x8000,				//	Yボタン
	}XINPUT_BUTTOM;

	CXInput();	//	コンストラクタ

	void Uninit(void) {}	//	終了
	void Update(void);		//	更新

	//	バイブレーションのセット
	void SetVibration(void) { XInputSetState(m_ControllerNumber, &m_Vibration); }

	XINPUT_STATE GetXinputState(void) { return m_state; }	//	XINPUT構造体の取得

	//	引数 : XINPUT_BUTTOM列挙を使う
	//	ゲームパッドデータ取得
	//	プレス
	BOOL GetKeyPress(int nKey) { return (m_aKeyState & nKey) ? TRUE : FALSE; }

	//	トリガー
	BOOL GetKeyTrigger(int nKey) { return (m_aKeyStateTrigger & nKey) ? TRUE : FALSE; }

	//	リピート
	BOOL GetKeyRepeat(int nKey) { return (m_aKeyStateRepeat & nKey) ? TRUE : FALSE; }

	//	リリース
	BOOL GetKeyRelease(int nKey) { return (m_aKeyStateRelease & nKey) ? TRUE : FALSE; }

	//	ゲームパッドデータ削除( トリガー )
	void FlushKeyTrigger(void) { m_aKeyStateTrigger = 0; }

private:
	WORD m_aKeyState;			// ゲームパッドの入力情報ワーク
	WORD m_aKeyStateTrigger;	// ゲームパッドのトリガー情報ワーク
	WORD m_aKeyStateRelease;	// ゲームパッドのリリース情報ワーク
	WORD m_aKeyStateRepeat;		// ゲームパッドのリピート情報ワーク
	int	 m_aKeyStateRepeatCnt;	// ゲームパッドのリピートカウンタ

	SHORT m_ThumbLX;	//	左スティックのX
	SHORT m_ThumbLY;	//	左スティックのY
    SHORT m_ThumbRX;	//	右スティックのX
    SHORT m_ThumbRY;	//	右スティックのY

	unsigned int m_ControllerNumber;	//	コントローラーの番号

	XINPUT_STATE m_state;		//	XINPUT_STATE構造体

	DWORD m_dwResult;	//	コントローラーが読み込めたかどうか

	XINPUT_VIBRATION m_Vibration;	//	バイブレーションの値
};
#endif