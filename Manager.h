/*=============================================================================

		マネージャ[ Manager.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _MANAGER_H_
#define _MANAGER_H_

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define ENABLE_PEOC_SOUND	//	Sound
//#undef ENABLE_PEOC_SOUND

#define ENABLE_PEOC_DEBUGCONSOLE	//	デバッグコンソール
#undef ENABLE_PEOC_DEBUGCONSOLE

/*-----------------------------------------------------------------------------
	前方宣言
-----------------------------------------------------------------------------*/
class CMode;			//	画面遷移
class CInputKeyboard;	//	キーボード
class CInputMouse;
#ifdef ENABLE_PEOC_SOUND
	class CSound;		//	サウンド
#endif
class CTextureManager;	//	テクスチャ管理
class CModelManager;	//	モデル管理
class CFileManager;		//	ファイル管理
class CCamera;			//	カメラ
class CLight;			//	ライト
class CFade;			//	フェード
#ifdef ENABLE_PEOC_DEBUGCONSOLE
	class CDebugConsole;	//	デバッグコンソール
#endif

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CManager
{
public:
	void Init(HINSTANCE hInstance, HWND hWnd);	//	初期化
	void Uninit(void);	//	終了
	void Update(void);	//	更新
	void Draw(void);	//	描画

	static void SetMode(CMode *Mode);	//	画面遷移の切り替え

	//	Setter
	static void SetTomatoCount(const int count) { m_TomatoCont = count; }

	//	Getter
	static CInputKeyboard* GetKeyboard(void) { return m_Keyboard; }	//	キーボード
	static CInputMouse* GetMouse(void) { return m_Mouse; }
	static CSound* GetSound(void) { return m_Sound; }				//	サウンド
	static CTextureManager* GetTextureManager(void) { return m_TextureManager; }	//	テクスチャ管理
	static CModelManager* GetModelManager(void) { return m_ModelManager; }	//	モデル管理
	static CFileManager* GetFileManager(void) { return m_FileManager; }		//	ファイル管理
	static CCamera* GetCamera(void) { return m_Camera; }			//	カメラ


	static int GetTomatoCount(void) { return m_TomatoCont; }

private:
	static CMode* m_Mode;				//	画面遷移	
	static CInputKeyboard* m_Keyboard;	//	キーボード
	static CInputMouse* m_Mouse;
#ifdef ENABLE_PEOC_SOUND
	static CSound* m_Sound;				//	サウンド
#endif
	static CTextureManager* m_TextureManager;	//	テクスチャ管理
	static CModelManager* m_ModelManager;		//	モデル管理
	static CFileManager* m_FileManager;			//	ファイル管理
	static CCamera* m_Camera;					//	カメラ
	static CLight* m_Light;						//	ライト
	static CFade* m_Fade;						//	フェード
#ifdef ENABLE_PEOC_DEBUGCONSOLE
	static CDebugConsole* m_DebugConsole;		//	デバッグコンソール
#endif

	static int m_TomatoCont;
};
#endif
