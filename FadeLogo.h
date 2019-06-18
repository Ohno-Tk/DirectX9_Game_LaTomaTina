/*=============================================================================

		フェードロゴ[ FadeLogo.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/07/20
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _FADE_LOGO_H_
#define _FADE_LOGO_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CFadeRogo :public CSprite2D
{
public:
	CFadeRogo(int Priolity);		//	コンストラクタ

	static CFadeRogo* Create(int Priolity);	//	生成

	virtual void Init(void)override { CSprite2D::Init(); }	//	初期化
	virtual void Uninit(void)override { CSprite2D::Uninit(); }	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override { CSprite2D::Draw(); }	//	描画

	//	Setter
	void SetUpLimit(const float limit) { m_UplimitFade = limit; }	//	上限値
	void SetLowerLimit(const float limit) { m_LowerFade = limit; }	//	下限値
	void SetFadeFlag(const bool Flag) { m_FadeFlag = Flag; }//	フェードフラグ
	void SetAlpha(const float value) { m_Color.a = value; }	//	α値

private:

private:
	typedef enum
	{	//	フェードの状態
		FADE_IN = 0,	//	フェードイン
		FADE_OUT,		//	フェードアウト
		FADE_MAX
	}FADE;

	D3DXCOLOR m_Color;	//	色
	float m_UplimitFade;	//	フェードの上限値
	float m_LowerFade;		//	フェードの下限値
	bool m_FadeFlag;		//	フェードフラグ

	FADE m_Fade;//	フェード状態
};
#endif
