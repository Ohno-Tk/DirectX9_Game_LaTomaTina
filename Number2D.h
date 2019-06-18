/*=============================================================================

		数字2D[ Number2D.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/07/14
-------------------------------------------------------------------------------
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _NUMBER2D_H_
#define _NUMBER2D_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CNumber2D
{
public:
	CNumber2D();	//	コンストラクタ

	//	生成
	static CNumber2D *Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth);

	void SetNumber(int Number);		//	数字の値設定

	void Uninit(void);	//	終了
	void Update(void);	//	更新
	void Draw( void );	//	描画

	//	Setter
	void SetColor(const D3DXCOLOR color) { m_Color = color; }	//	色のセット

private:
	void Init(int CntWidth);		//	初期化
	void MakeVerTex(int CntWidth);	//	頂点の作成
	void SetVerTex( void );		//	頂点の変更

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR2 m_Position;	//	座標
	D3DXVECTOR2 m_Size;	//	大きさ
	D3DXVECTOR2 m_USet;	//	テクスチャ座標

	D3DXCOLOR m_Color;	//	色

	CTextureManager::TEXTURE_ID m_TextureId;	//	テクスチャのID

};
#endif