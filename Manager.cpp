/*=============================================================================

		マネージャ[ Manager.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
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
	静的変数
-----------------------------------------------------------------------------*/
CMode* CManager::m_Mode = new CTitleScene;		//	画面遷移
CInputKeyboard* CManager::m_Keyboard = NULL;	//	キーボード
CInputMouse* CManager::m_Mouse = NULL;
#ifdef ENABLE_PEOC_SOUND
	CSound* CManager::m_Sound = NULL;			//	サウンド
#endif
CTextureManager* CManager::m_TextureManager = NULL;	//	テクスチャ管理
CModelManager* CManager::m_ModelManager = NULL;		//	モデル管理
CFileManager* CManager::m_FileManager = NULL;		//	ファイル管理
CCamera* CManager::m_Camera = NULL;	//	カメラ
CLight* CManager::m_Light = NULL;	//	ライト
CFade* CManager::m_Fade = NULL;		//	フェード

#ifdef ENABLE_PEOC_DEBUGCONSOLE
	CDebugConsole* CManager::m_DebugConsole = NULL;	//	デバッグコンソール
#endif

int CManager::m_TomatoCont = 0;

/*-----------------------------------------------------------------------------
 関数名:	void CManager::Init(HINSTANCE hInstance, HWND hWnd)
 引数:		HINSTANCE hInstance		インスタンス
			HWND hWnd				ウィンドウハンドル
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;


	//	DirectX
	hr = CDirectX::Init(hWnd, true);	//	初期化

	if (FAILED(hr))
	{	//	エラーチェック
		MessageBox(NULL, "DirectXクラスの生成に失敗", "Manager.cpp", MB_OK | MB_ICONHAND);
	}

	//	キーボードの生成
	m_Keyboard = new CInputKeyboard;

	hr = m_Keyboard->Init(hInstance, hWnd);	//	初期化

	if (FAILED(hr))
	{	//	エラーチェック
		MessageBox(NULL, "キーボードクラスの生成に失敗", "Manager.cpp", MB_OK | MB_ICONHAND);
	}

	m_Mouse = new CInputMouse;

	hr = m_Mouse->Init(hInstance, hWnd);
	
#ifdef ENABLE_PEOC_SOUND
	//	サウンドの生成
	m_Sound = new CSound;

	hr = m_Sound->Init();	//	初期化

	if (FAILED(hr))
	{	//	エラーチェック
		MessageBox(NULL, "キーボードクラスの生成に失敗", "Manager.cpp", MB_OK | MB_ICONHAND);
	}
#endif

	//	テクスチャクラスの生成
	m_TextureManager = new CTextureManager;

	//	モデルクラスの生成
	m_ModelManager = new CModelManager;
	m_ModelManager->Init();

	//	ファイル管理クラスの生成
	m_FileManager = new CFileManager;

	//	カメラクラスの生成
	m_Camera = new CCamera;

	//	ライトクラスの生成
	m_Light = new CLight;
	m_Light->Init();	//	初期化

	//	フェードクラスの生成
	m_Fade = CFade::Create();

	CDebugFont::Init();	//	デバッグフォントの初期化

	m_Mode->Init();	//	画面遷移の初期化

#ifdef ENABLE_PEOC_DEBUGCONSOLE

	//	デバッグコンソールクラスの生成
	m_DebugConsole = new CDebugConsole;
	m_DebugConsole->Init();
#endif
}

/*-----------------------------------------------------------------------------
関数名:		void CManager::Uninit(void)
引数:		
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CManager::Uninit(void)
{
	CDebugFont::Uninit();	//	デバッグフォントの終了

#ifdef ENABLE_PEOC_DEBUGCONSOLE
	if (m_DebugConsole)
	{	//	デバッグコンソール

		m_DebugConsole->Uninit();	//	終了
		delete m_DebugConsole;		//	解放
		m_DebugConsole = NULL;
	}
#endif

	if (m_Mode)
	{	//	画面遷移

		m_Mode->Uninit();	//	終了
		delete m_Mode;		//	解放
		m_Mode = NULL;
	}

	if (m_Fade)
	{	//	フェード

		m_Fade->Uninit();	//	終了
		delete m_Fade;		//	解放
		m_Fade = NULL;
	}

	if (m_Light)
	{	//	ライト

		delete m_Light;
		m_Light = NULL;
	}

	if (m_Camera)
	{	//	カメラ

		delete m_Camera;	//	解放
		m_Camera = NULL;
	}

	if (m_FileManager)
	{
		delete m_FileManager;
		m_FileManager = NULL;
	}

	if (m_ModelManager)
	{	//	モデル

		m_ModelManager->UnloadAll();
		delete m_ModelManager;	//	解放
		m_ModelManager = NULL;
	}

	if (m_TextureManager)
	{	//	テクスチャ

		m_TextureManager->UnloadAll();	//	全テクスチャの破棄
		delete m_TextureManager;		//	解放
		m_TextureManager = NULL;
	}

	if (m_Sound)
	{	//	サウンド

		m_Sound->Uninit();
		delete m_Sound;		//	終了
		m_Sound = NULL;		//	解放
	}

	if (m_Mouse)
	{
		m_Mouse->Uninit();
		delete m_Mouse;
		m_Mouse = NULL;
	}

	if (m_Keyboard)
	{	//	キーボード

		m_Keyboard->Uninit();	//	終了
		delete m_Keyboard;		//	解放
		m_Keyboard = NULL;
	}

	CDirectX::Uninit();	//	DirectXの終了
}

/*-----------------------------------------------------------------------------
関数名:		void CManager::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CManager::Update(void)
{
	m_Keyboard->Update();	//	キーボードの更新

	m_Mouse->Update();

	m_Camera->Update();		//	カメラの更新

	m_Fade->Update();		//	フェードの更新

	m_Mode->Update();		//	画面遷移の更新
}

/*-----------------------------------------------------------------------------
関数名:		void CManager::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CManager::Draw(void)
{
	CDirectX::DrawBegin();		//	描画の開始

	m_Mode->Draw();				//	画面遷移の描画

	m_Fade->Draw();				//	フェードの描画

	CDebugFont::Draw();			//	デバッグフォントの描画

	CDirectX::DrawEnd();		//	描画の終了
}

/*-----------------------------------------------------------------------------
関数名:		void CManager::SetMode(CMode *Mode)
引数:
戻り値:
説明:		画面遷移の切り替え
-----------------------------------------------------------------------------*/
void CManager::SetMode(CMode *Mode)
{
	if (!m_Mode) return;

	m_Mode->Uninit();	//	終了

	delete m_Mode;		//	解放
	m_Mode = NULL;

	//	新しいモードの設定
	m_Mode = Mode;

	m_Mode->Init();		//	初期化
}