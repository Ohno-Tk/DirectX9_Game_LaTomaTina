/*=============================================================================

		フェード[ Fade.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Mode.h"
#include "Fade.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define FADE_RATE ( 1.0f / 60 )	//	どのくらいでフェードさせるのか
#define TEX_ID ( CTextureManager::TEX_FADE )	//	テクスチャのID

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
CFade::FADE CFade::m_Fade = FADE_NONE;	//	フェード状態
CMode *CFade::m_Mode = NULL;			//	画面遷移のポインタ

/*-----------------------------------------------------------------------------
 関数名:	CFade::CFade()
 引数:		
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CFade::CFade()
{
	m_VtxBuff = NULL;	// 頂点バッファ

	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//	色
}

/*-----------------------------------------------------------------------------
関数名:		CFade *CFade::Create(void)
引数:
戻り値:		return fade;	クラスのポインタ
説明:		生成
-----------------------------------------------------------------------------*/
CFade *CFade::Create(void)
{
	CFade* fade;

	fade = new CFade;

	fade->Init();	//	初期化

	return fade;
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CFade::Init(void)
{
	//	テクスチャの取得
	CTextureManager* Texture = CManager::GetTextureManager();

	Texture->Load(TEX_ID);

	MakeVerTex();	//	頂点の作成
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CFade::Uninit(void)
{
	if (m_VtxBuff)
	{
		m_VtxBuff->Release();	//	解放
		m_VtxBuff = NULL;
	}

	m_Mode = NULL;
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CFade::Update(void)
{
	AlphaFade();	//	α値のフェード

	ChangeVerTex();	//	頂点の変更
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CFade::Draw(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(TEX_ID).Texture);

	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::MakeVerTex(void)
引数:
戻り値:
説明:		頂点の作成
-----------------------------------------------------------------------------*/
void CFade::MakeVerTex(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "頂点バッファの生成に失敗", "Fade.cpp", MB_OK | MB_ICONHAND);
		return;
	}


	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//	座標変換済み頂点フラグの設定
	pVtx[0].Rhw = 1.0f;
	pVtx[1].Rhw = 1.0f;
	pVtx[2].Rhw = 1.0f;
	pVtx[3].Rhw = 1.0f;

	//	頂点色の設定
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;

	//	テクスチャ座標の設定
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::ChangeVerTex(void)
引数:
戻り値:
説明:		頂点の変更
-----------------------------------------------------------------------------*/
void CFade::ChangeVerTex(void)
{
	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点色の設定
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
関数名:		void CFade::AlphaFade(void)
引数:
戻り値:
説明:		α値のフェード
-----------------------------------------------------------------------------*/
void CFade::AlphaFade(void)
{
	//	フェードがない時の処理
	if (m_Fade == FADE_NONE) return;

	if (m_Fade == FADE_IN)
	{	//	フェードイン時の処理

		m_Color.a -= FADE_RATE;	//	a値を減算して後ろの画面を浮かび上がらせる

		if (m_Color.a < 0.0f)
		{	//	フェードインの終了

			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}
	}

	else if (m_Fade == FADE_OUT)
	{	//	フェードアウト時の処理

		m_Color.a += FADE_RATE;	//	a値を加算して後ろの画面を消していく

		if (m_Color.a > 1.0f)
		{	//	フェードアウトの終了

			m_Color.a = 1.0f;
			m_Fade = FADE_IN;	//	フェードインに処理の切り替え

			//	遷移の設定
			CManager::SetMode(m_Mode);
		}
	}
}