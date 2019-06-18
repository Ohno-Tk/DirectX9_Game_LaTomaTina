/*=============================================================================

		ゲームループ[ GameLoop.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "GameLoop.h"
#include "Manager.h"

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
DWORD CGameLoop::m_dwFrameCount = 0;
DWORD CGameLoop::m_dwCurrentTime = 0;	//	現在の時間
DWORD CGameLoop::m_dwExecLastTime = 0;	//	現在の時刻をミリ単位で取得
DWORD CGameLoop::m_dwFPSLastTime = 0;
int CGameLoop::m_nCountFPS = 0;			//	FPSカウンタ
CManager* CGameLoop::m_Manager = NULL;	//	マネージャ

/*-----------------------------------------------------------------------------
 関数名:	
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void CGameLoop::Init(HINSTANCE hInstance, HWND hWnd)
{
	//	分解能の設定（タイマーの精度を良くする）
	timeBeginPeriod(1);

	//	各カウンターの初期化
	m_dwFrameCount = 0;
	m_dwCurrentTime = 0;				//	現在の時間
	m_dwExecLastTime = timeGetTime();	//	現在の時刻をミリ単位で取得
	m_dwFPSLastTime = m_dwExecLastTime;

	m_Manager = new CManager;
	m_Manager->Init(hInstance, hWnd);
}

/*-----------------------------------------------------------------------------
関数名:		void CGameLoop::ClockFps(void)
引数:
戻り値:
説明:		FPS計測
-----------------------------------------------------------------------------*/
void CGameLoop::ClockFps(void)
{
	m_dwCurrentTime = timeGetTime();	//	現在の時刻をミリ単位で取得

	if ((m_dwCurrentTime - m_dwFPSLastTime) >= 500)
	{

		m_nCountFPS = (m_dwFrameCount * 1000) / (m_dwCurrentTime - m_dwFPSLastTime);
		m_dwFPSLastTime = m_dwCurrentTime;
		m_dwFrameCount = 0;

	}

	if ((m_dwCurrentTime - m_dwExecLastTime) >= (1000 / 60))
	{	//	現在のフレームからどれ位たったのか( 差分計算 )	デバッグで計測したいときはifをコメントアウト

		m_dwExecLastTime = m_dwCurrentTime;	//	処理した時間を保存

		//	DirectXの処理（ゲーム処理）

		// 更新処理
		m_Manager->Update();

		// 描画処理
		m_Manager->Draw();

		m_dwFrameCount++;

	}
}

/*-----------------------------------------------------------------------------
関数名:		void CGameLoop::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CGameLoop::Uninit(void)
{
	if(m_Manager)
	{		
		m_Manager->Uninit();	//	終了処理
		delete m_Manager;		//	解放
		m_Manager = NULL;
	}
}