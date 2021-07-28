/*=============================================================================

		���̓f�o�C�X[ input.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/24
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/25
=============================================================================*/

#ifndef _INPUT_H_
#define _INPUT_H_

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX ( 256 )	//	�L�[�̍ő吔

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CInput
{	//	���̓f�o�C�X
public:
	CInput() { m_pDIDevice = NULL; }//	�R���X�g���N�^
	virtual ~CInput(){}	//	�f�X�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance);	//	������
	virtual void Uninit(void);		//	�I��
	virtual void Update(void) = 0;	//	�X�V

protected:
	static LPDIRECTINPUT8 m_pDInput;	// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDIDevice;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

class CInputKeyboard : public CInput
{	//	�L�[�{�[�h
public:
	CInputKeyboard();	//	�R���X�g���N�^
	~CInputKeyboard(){}	//	�f�X�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//	������
	void Uninit(void) { CInput::Uninit(); }			//	�I��
	virtual void Update(void)override;				//	�X�V

	//	����:DIK_W�Ȃ�DIK_�`
	//	�L�[�{�[�h�f�[�^�擾
	//	�v���X
	BOOL GetKeyPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE; }

	//	�g���K�[
	BOOL GetKeyTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE; }

	//	���s�[�g
	BOOL GetKeyRepeat(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE : FALSE; }

	//	�����[�X
	BOOL GetKeyRelease(int nKey) { return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE; }

	//	�L�[�{�[�h�f�[�^�폜( �g���K�[ )
	void FlushKeyTrigger(int nKey) { m_aKeyStateTrigger[nKey] = 0; }

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int	 m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
};

class CInputMouse : public CInput
{	//	�}�E�X
public:
	typedef enum
	{
		MOUSE_LEFT = 0,	//	���N���b�N
		MOUSE_RIGHT,	//	�E�N���b�N
		MOUSE_WHEEL,	//	�z�C�[��
	}MOUSEBUTTOM;

	CInputMouse() {}	//	�R���X�g���N�^
	~CInputMouse() {}	//	�f�X�X�g���N�^

	HRESULT Init(HINSTANCE hInst, HWND hWnd);	//	������
	void Uninit(void) { CInput::Uninit(); }		//	�I��
	void Update(void) override;					//	�X�V

	//	���� : MOUSEBUTTOM�\���̂��g��
	//	�}�E�X�f�[�^�擾
	//	�v���X
	BOOL GetKeyPress(int Key) { return (m_MouseState.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	//	�g���K�[
	BOOL GetKeyTrigger(int Key) { return (m_MouseStateTrigger.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	//	���s�[�g
	BOOL GetKeyRelease(int Key) { return (m_MouseStateRepeat.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }

	// �O�t���[������̍������W
	LONG GetAxisX(void) { return m_MouseState.lX; }
	LONG GetAxisY(void) { return m_MouseState.lY; }
	LONG GetAxisZ(void) { return m_MouseState.lZ; }
	
	const POINT& GetPosWorld(void) { return m_PosMouseWorld; }// �}�E�X�̃X�N���[�����W�擾
	
private:
	DIMOUSESTATE2 m_MouseState;				// �}�E�X�̏�Ԃ��󂯂郏�[�N
	DIMOUSESTATE2 m_MouseStateTrigger;		// �g���K�[�̃��[�N
	DIMOUSESTATE2 m_MouseStateRelease;		// �����[�X�̃��[�N
	DIMOUSESTATE2 m_MouseStateRepeat;		// ���s�[�g�̃��[�N
	POINT		  m_PosMouseWorld;			// �}�E�X�̃X�N���[�����W
};

class CXInput
{	//	�Q�[���p�b�h( XBOX )
public:
	typedef enum
	{
		XINPUT_DPAD_UP = 0x0001,		//	�\���L�[��
		XINPUT_DPAD_DOWN = 0x0002,		//	�\���L�[��
		XINPUT_DPAD_LEFT = 0x0004,		//	�\���L�[��
		XINPUT_DPAD_RIGHT = 0x0008,		//	�\���L�[�E
		XINPUT_START = 0x0010,			//	�X�^�[�g�L�[
		XINPUT_BACK = 0x0020,			//	�Z���N�g�L�[
		XINPUT_LEFT_THUMB = 0x0040,		//	���X�e�B�b�N��������
		XINPUT_RIGHT_THUMB = 0x0080,	//	�E�X�e�B�b�N��������
		XINPUT_LEFT_SHOULDER = 0x0100,	//	L1�L�[
		XINPUT_RIGHT_SHOULDER = 0x0200,	//	R1�L�[
		XINPUT_A = 0x1000,				//	A�{�^��
		XINPUT_B = 0x2000,				//	B�{�^��
		XINPUT_X = 0x4000,				//	X�{�^��
		XINPUT_Y = 0x8000,				//	Y�{�^��
	}XINPUT_BUTTOM;

	CXInput();	//	�R���X�g���N�^

	void Uninit(void) {}	//	�I��
	void Update(void);		//	�X�V

	//	�o�C�u���[�V�����̃Z�b�g
	void SetVibration(void) { XInputSetState(m_ControllerNumber, &m_Vibration); }

	XINPUT_STATE GetXinputState(void) { return m_state; }	//	XINPUT�\���̂̎擾

	//	���� : XINPUT_BUTTOM�񋓂��g��
	//	�Q�[���p�b�h�f�[�^�擾
	//	�v���X
	BOOL GetKeyPress(int nKey) { return (m_aKeyState & nKey) ? TRUE : FALSE; }

	//	�g���K�[
	BOOL GetKeyTrigger(int nKey) { return (m_aKeyStateTrigger & nKey) ? TRUE : FALSE; }

	//	���s�[�g
	BOOL GetKeyRepeat(int nKey) { return (m_aKeyStateRepeat & nKey) ? TRUE : FALSE; }

	//	�����[�X
	BOOL GetKeyRelease(int nKey) { return (m_aKeyStateRelease & nKey) ? TRUE : FALSE; }

	//	�Q�[���p�b�h�f�[�^�폜( �g���K�[ )
	void FlushKeyTrigger(void) { m_aKeyStateTrigger = 0; }

private:
	WORD m_aKeyState;			// �Q�[���p�b�h�̓��͏�񃏁[�N
	WORD m_aKeyStateTrigger;	// �Q�[���p�b�h�̃g���K�[��񃏁[�N
	WORD m_aKeyStateRelease;	// �Q�[���p�b�h�̃����[�X��񃏁[�N
	WORD m_aKeyStateRepeat;		// �Q�[���p�b�h�̃��s�[�g��񃏁[�N
	int	 m_aKeyStateRepeatCnt;	// �Q�[���p�b�h�̃��s�[�g�J�E���^

	SHORT m_ThumbLX;	//	���X�e�B�b�N��X
	SHORT m_ThumbLY;	//	���X�e�B�b�N��Y
    SHORT m_ThumbRX;	//	�E�X�e�B�b�N��X
    SHORT m_ThumbRY;	//	�E�X�e�B�b�N��Y

	unsigned int m_ControllerNumber;	//	�R���g���[���[�̔ԍ�

	XINPUT_STATE m_state;		//	XINPUT_STATE�\����

	DWORD m_dwResult;	//	�R���g���[���[���ǂݍ��߂����ǂ���

	XINPUT_VIBRATION m_Vibration;	//	�o�C�u���[�V�����̒l
};
#endif