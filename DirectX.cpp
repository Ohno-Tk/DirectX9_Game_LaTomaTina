/*=============================================================================

		DirectX設定[ DirectX.cpp ]

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
#include "DirectX.h"
#include "GameLoop.h"

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
D3DXCOLOR CDirectX::m_BackBufferColor = D3DCOLOR_RGBA(0, 177, 184, 255);//	バックバッファ色
LPDIRECT3D9 CDirectX::m_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9 CDirectX::m_pD3DDevice = NULL;	// Deviceオブジェクト

#ifdef _DEBUG
LPD3DXFONT CDirectX::m_Font = NULL;	// フォントへのポインタ
#endif

/*-----------------------------------------------------------------------------
 関数名:	HRESULT CDirectX::Init(HWND Wnd, bool Window)
 引数:		HWND Wnd		ウィンドウハンドル
			bool Window		ウィンドウモード
 戻り値:	return S_OK;	成功
			return E_FAIL;	失敗
 説明:		初期化
-----------------------------------------------------------------------------*/
HRESULT CDirectX::Init(HWND Wnd, bool Window)
{
	HRESULT hr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	D3DDISPLAYMODE d3ddm = {};


	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_pD3D)
	{	//	ヌルチェック

		MessageBox(NULL, "Direct3Dオブジェクトの作成に失敗", "DirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	hr = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	if (FAILED(hr))
	{
		MessageBox(NULL, "ディスプレイモードの取得に失敗", "DirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	SetUpDevice(d3dpp, d3ddm, Wnd, Window);	//	デバイスの初期化

	SetRenderState();	//	レンダーステートの設定

	SetSamplerState();	//	サンプラーステートの設定

	SetTextureStageState();	//	テクスチャステージステートの設定

#ifdef _DEBUG
	// デバッグ情報表示用フォントを生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
#endif

	return S_OK;
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::Uninit(void)
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void CDirectX::Uninit(void)
{
#ifdef _DEBUG
	if (m_Font)
	{	// 情報表示用フォント
		m_Font->Release();	//	解放
		m_Font = NULL;
	}

#endif

	if(m_pD3D)
	{	//	Direct3Dオブジェクトの破棄

		m_pD3D->Release();	//	解放
		m_pD3D = NULL;
	}

	if(m_pD3DDevice)
	{	// デバイスの破棄

		m_pD3DDevice->Release();	//	解放
		m_pD3DDevice = NULL;
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::DrawBegin(void)
 引数:		
 戻り値:	
 説明:		描画の開始
-----------------------------------------------------------------------------*/
void CDirectX::DrawBegin(void)
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), m_BackBufferColor, 1.0f, 0);

	// Direct3Dによる描画の開始
	m_pD3DDevice->BeginScene();
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::DrawEnd(void)
 引数:		
 戻り値:	
 説明:		描画の終了
-----------------------------------------------------------------------------*/
void CDirectX::DrawEnd(void)
{
#ifdef _DEBUG

	DrawFPS();	// FPS表示

#endif

	// Direct3Dによる描画の終了
	m_pD3DDevice->EndScene();

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
 引数:		D3DPRESENT_PARAMETERS d3dpp
			D3DDISPLAYMODE d3ddm
			HWND Wnd						ウィンドウハンドル
			bool Window						ウィンドウモード
 戻り値:	
 説明:		デバイスの初期化
-----------------------------------------------------------------------------*/
void CDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
{
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = Window;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル


	HRESULT hr;


	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Wnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice);
	if (FAILED(hr))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			Wnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice);
		if (FAILED(hr))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, Wnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice);
			if (FAILED(hr))
			{

				MessageBox(NULL, "デバイスの生成に失敗", "DirectX.cpp", MB_OK | MB_ICONHAND);
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::SetRenderState(void)
 引数:		
 戻り値:	
 説明:		レンダーステートの設定
-----------------------------------------------------------------------------*/
void CDirectX::SetRenderState(void)
{
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
}

/*-----------------------------------------------------------------------------
 関数名:	void CDirectX::SetRenderState(void)
 引数:		
 戻り値:	
 説明:		サンプラーステートの設定
-----------------------------------------------------------------------------*/
void CDirectX::SetSamplerState(void)
{
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定
}

/*-----------------------------------------------------------------------------
 関数名:	void SetRenderState(void)
 引数:		
 戻り値:	
 説明:		テクスチャステージステートの設定
-----------------------------------------------------------------------------*/
void CDirectX::SetTextureStageState(void)
{
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理(初期値はD3DTOP_SELECTARG1)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数(初期値はD3DTA_TEXTURE、テクスチャがない場合はD3DTA_DIFFUSE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// ２番目のアルファ引数(初期値はD3DTA_CURRENT)
}

#ifdef _DEBUG
/*-----------------------------------------------------------------------------
関数名:		void CDirectX::DrawFPS(void)
引数:
戻り値:
説明:		FPS表示
-----------------------------------------------------------------------------*/
void CDirectX::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS取得
	nCountFPS = CGameLoop::GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_Font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif