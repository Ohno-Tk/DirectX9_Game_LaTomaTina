/*=============================================================================

		数字2D[ Number2D.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/07/14
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
#include "Number2D.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define BUNKATUSU ( 0.1f )	//	テクスチャの分割数

/*-----------------------------------------------------------------------------
 関数名:	CNumber2D :: CNumber2D()
 引数:		
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CNumber2D::CNumber2D()
{

	m_VtxBuff = NULL;							// 頂点バッファ

	m_Position = D3DXVECTOR2(0.0f, 0.0f);		//	座標
	m_Size = D3DXVECTOR2(0.0f, 0.0f);			//	大きさ
	m_USet = D3DXVECTOR2(0.0f, 0.0f);			//	テクスチャ座標
	m_Color = D3DXCOLOR(255, 255, 255, 255);	//	色
}

/*-----------------------------------------------------------------------------
 関数名:	CNumber2D *CNumber2D::Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth)
 引数:		D3DXVECTOR3 Pos							座標
			D3DXVECTOR3 Size						大きさ
			CTextureManager::TEXTURE_ID TextureID	テクスチャのID
			int CntWidth							横のカウンタ
			NUMBERTYPE numbertype
 戻り値:	return number2D;	クラスのポインタ
 説明:		生成
-----------------------------------------------------------------------------*/
CNumber2D *CNumber2D::Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth)
{

	CNumber2D *number2D;

	//	生成
	number2D = new CNumber2D;

	number2D->m_Position = Pos;	//	座標

	number2D->m_Size = Size;	//	大きさ

	number2D->m_TextureId = TextureID;	//	テクスチャのID

	//	初期化
	number2D->Init(CntWidth);

	return number2D;
}

/*-----------------------------------------------------------------------------
 関数名:	void CNumber2D::Init(int CntWidth)
 引数:		int CntWidth		横のカウンタ
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void CNumber2D::Init(int CntWidth)
{
	MakeVerTex(CntWidth);
}

/*-----------------------------------------------------------------------------
関数名:		void CNumber2D::Uninit( void )
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CNumber2D::Uninit(void)
{

	// 頂点バッファの破棄
	if (m_VtxBuff != NULL)	//	頂点バッファインタフェース開放
	{

		m_VtxBuff->Release();
		m_VtxBuff = NULL;

	}
}

/*-----------------------------------------------------------------------------
関数名:		void CNumber2D::Update( void )
引数:		
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CNumber2D::Update(void)
{

	//	頂点の変更
	SetVerTex();

}

/*-----------------------------------------------------------------------------
 関数名:	void CNumber2D::Draw( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void CNumber2D::Draw( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);



	// テクスチャの設定
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);


	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

/*-----------------------------------------------------------------------------
 関数名:	void CNumber2D::MakeVerTex( int CntWidth)
 引数:		int CntWidth	横のカウンタ
 戻り値:	
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
void CNumber2D::MakeVerTex(int CntWidth)
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成失敗", "Number2D.cpp", MB_OK | MB_ICONHAND);
	}

	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;


	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff-> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	頂点座標の設定
	pVtx[ 0 ].Pos = D3DXVECTOR3( m_Position.x            - m_Size.x * CntWidth , m_Position.y            , 0.0f);
	pVtx[ 1 ].Pos = D3DXVECTOR3( m_Position.x + m_Size.x - m_Size.x * CntWidth , m_Position.y            , 0.0f);
	pVtx[ 2 ].Pos = D3DXVECTOR3( m_Position.x            - m_Size.x * CntWidth , m_Position.y + m_Size.y , 0.0f);
	pVtx[ 3 ].Pos = D3DXVECTOR3( m_Position.x + m_Size.x - m_Size.x * CntWidth , m_Position.y + m_Size.y , 0.0f);


	//	座標変換済み頂点フラグの設定
	pVtx[ 0 ].Rhw = 1.0f;
	pVtx[ 1 ].Rhw = 1.0f;
	pVtx[ 2 ].Rhw = 1.0f;
	pVtx[ 3 ].Rhw = 1.0f;


	//	頂点色の設定
	pVtx[ 0 ].Color = m_Color;
	pVtx[ 1 ].Color = m_Color;
	pVtx[ 2 ].Color = m_Color;
	pVtx[ 3 ].Color = m_Color;


	//	テクスチャ座標の設定
	pVtx[ 0 ].Tex = D3DXVECTOR2( m_USet.x             , 0 );
	pVtx[ 1 ].Tex = D3DXVECTOR2( m_USet.x + BUNKATUSU , 0 );
	pVtx[ 2 ].Tex = D3DXVECTOR2( m_USet.x             , 1 );
	pVtx[ 3 ].Tex = D3DXVECTOR2( m_USet.x + BUNKATUSU , 1 );


	//	バッファのロック
	m_VtxBuff-> Unlock();

}

/*-----------------------------------------------------------------------------
 関数名:	void CNumber2D :: SetVerTex( ivoid )
 引数:		
 戻り値:	
 説明:		頂点の変更
-----------------------------------------------------------------------------*/
void CNumber2D::SetVerTex( void )
{

	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;


	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	頂点色の設定
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	//	テクスチャ座標の設定
	pVtx[0].Tex = D3DXVECTOR2(m_USet.x, 0);
	pVtx[1].Tex = D3DXVECTOR2(m_USet.x + BUNKATUSU, 0);
	pVtx[2].Tex = D3DXVECTOR2(m_USet.x, 1);
	pVtx[3].Tex = D3DXVECTOR2(m_USet.x + BUNKATUSU, 1);


	//	バッファのロック
	m_VtxBuff -> Unlock();

}

/*-----------------------------------------------------------------------------
関数名:		void CNumber2D::SetNumber(int Number)
引数:		int Number	数字
戻り値:
説明:		頂点の変更
-----------------------------------------------------------------------------*/
void CNumber2D::SetNumber(int Number)
{
	m_USet.x = Number * 0.1f;

}