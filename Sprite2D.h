/*=============================================================================

		2D描画[ Sprite2D.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _SPRITE2D_H_
#define _SPRITE2D_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CSprite2D:public CScene
{
public:
	CSprite2D(int Priolity);	//	コンストラクタ

	static CSprite2D* Create(int Priolity);	//	生成

	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

	virtual void TextureAnimation(void);		//	テクスチャアニメーション

	//	Setter
	void SetSize(const D3DXVECTOR2 Size) { m_Size = Size; }	//	大きさ
	void SetColor(const D3DXCOLOR Col) { m_Color = Col; }	//	色
	void SetTexturePattern(const int Pattern) { m_TexturePattern = Pattern; }	//	テクスチャパターン
	void SetAnimationTime(const float Time) { m_TextureAnimationTime = Time; }	//	テクスチャアニメーションタイム
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }//	テクスチャID

	//	Getter
	D3DXVECTOR2 GetSize(void) { return m_Size; }	//	大きさ
	D3DXCOLOR GetColor(void) { return m_Color; }	//	色

private:
	void MakeVerTex(void);		//	頂点の作成
	void SetUpVerTex(void);		//	頂点の設定
private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//	頂点バッファ
	D3DXVECTOR2 m_Size;					//	大きさ
	D3DXCOLOR m_Color;					//	色
	int m_TexturePattern;				//	テクスチャパターン
	float m_TextureAnimationCount;		//	テクスチャアニメーションカウンタ
	float m_TextureAnimationTime;		//	テクスチャアニメーションタイム

	CTextureManager::TEXTURE_ID m_TextureId;	//	テクスチャID
};
#endif
