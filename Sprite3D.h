/*=============================================================================

		3D描画[ Sprite3D.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _SPRITE3D_H_
#define _SPRITE3D_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CSprite3D:public CScene
{
public:
	CSprite3D(int Priolity);	//	コンストラクタ

	static CSprite3D* Create(int Priolity);	//	生成

	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

	virtual void TextureAnimation(void);	//	テクスチャアニメーション

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	回転
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	拡大率
	void SetSize(const D3DXVECTOR3 Size) { m_Size = Size; }			//	頂点座標
	void SetNormal(const D3DXVECTOR3 Nor) { m_Normal = Nor; }		//	法線
	void SetColor(const D3DXCOLOR Col) { m_Color = Col; }			//	色
	void SetTexturePattern(const int Pattern) { m_TexturePattern = Pattern; }	//	テクスチャパターン
	void SetAnimationTime(const float Time) { m_TextureAnimationTime = Time; }	//	テクスチャアニメーションタイム
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }//	テクスチャID

	//	Getter
	const LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)const{ return m_VtxBuff; }	//	頂点バッファ
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	回転
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	拡大率
	D3DXVECTOR3 GetSize(void) { return m_Size; }			//	頂点座標
	D3DXVECTOR3 GetNormal(void) { return m_Normal; }		//	法線
	D3DXCOLOR GetColor(void) { return m_Color; }			//	色

private:
	void MakeVerTex(void);						//	頂点の作成
	virtual void SetUpVerTex(void);				//	頂点の設定
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//	頂点バッファ
	D3DXVECTOR3	m_Rotation;				//	回転
	D3DXVECTOR3	m_Scale;				//	拡大率
	float m_TextureAnimationCount;		//	テクスチャアニメーションカウンタ
	float m_TextureAnimationTime;		//	テクスチャアニメーションタイム

	CTextureManager::TEXTURE_ID m_TextureId;	//	テクスチャID

protected:
	D3DXVECTOR3 m_Size;					//	頂点座標
	D3DXVECTOR3	m_Normal;				//	法線
	D3DXCOLOR m_Color;					//	色
	int m_TexturePattern;				//	テクスチャパターン
};
#endif
