/*=============================================================================

		メッシュ半球[ MeshDome.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/05/12
-------------------------------------------------------------------------------
	■　更新日
		2017/08/18
=============================================================================*/

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CMeshDome : public CScene
{
public:
	typedef enum
	{	//	どっち周りで描画させるか

		IDXBACK_DRAW_CLOCKWISE = 0,	//	時計回り
		IDXBACK_DRAW_INV_CLOCKWISE	//	逆時計回り

	}IDXBACK_DRAW;

	CMeshDome(int Priolity = 1);		//	コンストラクタ
	~CMeshDome(){}	//	デスストラクタ

	static CMeshDome *Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID);

	virtual void Init(void)override;		//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;		//	描画

	void SetRot(const D3DXVECTOR3 Rot) { m_Rot = Rot; };		//	回転のセット
															//	縦横の枚数のセット
	void SetNumBlock(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumBlock_X = NumBlock_X; m_NumBlock_Y = NumBlock_Y; };

	//	頂点数の計算
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_Vertex = (NumBlock_X + 1) * (NumBlock_Y + 1); };

	//	インデックスバッファの計算
	void SetIdxVerTex(const UINT NumBlock_X, const UINT NumBlock_Y) { m_IdxVerTex = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2; };

	//	どっち周りで描画させるか
	void SetIdxBackDraw(const IDXBACK_DRAW IdxBackDraw) { m_IdxBackDraw = IdxBackDraw; };

	//	テクスチャのIDのセット
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }

private:
	void MakeIndex(void);	//	インデックスバッファの作成
	void SetWorld(LPDIRECT3DDEVICE9 Device);		//	ワールド座標変換
	void MakeVerTex(void);	//	頂点の作成

	static LPDIRECT3DTEXTURE9 m_Texture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_IdxBuff;		//	インデックスバッファインタフェースへのポインタのアドレス

	D3DXVECTOR3	m_Rot;			// 回転
	D3DXVECTOR3	m_Scl;			// 拡大率

	D3DXVECTOR2 m_UVSet;		//	テクスチャ座標

	D3DXMATRIX	m_MtxWorld;		// ワールドマトリックス


	UINT m_NumBlock_X;	//	横の枚数
	UINT m_NumBlock_Y;	//	縦の枚数

	int m_Vertex;		//	頂点数
	int m_IdxVerTex;	//	インデックスバッファ数

	float m_Radius;	//	半径

	IDXBACK_DRAW m_IdxBackDraw;	//	どっち周りで描画させるか

	CTextureManager::TEXTURE_ID m_TextureId;	//	テクスチャのID

};
#endif