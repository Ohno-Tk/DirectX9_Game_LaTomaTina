/*=============================================================================

		DirectX設定[ DirectX.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _DIRECTX_H_
#define _DIRECTX_H_

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <d3dx9.h>
#include <crtdbg.h>
#include <Xinput.h>

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define SCREEN_WIDTH   ( 800 )	//	ウインドウの幅
#define SCREEN_HEIGHT  ( 600 )	//	ウインドウの高さ

//	頂点フォーマット
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//	2D
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)	//	3D

#define NUM_VERTEX ( 4 )	//	頂点数
#define NUM_POLYGON ( 2 )	//	ポリゴン数

#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)	//	メモリリーク検出(出力デバッグに表示される)

/*-----------------------------------------------------------------------------
	 ライブラリファイル
	 [構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
-----------------------------------------------------------------------------*/
#pragma comment(lib , "d3d9.lib")
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XAudio2.h>

#pragma comment(lib, "xinput.lib")	//	XInput
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")	//	システム時刻取得に必要
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/
struct VERTEX_2D
{
	D3DXVECTOR3 Pos;	//	頂点座標
	float Rhw;			//	座標変換済み頂点フラグ（DirectXにしかない仕様）必ず1.0fを入れる
	D3DCOLOR Color;		//	頂点カラー
	D3DXVECTOR2 Tex;	//	テクスチャ座標
};

struct VERTEX_3D
{
	D3DXVECTOR3 Pos;	//	頂点座標
	D3DXVECTOR3 Nor;	//	法線
	D3DCOLOR Color;		//	頂点カラー
	D3DXVECTOR2 Tex;	//	テクスチャ座標
};

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CDirectX
{
public:
	static HRESULT Init(HWND Wnd, bool Window);	//	初期化
	static void Uninit(void);					//	終了

	static void DrawBegin(void);	//	描画の開始
	static void DrawEnd(void);		//	描画の終了

	//	Getter
	static LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//	デバイス

private:
	//	デバイスの初期化
	static void SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window);
	static void SetRenderState(void);			//	レンダーステートの設定
	static void SetSamplerState(void);			//	サンプラーステートの設定
	static void SetTextureStageState(void);		//	テクスチャステージステートの設定

#ifdef _DEBUG
	static void DrawFPS(void);	//	FPS表示
#endif

private:
	static D3DXCOLOR m_BackBufferColor;				//	バックバッファ色

	static LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	static LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	static LPD3DXFONT m_Font;	// フォントへのポインタ
#endif
};
#endif
