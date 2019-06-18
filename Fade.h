/*=============================================================================

		フェード[ Fade.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/25
=============================================================================*/

#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CFade
{
public:
	enum FADE
	{	//	フェードの状態
		FADE_NONE = 0,
		FADE_IN,	//	フェードイン
		FADE_OUT,	//	フェードアウト
	};

	CFade();	//	コンストラクタ

	//	フェードのセット
	static void SetFade(const FADE Fade, CMode *Mode) { m_Fade = Fade, m_Mode = Mode; }

	static CFade *Create(void);	//	生成
	
	void Uninit(void);	//	終了
	void Update(void);	//	更新
	void Draw(void);	//	描画

private:
	void Init(void);			//	初期化
	void MakeVerTex(void);		//	頂点の作成
	void ChangeVerTex(void);	//	頂点の変更
	void AlphaFade(void);		//	α値のフェード

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	// 頂点バッファのポインタ

	D3DXCOLOR m_Color;					//	色

	static FADE m_Fade;					//	フェード状態
	static CMode *m_Mode;				//	画面遷移のポインタ
};
#endif
