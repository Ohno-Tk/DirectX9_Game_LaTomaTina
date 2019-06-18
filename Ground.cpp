/*=============================================================================

		地面[ Ground.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite3D.h"
#include "Ground.h"

/*-----------------------------------------------------------------------------
 関数名:	CGround* CGround::Create(int Priolity)
 引数:		
 戻り値:	return ground;	クラスのポインタ
 説明:		生成
-----------------------------------------------------------------------------*/
CGround* CGround::Create(int Priolity)
{
	CGround* ground;

	ground = new CGround(Priolity);

	ground->Init();

	return ground;
}

/*-----------------------------------------------------------------------------
関数名:		void CGround::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CGround::Init(void)
{
	CSprite3D::Init();
}

/*-----------------------------------------------------------------------------
関数名:		void CGround::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CGround::Uninit(void)
{
	CSprite3D::Uninit();
}

/*-----------------------------------------------------------------------------
関数名:		void CGround::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CGround::Update(void)
{
	m_Scroll += m_ScrollSpeed;

	CSprite3D::Update();
}

/*-----------------------------------------------------------------------------
関数名:		void CGround::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CGround::Draw(void)
{
	CSprite3D::Draw();
}

/*-----------------------------------------------------------------------------
関数名:		void CGround::SetUpVerTex(void)
引数:
戻り値:
説明:		頂点の設定
-----------------------------------------------------------------------------*/
void CGround::SetUpVerTex(void)
{
	//	頂点バッファ取得
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = CSprite3D::GetVtxBuff();

	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, m_Size.z);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, -m_Size.z);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, -m_Size.y, -m_Size.z);


	//	法線
	pVtx[0].Nor = m_Normal;
	pVtx[1].Nor = m_Normal;
	pVtx[2].Nor = m_Normal;
	pVtx[3].Nor = m_Normal;


	// 頂点カラー
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;

	pVtx[0].Tex = D3DXVECTOR2(0, 0 + m_Scroll);
	pVtx[1].Tex = D3DXVECTOR2(10, 0 + m_Scroll);
	pVtx[2].Tex = D3DXVECTOR2(0, 10 + m_Scroll);
	pVtx[3].Tex = D3DXVECTOR2(10, 10 + m_Scroll);

	VtxBuff->Unlock();	//	バッファをアンロック
}