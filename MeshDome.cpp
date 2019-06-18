/*=============================================================================

		メッシュ半球[ MeshDome.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/05/12
-------------------------------------------------------------------------------
	■　更新日
		2017/08/18
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "MeshDome.h"

/*-----------------------------------------------------------------------------
	静的メンバ変数
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 CMeshDome::m_Texture = NULL;	// テクスチャへのポインタ

/*-----------------------------------------------------------------------------
関数名:		CMeshDome::CMeshDome(int Priolity)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
CMeshDome::CMeshDome(int Priolity) : CScene(Priolity)
{
	m_VtxBuff = NULL;		// 頂点バッファへのポインタ

	m_IdxBuff = NULL;	//	インデックスバッファ

	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 拡大率

	m_UVSet = D3DXVECTOR2(0.0f, 0.0f);	//	UV座標

	m_NumBlock_X = 0;	//	横の枚数
	m_NumBlock_Y = 0;	//	縦の枚数

	m_Vertex = 0;		//	頂点数
	m_IdxVerTex = 0;	//	インデックスバッファ数

	m_Radius = 0.0f;	//	半径

	m_IdxBackDraw = IDXBACK_DRAW_CLOCKWISE;	//	どっち周りで描画させるか
}

/*-----------------------------------------------------------------------------
 関数名:	CMeshDome *CMeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID)
 引数:		D3DXVECTOR3 Pos							座標
			UINT NumBlock_X							横の枚数
			UINT NumBlock_Y							縦の枚数
			float Radius							半径
			IDXBACK_DRAW IdxBack					どっち周りで描画させるか
			CTextureManager::TEXTURE_ID TextureID	テクスチャのID
 戻り値:	return MeshDome;	クラスのポインタ
 説明:		生成
-----------------------------------------------------------------------------*/
CMeshDome *CMeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID)
{

	CMeshDome *MeshDome;

	//	生成
	MeshDome = new CMeshDome;


	//	座標のセット
	MeshDome->SetPosition( Pos );

	//	縦横の枚数のセット
	MeshDome->SetNumBlock( NumBlock_X , NumBlock_Y );

	//	頂点数の計算
	MeshDome->SetVertexCount( NumBlock_X , NumBlock_Y );

	//	インデックスバッファの計算
	MeshDome->SetIdxVerTex( NumBlock_X , NumBlock_Y );

	//	どっち周りで描画させるか
	MeshDome->SetIdxBackDraw( IdxBack );

	//	テクスチャのIDのセット
	MeshDome->SetTextureID( TextureID );

	MeshDome->m_Radius = Radius;	//	半径

	MeshDome->Init();	//	初期化

	return MeshDome;
}

/*-----------------------------------------------------------------------------
関数名:		void CMeshDome::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CMeshDome::Init(void)
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_Vertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "頂点バッファの生成エラー", "MeshDome.cpp", MB_OK | MB_ICONHAND);

	}
	
	MakeVerTex();	//	頂点の作成
		
	MakeIndex();	//	インデックスバッファの作成

}

/*-----------------------------------------------------------------------------
関数名:		void CMeshDome::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CMeshDome::Uninit(void)
{

	//	ヌルチェック
	if (m_VtxBuff != NULL)
	{

		m_VtxBuff->Release();
		m_VtxBuff = NULL;

	}

	if (m_IdxBuff != NULL)
	{

		m_IdxBuff->Release();
		m_IdxBuff = NULL;

	}

	CScene::Release();	//	オブジェクト自身の解放

}

/*---------------------------------------------------------------------------- -
関数名:		void CMeshDome::Update(void)
引数 :
戻り値 :
説明 :		更新
---------------------------------------------------------------------------- - */
void CMeshDome::Update(void)
{
	m_Rot.y += 0.01f;
}

/*-----------------------------------------------------------------------------
関数名:		void CMeshDome::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CMeshDome::Draw(void)
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	//	パイプラインのストリーム
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IdxBuff);

	//	頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);

	SetWorld(Device);	//	ワールド座標変換

	//	描画
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_IdxVerTex, 0, m_IdxVerTex - 2);

}

/*-----------------------------------------------------------------------------
 関数名:	void CMeshDome::MakeVerTex(void)
 引数:		
 戻り値:	
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
void CMeshDome::MakeVerTex(void)
{

	//	仮想アドレスを取得するポインタ変数
	VERTEX_3D* pVtx;

	//	座標の格納変数
	D3DXVECTOR3 Pos;

	//	360度の一つ分の角度求める
	float Rot_XZ = 360.0f / m_NumBlock_X;

	//	90度の一つ分の角度求める
	float Rot_Y = 90.0f / m_NumBlock_Y;

	//	一つのUV座標を求める
	m_UVSet.x = 1.0f / m_NumBlock_X;
	m_UVSet.y = 1.0f / m_NumBlock_Y;


	//	バッファをロックし仮想アドレスを取得する
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	縦
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y + 1; Cnt1++)
	{

		//	角度の設定
		float θy = 90 - (Cnt1 * Rot_Y);

		//	最初に90度から求める
		//	90度から引いていく
		Pos.y = m_Radius * sinf(D3DXToRadian(θy));

		//	横
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X + 1; Cnt2++)
		{
			//	角度の設定
			float θxz = Cnt2 * Rot_XZ;

			//	XZ軸で360度求める
			Pos.x = m_Radius * cosf(D3DXToRadian(θy)) * cosf(D3DXToRadian(θxz));
			Pos.z = m_Radius * cosf(D3DXToRadian(θy)) * sinf(D3DXToRadian(θxz));


			//	頂点座標の設定
			pVtx[0].Pos = Pos;


			//	法線の設定
			pVtx[0].Nor = D3DXVECTOR3(0.0f, 10.0f, 0.0f);


			//	頂点色の設定
			pVtx[0].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	テクスチャ座標の設定
			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_UVSet.x, Cnt1 * m_UVSet.y);

			pVtx++;	//	ポインタをずらす

		}
	}

	//	バッファのアンロック
	m_VtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
関数名:		void CMeshDome::MakeIndex(void)
引数:
戻り値:
説明:		インデックスバッファの作成
-----------------------------------------------------------------------------*/
void CMeshDome::MakeIndex(void)
{

	HRESULT hr;

	WORD* pIdx;	//	ポインタ変数

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	//	インデックスバッファの生成
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_IdxVerTex,	//	バッファ量
		D3DUSAGE_WRITEONLY,	//	使用方法フラグ
		D3DFMT_INDEX16, //	インデックスフォーマット
		D3DPOOL_MANAGED, //	メモリの管理方法
		&m_IdxBuff,	//	インデックスバッファインターフェースへのポインタのアドレス
		NULL);


	//	インデックスバッファのエラーチェック
	if (FAILED(hr))
	{

		MessageBox(NULL, "インデックスバッファの生成失敗", "Mesh.cpp", MB_OK | MB_ICONHAND);

	}


	//	インデックスバッファをロック
	m_IdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	if (m_IdxBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{	//	時計回り

		//	時計回りを裏面とする
		//	縦
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{

			//	はじめじゃなかったら
			//	縮退ポリゴン
			if (Cnt1 != 0)
			{

				//	1点打つ
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	ポインタをずらす

			}

				//	2点打つ
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	ポインタをずらす

			//	横
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{

				//	2点打つ
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	ポインタをずらす

			}

				//	最後じゃなかったら
				//	縮退ポリゴン
			if (Cnt1 != m_NumBlock_Y - 1)
			{

				//	1点打つ
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	ポインタをずらす

			}
		}
	}
	else
	{

		//	逆時計回りを裏面とする
		//	縦
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{
			//	はじめじゃなかったら
			//	縮退ポリゴン
			if (Cnt1 != 0)
			{
				//	1点打つ

				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	ポインタをずらす

			}

				//	2点打つ
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	ポインタをずらす

			//	横
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{
				//	2点打つ
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	ポインタをずらす

			}

				//	最後じゃなかったら
				//	縮退ポリゴン
			if (Cnt1 != m_NumBlock_Y - 1)
			{
				//	1点打つ
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	ポインタをずらす

			}
		}
	}

	//	インデックスバッファのアンロック
	m_IdxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
関数名:		void CMeshDome::SetWorld(LPDIRECT3DDEVICE9 Device)
引数:		LPDIRECT3DDEVICE9 Device	デバイス
戻り値:
説明:		ワールド座標変換
-----------------------------------------------------------------------------*/
void CMeshDome::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX mtxScl, mtxRot, mtxPos;

	D3DXMatrixIdentity(&m_MtxWorld);	//	行列を単位行列にする


	//	拡大行列を作る
	D3DXMatrixScaling(&mtxScl,	//拡大行列が作られる
		m_Scl.x,	//	X軸拡大
		m_Scl.y,	//	Y軸拡大
		m_Scl.z);	//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	//	回転行列が作られる
		D3DXToRadian(m_Rot.y), //	Y軸回転
		D3DXToRadian(m_Rot.x), //	X軸回転
		D3DXToRadian(m_Rot.z)); //	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&mtxPos,
		m_Position.x,	//	X軸移動
		m_Position.y,	//	Y軸移動
		m_Position.z);	//	Z軸移動


	//	掛ける
	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxScl);

	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxPos);

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &m_MtxWorld);

}